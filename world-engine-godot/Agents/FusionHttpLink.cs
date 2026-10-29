using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using Godot;
using NltWorldEngine.Observer.Trace;

namespace NltWorldEngine.Agents;

/// <summary>
/// Async HTTP loopback: Godot POSTs each perception to a Fusion endpoint; Fusion
/// returns a correlated intent. Single-avatar, low-frequency decision cycle —
/// one in-flight request per avatar, enforced timeouts, stale ticks rejected,
/// fail closed on transport errors. Model inference never touches the Godot
/// physics/render thread: HTTP runs on background tasks, results marshal back
/// through IntentIngress's explicit main-thread dispatcher.
/// </summary>
public partial class FusionHttpLink : Node
{
	private readonly System.Net.Http.HttpClient _http = new()
	{
		// The HttpClient ceiling must not undercut the per-request CTS below: whichever fires first
		// wins, and an HttpClient timeout shorter than the request budget throws away the allowance.
		Timeout = Timeout.InfiniteTimeSpan,
	};
	private readonly Dictionary<string, Task> _inFlight = new();
	private readonly Dictionary<string, double> _backoffUntil = new();
	private readonly object _lock = new();

	/// <summary>Fusion endpoint, e.g. http://127.0.0.1:8001/agent-loop/perception (matches
	/// neurolift-ai-fusion/src/fusion/agent_loop_http.py).</summary>
	[Export] public string FusionEndpoint { get; set; } = "http://127.0.0.1:8001/agent-loop/perception";

	private static readonly JsonSerializerOptions JsonOptions = new()
	{
		PropertyNamingPolicy = null,
		DefaultIgnoreCondition = System.Text.Json.Serialization.JsonIgnoreCondition.WhenWritingNull,
	};

	/// <summary>
	/// Seconds to wait for a decision before abandoning the request.
	///
	/// Must exceed the slowest realistic inference on the Fusion side. A local GGUF decode runs on
	/// a CPU thread and routinely takes longer than the previous 5 s default; the client would give
	/// up while the server was still working, then the next tick would collide with the server's
	/// one-in-flight-per-agent guard and get a 429 — which cascaded into a warning every two seconds
	/// for the rest of the session. Failing closed is correct, but giving up *before* the server does
	/// is what turned one slow decode into a permanently broken loop.
	/// </summary>
	[Export] public float RequestTimeoutSeconds { get; set; } = 30f;

	/// <summary>Observer trace for intents and failed decisions (observer-trace-v1 §4.3, §4.5).</summary>
	public ITraceSink Trace { get; set; } = NullTraceSink.Instance;

	/// <summary>The driver's tick now, read when an intent arrives to report how far behind it is.
	/// Called from a background task; the driver's tick is a plain int, so the read is atomic.</summary>
	public Func<int> TickNow { get; set; } = () => 0;

	/// <summary>Seconds to keep quiet after a transport failure, so one outage does not become a
	/// warning on every cadence tick.</summary>
	private const float TransportBackoffSeconds = 5f;

	/// <summary>
	/// POST one perception; on correlated intent, run it through ingress.
	/// Fire-and-forget safe: drops when one request per avatar is already in flight,
	/// rejects stale ticks, fails closed (no movement) on any transport error.
	/// Returns true when a request was sent, false when it was dropped.
	/// </summary>
	public bool RequestDecision(
		AvatarCharacter avatar,
		AgentPerceptionSnapshot perception,
		IntentIngress ingress,
		int currentTick)
	{
		lock (_lock)
		{
			if (_inFlight.TryGetValue(avatar.AgentId, out var existing)
				&& !existing.IsCompleted)
				return false;

			// After a transport failure, stay quiet for a few seconds. Without this the loop
			// re-attempts on every cadence tick, so a Fusion server that is simply not running
			// produces a warning every two seconds and buries real diagnostics under its own.
			if (_backoffUntil.TryGetValue(avatar.AgentId, out var until)
				&& Time.GetTicksMsec() / 1000.0 < until)
				return false;

			_inFlight[avatar.AgentId] = FetchAndApplyAsync(avatar, perception, ingress, currentTick);
			return true;
		}
	}

	private void TraceFailure(AgentPerceptionSnapshot perception, int? httpStatus, string error)
	{
		if (Trace.Enabled)
			Trace.Write(new DecisionFailedRecord
			{
				AgentId = perception.AgentId,
				Tick = perception.Tick,
				HttpStatus = httpStatus,
				Error = error,
			});
	}

