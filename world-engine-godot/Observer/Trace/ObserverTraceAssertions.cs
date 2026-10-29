using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using NltWorldEngine.Agents;

namespace NltWorldEngine.Observer.Trace;

/// <summary>
/// Checks for the observer-trace producer (OBS-TRACE-001), runnable outside the engine. Like
/// <see cref="ActionAssertions"/>, a plain static class so AgentHarness can drive it.
/// </summary>
public static class ObserverTraceAssertions
{
    private static int _passed;
    private static int _failed;

    /// <summary>Run every check. Returns true when all passed.</summary>
    public static bool RunAll()
    {
        _passed = 0;
        _failed = 0;
        Console.WriteLine("\n=== NLT observer-trace self-test ===");

        HeaderComesFirst();
        RecordShapes();
        ConcurrentWritesStayWholeLines();
        DisabledSinkWritesNothing();
        EnableSwitch();
        IngressReportsStage();

        Console.WriteLine($"\n=== {_passed} passed, {_failed} failed ===");
        return _failed == 0;
    }

    private static List<JsonElement> Lines(StringWriter text)
        => text.ToString().Split('\n', StringSplitOptions.RemoveEmptyEntries)
            .Select(l => JsonDocument.Parse(l).RootElement.Clone())
            .ToList();

    private static ObserverTraceWriter NewWriter(StringWriter into)
        => new(into, new TraceHeader
        {
            RunId = "run-test",
            GodotVersion = "test",
            StartTime = "2026-10-29T00:00:00Z",
            AgentRoster = new[] { "stay_alert_001" },
            CadenceHz = 10,
        });

    private static void HeaderComesFirst()
    {
        Console.WriteLine("\n[header]");
        var text = new StringWriter();
        using var writer = NewWriter(text);
        var lines = Lines(text);
        Check(lines.Count == 1, "the header is written as soon as the writer opens");
        var h = lines[0];
        Check(h.GetProperty("schemaVersion").GetString() == ObserverTraceVocabulary.SchemaVersion,
            "header carries exactly nlt.observer-trace.v1");
        Check(new[] { "runId", "engineCommit", "godotVersion", "startTime", "agentRoster", "cadenceHz" }
                .All(k => h.TryGetProperty(k, out _)),
            "header carries every required key");
        Check(!h.TryGetProperty("synthetic", out _), "a real run does not claim to be synthetic");
        Check(TraceHeader.NewRunId(new DateTime(2026, 10, 29, 14, 5, 12, DateTimeKind.Utc))
                .StartsWith("run-20261029T140512Z-", StringComparison.Ordinal),
            "run ids sort by start time");
    }

    private static void RecordShapes()
    {
        Console.WriteLine("\n[record shapes]");
        var text = new StringWriter();
        using (var writer = NewWriter(text))
        {
            var v = TraceVector.Of(1, 0, 2);
            writer.Write(new TickRecord { Tick = 1, AgentId = "a", Scene = new TraceScene { Id = "open_world", Kind = "open_world" }, Position = v, Velocity = v });
            writer.Write(new PerceptionSentRecord { Tick = 1, AgentId = "a" });
            writer.Write(new IntentRecord { MessageId = "i1", AgentId = "a", ObservedTick = 1, Verb = "wait" });
            writer.Write(new ResultRecord { IntentMessageId = "i1", Status = "accepted", Stage = ObserverTraceVocabulary.StageAccepted });
            writer.Write(new DecisionFailedRecord { AgentId = "a", Tick = 2, Error = "transport: TaskCanceledException" });
            writer.Write(new SceneTransitionRecord { AgentId = "a", From = "open_world", To = "personal_1", Tick = 3 });
            writer.Write(new SceneEntitiesRecord { Scene = "personal_1", Entities = new[] { new TraceEntity { Id = "exit", Kind = "door", Position = v, Affordances = new[] { "use" } } } });
            Check(writer.RecordCount == 7, "the writer counts records, not the header");
        }
        var lines = Lines(text).Skip(1).ToList();
        var types = lines.Select(l => l.GetProperty("type").GetString()).ToArray();
        Check(types.SequenceEqual(new[] { "tick", "perception_sent", "intent", "result", "decision_failed", "scene_transition", "scene_entities" }),
            "each record carries its contract type as the 'type' discriminator, in write order");
        Check(lines.All(l => l.EnumerateObject().First().Name == "type" && l.EnumerateObject().Count(p => p.Name.Equals("type", StringComparison.OrdinalIgnoreCase)) == 1),
            "the discriminator is written once, as the first key");
        var required = new Dictionary<string, string[]>
        {
            ["tick"] = new[] { "tick", "agentId", "scene", "position", "velocity" },
            ["perception_sent"] = new[] { "tick", "agentId" },
            ["intent"] = new[] { "messageId", "agentId", "observedTick", "verb" },
            ["result"] = new[] { "intentMessageId", "status", "stage" },
            ["decision_failed"] = new[] { "agentId", "tick" },
            ["scene_transition"] = new[] { "agentId", "from", "to", "tick" },
            ["scene_entities"] = new[] { "scene", "entities" },
        };
        Check(lines.All(l => required[l.GetProperty("type").GetString()!].All(k => l.TryGetProperty(k, out _))),
            "every record carries its required keys");
        Check(!lines[2].TryGetProperty("targetId", out _) && !lines[4].TryGetProperty("httpStatus", out _),
            "absent optional fields are omitted, not written as null");
        Check(lines[0].GetProperty("position").GetProperty("z").GetSingle() == 2f,
            "positions keep Godot's frame (z is horizontal)");
    }

