using System;
using System.Buffers;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.Json;
using System.Threading;

namespace NltWorldEngine.Agents;

/// <summary>
/// What the agent loop reports to an observer trace (<c>nlt.observer-trace.v1</c>,
/// <c>docs/contracts/observer-trace-v1.md</c>). Called from Godot's main thread and from HTTP
/// continuations on the thread pool, so implementations must be thread-safe, must not block, and
/// must not throw. Null everywhere it is optional: with no trace the loop behaves exactly as before.
/// </summary>
public interface IAgentLoopTrace
{
    /// <summary>A perception was actually POSTed (not dropped by the in-flight or backoff guard).</summary>
    void PerceptionSent(AgentPerceptionSnapshot perception);

    /// <summary>Fusion answered with an intent that parsed and correlated with its perception.</summary>
    void IntentReceived(SemanticIntent intent);

    /// <summary>The decision exchange produced no intent: an HTTP status, a transport error, or an
    /// answer the engine could not accept as an intent.</summary>
    void DecisionFailed(string agentId, int tick, int? httpStatus, string error, string? detail);

    /// <summary>Ingress decided an intent. <paramref name="stage"/> is one of
    /// <see cref="ObserverTraceFormat.Stages"/>; <paramref name="governanceCode"/> is null when
    /// governance did not run (a protocol rejection).</summary>
    void IntentResult(IntentExecutionResult result, string stage, string? governanceCode);
}

/// <summary>One roster entry in a trace header.</summary>
public sealed record TraceAgent(string AgentId, string EngineId, string DisplayName, string Driver);

/// <summary>Values written into a trace header.</summary>
public sealed record TraceHeader(
    string RunId,
    string EngineCommit,
    string GodotVersion,
    DateTime StartTimeUtc,
    double TraceHz,
    long MaxBytes,
    IReadOnlyList<TraceAgent> Agents);

/// <summary>
/// The <c>nlt.observer-trace.v1</c> record encoding: one JSON object per line, keys in a fixed
/// order so the format can be pinned by a golden file. Pure .NET, no Godot types, so the harness can
/// check it out of engine.
/// </summary>
public static class ObserverTraceFormat
{
    public const string SchemaVersion = "nlt.observer-trace.v1";

    /// <summary>Where the engine decided an intent: protocol validation, ASFDK governance, the
    /// live-world re-check, or acceptance for execution.</summary>
    public static readonly IReadOnlyList<string> Stages = new[] { "protocol", "governance", "physical", "accepted" };

    // Relaxed escaping keeps reasons readable (quotes stay quotes). The trace is a data file, never
    // inlined into HTML, so the HTML-safe escapes the default encoder adds buy nothing here.
    private static readonly JsonWriterOptions Options = new()
    {
        Indented = false,
        Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping,
    };

    public static string Header(TraceHeader h) => Line(w =>
    {
        w.WriteString("type", "header");
        w.WriteString("schemaVersion", SchemaVersion);
        w.WriteString("runId", h.RunId);
        w.WriteString("engineCommit", h.EngineCommit);
        w.WriteString("godotVersion", h.GodotVersion);
        w.WriteString("startTime", h.StartTimeUtc.ToUniversalTime().ToString("yyyy-MM-ddTHH:mm:ss.fffZ",
            System.Globalization.CultureInfo.InvariantCulture));
        w.WriteNumber("traceHz", h.TraceHz);
        w.WriteNumber("maxBytes", h.MaxBytes);
        w.WriteStartArray("agents");
        foreach (var a in h.Agents)
        {
            w.WriteStartObject();
            w.WriteString("agentId", a.AgentId);
            w.WriteString("engineId", a.EngineId);
            w.WriteString("displayName", a.DisplayName);
            w.WriteString("driver", a.Driver);
            w.WriteEndObject();
        }
        w.WriteEndArray();
    });

    public static string Tick(int tick, string agentId, string sceneId, string sceneKind,
        float px, float py, float pz, float vx, float vy, float vz) => Line(w =>
    {
        w.WriteString("type", "tick");
        w.WriteNumber("tick", tick);
        w.WriteString("agentId", agentId);
        w.WriteStartObject("scene");
        w.WriteString("id", sceneId);
        w.WriteString("kind", sceneKind);
        w.WriteEndObject();
        Vector(w, "position", px, py, pz);
        Vector(w, "velocity", vx, vy, vz);
    });