	private async Task FetchAndApplyAsync(
		AvatarCharacter avatar,
		AgentPerceptionSnapshot perception,
		IntentIngress ingress,
		int currentTick)
	{
		var _transportFailed = false;
		// In-flight and backoff bookkeeping is keyed by the avatar's internal id, as RequestDecision
		// reads it. The perception may carry a different roster id (AGENT-LOOP-003 F0).
		var key = avatar.AgentId;
		try
		{
			using var cts = new CancellationTokenSource(TimeSpan.FromSeconds(RequestTimeoutSeconds));
			var body = JsonSerializer.Serialize(perception, JsonOptions);
			using var content = new StringContent(body, Encoding.UTF8, "application/json");
			var started = System.Diagnostics.Stopwatch.StartNew();
			using var response = await _http.PostAsync(FusionEndpoint, content, cts.Token);
			if (!response.IsSuccessStatusCode)
			{
				// Read once: the trace and the 404 diagnosis below both want Fusion's own words.
				var errorBody = await response.Content.ReadAsStringAsync(cts.Token);
				TraceFailure(perception, (int)response.StatusCode,
					errorBody.Length == 0 ? response.ReasonPhrase ?? "" : errorBody[..Math.Min(errorBody.Length, 200)]);
				// 429 is the server's one-in-flight-per-agent guard, i.e. our own previous request
				// still decoding. That is a pacing signal, not a fault: log it and let the in-flight
				// guard throttle us. Treating it as a warning produced an error every cadence tick.
				if ((int)response.StatusCode == 429)
				{
					ReportInfo($"Fusion still deciding for {perception.AgentId}; request skipped.");
					return;
				}
				// 404 from Fusion's own route means no pair is registered under this agentId
				// (AGENT-LOOP-003 F0); any other 404 is most likely a wrong endpoint path.
				if ((int)response.StatusCode == 404)
				{
					ReportWarning(errorBody.Contains("agent is not registered", StringComparison.Ordinal)
						? $"Fusion does not serve agent '{perception.AgentId}'; no intent applied. " +
							"Set NLT_AGENT_LOOP_AGENT_ID to a roster id Fusion registered."
						: $"Fusion returned HTTP 404 for {perception.AgentId}; no intent applied. " +
							$"Check NLT_AGENT_LOOP_ENDPOINT ({FusionEndpoint}).");
					return;
				}
				ReportWarning($"Fusion returned HTTP {(int)response.StatusCode} for {perception.AgentId}; no intent applied.");
				return;
			}
			var json = await response.Content.ReadAsStringAsync(cts.Token);
			var decisionMs = started.ElapsedMilliseconds;
			if (!AgentLoopProtocol.TryParseIntent(json, perception, out var intent, out var parseError)
				|| intent == null)
			{
				TraceFailure(perception, (int)response.StatusCode, $"intent rejected: {parseError}");
				ReportWarning($"Fusion intent rejected for {perception.AgentId}: {parseError}");
				return;
			}
			if (Trace.Enabled)
				Trace.Write(new IntentRecord
				{
					MessageId = intent.MessageId,
					AgentId = intent.AgentId,
					ObservedTick = intent.ObservedTick,
					Verb = intent.Verb,
					TargetId = intent.TargetId,
					TicksBehind = Math.Max(0, TickNow() - intent.ObservedTick),
					DecisionMs = decisionMs,
				});
			if (intent.ObservedTick != perception.Tick)
			{
				TraceFailure(perception, (int)response.StatusCode,
					$"stale tick {intent.ObservedTick}, expected {perception.Tick}");
				ReportWarning($"Fusion intent for {perception.AgentId} used stale tick {intent.ObservedTick}; " +
					$"expected {perception.Tick}. No intent applied.");
				return;
			}
			var result = await ingress.SubmitAsync(avatar, perception, intent, currentTick);
			var status = result.Status == "accepted" ? "accepted" : "rejected";
			var detail = string.IsNullOrWhiteSpace(result.Reason) ? "" : $": {result.Reason}";
			ReportInfo($"Intent {intent.Verb} for {perception.AgentId} {status}{detail}");
		}
		catch (Exception e) when (e is System.Net.Http.HttpRequestException
			or TaskCanceledException or OperationCanceledException or JsonException)
		{
			// A timeout or a refused connection both mean "Fusion is not answering yet". Back off
			// and report once; the backoff above keeps the rest of the cadence quiet.
			_transportFailed = true;
			TraceFailure(perception, null, $"transport: {e.GetType().Name}");
			lock (_lock)
			{
				_backoffUntil[key] =
					Time.GetTicksMsec() / 1000.0 + TransportBackoffSeconds;
			}
			ReportWarning($"transport failed closed for {perception.AgentId}: {e.GetType().Name}. " +
				$"Pausing requests for {TransportBackoffSeconds:F0}s.");
		}
		catch (Exception e)
		{
			var message = $"[FusionHttpLink] decision processing failed for {perception.AgentId}: {e.GetType().Name}";
			Callable.From(() => GD.PushError(message)).CallDeferred();
		}
		finally
		{
			lock (_lock)
			{
				_inFlight.Remove(key);
				// A completed round trip clears any penalty, so recovery is immediate rather than
				// waiting out a backoff levied for a failure that no longer applies. Set by the
				// catch above, so absence here means this request did not fail on transport.
				if (!_transportFailed)
					_backoffUntil.Remove(key);
			}
		}
	}

	public override void _ExitTree()
	{
		_http.Dispose();
		base._ExitTree();
	}

	private static void ReportWarning(string message) =>
		Callable.From(() => GD.PushWarning($"[FusionHttpLink] {message}")).CallDeferred();

	private static void ReportInfo(string message) =>
		Callable.From(() => GD.Print($"[FusionHttpLink] {message}")).CallDeferred();
}