    private static void ConcurrentWritesStayWholeLines()
    {
        Console.WriteLine("\n[thread safety]");
        var text = new StringWriter();
        using (var writer = NewWriter(text))
        {
            // FusionHttpLink reports from background tasks while the driver samples on the main
            // thread: interleaved writes must still be one JSON object per line.
            Parallel.For(0, 400, i => writer.Write(new PerceptionSentRecord { Tick = i, AgentId = $"a{i % 4}" }));
        }
        var raw = text.ToString().Split('\n', StringSplitOptions.RemoveEmptyEntries);
        bool allParse = raw.All(l =>
        {
            try { JsonDocument.Parse(l); return true; }
            catch (JsonException) { return false; }
        });
        Check(raw.Length == 401 && allParse, "400 concurrent writes leave 400 whole lines after the header");
    }

    private static void DisabledSinkWritesNothing()
    {
        Console.WriteLine("\n[tracing off]");
        Check(!NullTraceSink.Instance.Enabled, "the default sink reports itself disabled");
        var text = new StringWriter();
        var writer = NewWriter(text);
        writer.Dispose();
        writer.Write(new PerceptionSentRecord { Tick = 1, AgentId = "a" });
        Check(!writer.Enabled && Lines(text).Count == 1, "a closed writer drops later records");

        var failing = new FailingWriter();
        var broken = new ObserverTraceWriter(failing, new TraceHeader { RunId = "run-test" });
        failing.Fail = true;
        bool threw = false;
        try { broken.Write(new PerceptionSentRecord { Tick = 1, AgentId = "a" }); }
        catch (IOException) { threw = true; }
        Check(!threw && !broken.Enabled && broken.Error is IOException,
            "an I/O error stops tracing instead of throwing into the decision path");
    }

    /// <summary>A disk that fills up after the header.</summary>
    private sealed class FailingWriter : StringWriter
    {
        public bool Fail;

        public override void Write(string? value)
        {
            if (Fail)
                throw new IOException("No space left on device");
            base.Write(value);
        }
    }