    public static string PerceptionSent(int tick, string agentId, string messageId) => Line(w =>
    {
        w.WriteString("type", "perception_sent");
        w.WriteNumber("tick", tick);
        w.WriteString("agentId", agentId);
        w.WriteString("messageId", messageId);
    });

    public static string Intent(string messageId, string agentId, int observedTick, string verb,
        string? targetId, int atTick) => Line(w =>
    {
        w.WriteString("type", "intent");
        w.WriteString("messageId", messageId);
        w.WriteString("agentId", agentId);
        w.WriteNumber("observedTick", observedTick);
        w.WriteString("verb", verb);
        NullableString(w, "targetId", targetId);
        w.WriteNumber("atTick", atTick);
    });

    public static string Result(string intentMessageId, string agentId, int tick, string status,
        string stage, string? governanceCode, string? reason, int atTick) => Line(w =>
    {
        w.WriteString("type", "result");
        w.WriteString("intentMessageId", intentMessageId);
        w.WriteString("agentId", agentId);
        w.WriteNumber("tick", tick);
        w.WriteString("status", status);
        w.WriteString("stage", stage);
        NullableString(w, "governanceCode", governanceCode);
        NullableString(w, "reason", reason);
        w.WriteNumber("atTick", atTick);
    });

    public static string DecisionFailed(string agentId, int tick, int? httpStatus, string error,
        string? detail, int atTick) => Line(w =>
    {
        w.WriteString("type", "decision_failed");
        w.WriteString("agentId", agentId);
        w.WriteNumber("tick", tick);
        if (httpStatus is int status)
            w.WriteNumber("httpStatus", status);
        else
            w.WriteNull("httpStatus");
        w.WriteString("error", error);
        NullableString(w, "detail", detail);
        w.WriteNumber("atTick", atTick);
    });

    public static string SceneTransition(string agentId, string from, string to, int tick) => Line(w =>
    {
        w.WriteString("type", "scene_transition");
        w.WriteString("agentId", agentId);
        w.WriteString("from", from);
        w.WriteString("to", to);
        w.WriteNumber("tick", tick);
    });

    /// <summary>The last record of a trace that hit its cap; nothing follows it.</summary>
    public static string Truncated(string reason, long bytesWritten, long recordsWritten) => Line(w =>
    {
        w.WriteString("type", "truncated");
        w.WriteString("reason", reason);
        w.WriteNumber("bytesWritten", bytesWritten);
        w.WriteNumber("recordsWritten", recordsWritten);
    });

    private static void Vector(Utf8JsonWriter w, string name, float x, float y, float z)
    {
        w.WriteStartObject(name);
        Component(w, "x", x);
        Component(w, "y", y);
        Component(w, "z", z);
        w.WriteEndObject();
    }

    // JSON has no NaN or infinity; a non-finite engine value is written as null rather than dropped,
    // so the trace still shows the engine held something unusable at that tick.
    private static void Component(Utf8JsonWriter w, string name, float value)
    {
        if (float.IsFinite(value))
            w.WriteNumber(name, value);
        else
            w.WriteNull(name);
    }

    private static void NullableString(Utf8JsonWriter w, string name, string? value)
    {
        if (value == null)
            w.WriteNull(name);
        else
            w.WriteString(name, value);
    }

    private static string Line(Action<Utf8JsonWriter> body)
    {
        var buffer = new ArrayBufferWriter<byte>(256);
        using (var w = new Utf8JsonWriter(buffer, Options))
        {
            w.WriteStartObject();
            body(w);
            w.WriteEndObject();
        }
        return Encoding.UTF8.GetString(buffer.WrittenSpan);
    }
}

/// <summary>
/// Appends trace lines to a file from a background thread. <see cref="TryWrite"/> never blocks and
/// never throws: it queues the line and returns. The file is a gap-free prefix of the run: when the
/// byte cap would be exceeded, or the queue fills because the disk cannot keep up, the writer writes
/// one <c>truncated</c> record and accepts nothing after it. Lines are flushed whenever the queue
/// drains, so a run killed by SIGHUP still leaves everything written up to that point.
/// </summary>
public sealed class ObserverTraceWriter : IDisposable
{
    /// <summary>Bytes kept free under the cap for the <c>truncated</c> record.</summary>
    public const int TruncationReserve = 256;

    private readonly ConcurrentQueue<string> _queue = new();
    private readonly SemaphoreSlim _signal = new(0);
    private readonly Thread _thread;
    private readonly Stream _stream;
    private readonly long _maxBytes;
    private readonly int _queueCapacity;
    private int _queued;
    private volatile bool _closed;
    private string? _stopReason;
    private long _bytesWritten;
    private long _recordsWritten;
    private long _dropped;