    private static void EnableSwitch()
    {
        Console.WriteLine("\n[--trace / NLT_OBSERVER_TRACE]");
        Check(ObserverTraceLauncher.RequestedPath(Array.Empty<string>(), "") == null, "off by default");
        Check(ObserverTraceLauncher.RequestedPath(Array.Empty<string>(), "0") == null, "NLT_OBSERVER_TRACE=0 stays off");
        Check(ObserverTraceLauncher.RequestedPath(new[] { "--trace" }, null) == "", "--trace alone means the default path");
        Check(ObserverTraceLauncher.RequestedPath(new[] { "--trace", "/tmp/a.jsonl" }, null) == "/tmp/a.jsonl", "--trace <path> uses that path");
        Check(ObserverTraceLauncher.RequestedPath(new[] { "--trace", "--capture", "x.png" }, null) == "",
            "a flag after --trace is not taken as its path");
        Check(ObserverTraceLauncher.RequestedPath(Array.Empty<string>(), "1") == "", "NLT_OBSERVER_TRACE=1 means the default path");
        Check(ObserverTraceLauncher.RequestedPath(Array.Empty<string>(), "/tmp/b.jsonl") == "/tmp/b.jsonl", "NLT_OBSERVER_TRACE=<path> uses that path");
    }

    private static void IngressReportsStage()
    {
        Console.WriteLine("\n[ingress reports the deciding stage]");
        var perception = new AgentPerceptionSnapshot
        {
            MessageId = "obs-7",
            AgentId = "stay_alert_001",
            Tick = 7,
            Scene = new AgentLoopScene { Id = "open_world", Kind = "open_world" },
            Self = new AgentPhysicalState { Position = new PhysicalVector3(), Velocity = new PhysicalVector3() },
            VisibleEntities = Array.Empty<VisibleEntity>(),
        };
        var text = new StringWriter();
        using var writer = NewWriter(text);
        var ingress = new IntentIngress(OpenGovernanceGate.Instance, runOnMainThread: f => Task.FromResult(f()), trace: writer);

        // Not in the verb allowlist: refused by protocol validation, before governance runs.
        var refused = ingress.SubmitAsync(null!, perception,
            new SemanticIntent { MessageId = "int-1", AgentId = "stay_alert_001", ObservedTick = 7, Verb = "teleport" }, 7).Result;
        // Valid, but there is no avatar to move: refused by the live-world re-check.
        var gone = ingress.SubmitAsync(null!, perception,
            new SemanticIntent { MessageId = "int-2", AgentId = "stay_alert_001", ObservedTick = 7, Verb = "wait" }, 7).Result;

        var results = Lines(text).Skip(1).ToList();
        Check(results.Count == 2 && results.All(r => r.GetProperty("type").GetString() == "result"),
            "every ingress outcome is traced as a result");
        Check(refused.Status == "rejected" && results[0].GetProperty("stage").GetString() == ObserverTraceVocabulary.StageProtocol,
            "a protocol refusal is traced with stage 'protocol'");
        Check(gone.Status == "rejected" && results[1].GetProperty("stage").GetString() == ObserverTraceVocabulary.StagePhysical,
            "a live-world refusal is traced with stage 'physical'");
        Check(results[1].GetProperty("intentMessageId").GetString() == "int-2" && results[1].GetProperty("tick").GetInt32() == 7,
            "the traced result names its intent and tick");
        Check(!results[0].TryGetProperty("governanceCode", out _),
            "a protocol refusal carries no governance code: the gate never ran");
        Check(results[1].TryGetProperty("governanceCode", out var bypass) && bypass.GetString() == "gate-unavailable",
            "a bypassed gate is visible in the trace as 'gate-unavailable'");

        var cleanText = new StringWriter();
        using var cleanWriter = NewWriter(cleanText);
        var cleanIngress = new IntentIngress(new CleanGate(), runOnMainThread: f => Task.FromResult(f()), trace: cleanWriter);
        cleanIngress.SubmitAsync(null!, perception,
            new SemanticIntent { MessageId = "int-3", AgentId = "stay_alert_001", ObservedTick = 7, Verb = "wait" }, 7).Wait();
        Check(!Lines(cleanText)[1].TryGetProperty("governanceCode", out _),
            "a clean gate code is not reported as a governance code");
    }

    private sealed class CleanGate : IGovernanceGate
    {
        public Task<GovernanceDecision> EvaluateAsync(SemanticIntent intent)
            => Task.FromResult(new GovernanceDecision { Allowed = true });
    }

    private static void Check(bool condition, string what)
    {
        if (condition)
        {
            _passed++;
            Console.WriteLine($"  PASS  {what}");
        }
        else
        {
            _failed++;
            Console.WriteLine($"  FAIL  {what}");
        }
    }
}