    public ObserverTraceWriter(string path, long maxBytes, int queueCapacity = 16384)
        : this(new FileStream(path, FileMode.Create, FileAccess.Write, FileShare.Read), maxBytes, queueCapacity)
    {
    }

    public ObserverTraceWriter(Stream stream, long maxBytes, int queueCapacity = 16384)
    {
        if (maxBytes <= TruncationReserve)
            throw new ArgumentOutOfRangeException(nameof(maxBytes), $"cap must exceed {TruncationReserve} bytes");
        _stream = stream;
        _maxBytes = maxBytes;
        _queueCapacity = Math.Max(1, queueCapacity);
        _thread = new Thread(Run) { IsBackground = true, Name = "ObserverTraceWriter" };
        _thread.Start();
    }

    /// <summary>Lines written to the file so far, including the <c>truncated</c> record.</summary>
    public long RecordsWritten => Interlocked.Read(ref _recordsWritten);

    /// <summary>Bytes written to the file so far.</summary>
    public long BytesWritten => Interlocked.Read(ref _bytesWritten);

    /// <summary>Lines refused after the trace stopped (cap reached, queue full, or closed).</summary>
    public long Dropped => Interlocked.Read(ref _dropped);

    /// <summary>Why the trace stopped early, or null while it is still accepting lines.</summary>
    public string? StopReason => Volatile.Read(ref _stopReason);

    /// <summary>Queue one line. Returns false, without blocking, if the trace no longer accepts lines.</summary>
    public bool TryWrite(string line)
    {
        if (_closed || Volatile.Read(ref _stopReason) != null)
        {
            Interlocked.Increment(ref _dropped);
            return false;
        }
        if (Interlocked.Increment(ref _queued) > _queueCapacity)
        {
            Interlocked.Decrement(ref _queued);
            Interlocked.Increment(ref _dropped);
            Stop("queue_full");
            _signal.Release();
            return false;
        }
        _queue.Enqueue(line);
        _signal.Release();
        return true;
    }

    private void Stop(string reason) => Interlocked.CompareExchange(ref _stopReason, reason, null);

    private void Run()
    {
        bool markerWritten = false;
        try
        {
            while (true)
            {
                _signal.Wait(250);
                while (_queue.TryDequeue(out var line))
                {
                    Interlocked.Decrement(ref _queued);
                    if (markerWritten)
                    {
                        Interlocked.Increment(ref _dropped);
                        continue;
                    }
                    var bytes = Encoding.UTF8.GetBytes(line + "\n");
                    if (_bytesWritten + bytes.Length > _maxBytes - TruncationReserve)
                    {
                        Stop("size_cap");
                        Interlocked.Increment(ref _dropped);
                        markerWritten = WriteMarker();
                        continue;
                    }
                    Append(bytes);
                }
                // Everything queued before a queue overflow is written first; the marker follows it.
                if (!markerWritten && Volatile.Read(ref _stopReason) != null && _queue.IsEmpty)
                    markerWritten = WriteMarker();
                _stream.Flush();
                if ((_closed || markerWritten) && _queue.IsEmpty)
                    break;
            }
        }
        catch (Exception e) when (e is IOException or ObjectDisposedException or UnauthorizedAccessException)
        {
            // The disk failed under the trace. The loop is unaffected; the trace stops here.
            Stop("io_error");
        }
    }

    private bool WriteMarker()
    {
        var marker = ObserverTraceFormat.Truncated(Volatile.Read(ref _stopReason) ?? "size_cap", _bytesWritten,
            _recordsWritten + 1);
        Append(Encoding.UTF8.GetBytes(marker + "\n"));
        return true;
    }

    private void Append(byte[] bytes)
    {
        _stream.Write(bytes, 0, bytes.Length);
        Interlocked.Add(ref _bytesWritten, bytes.Length);
        Interlocked.Increment(ref _recordsWritten);
    }

    /// <summary>Write what is queued, then close the file. Waits at most <paramref name="timeout"/>.</summary>
    public void Dispose() => Close(TimeSpan.FromSeconds(2));

    public void Close(TimeSpan timeout)
    {
        if (_closed)
            return;
        _closed = true;
        _signal.Release();
        _thread.Join(timeout);
        try
        {
            _stream.Dispose();
        }
        catch (IOException)
        {
        }
    }
}
