using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace NltWorldEngine.Observer.Trace;

// The nlt.observer-trace.v1 producer (docs/contracts/observer-trace-v1.md).
//
// Plain C# on purpose: no Godot types, so AgentHarness can drive the writer and check its output
// without launching the engine. Callers convert Vector3 to TraceVector at the hook point.

/// <summary>Wire vocabulary for the observer trace.</summary>
public static class ObserverTraceVocabulary
{
    public const string SchemaVersion = "nlt.observer-trace.v1";

    public const string StageProtocol = "protocol";
    public const string StageGovernance = "governance";
    public const string StagePhysical = "physical";
    public const string StageAccepted = "accepted";
}

/// <summary>A position or velocity, in Godot's frame (y up).</summary>
public sealed class TraceVector
{
    [JsonPropertyName("x")] public float X { get; init; }
    [JsonPropertyName("y")] public float Y { get; init; }
    [JsonPropertyName("z")] public float Z { get; init; }

    public static TraceVector Of(float x, float y, float z) => new() { X = x, Y = y, Z = z };
}

public sealed class TraceScene
{
    [JsonPropertyName("id")] public string Id { get; init; } = "";
    [JsonPropertyName("kind")] public string Kind { get; init; } = "";
}

/// <summary>Line 1 of every trace (contract §3).</summary>
public sealed class TraceHeader
{
    [JsonPropertyName("schemaVersion")] public string SchemaVersion { get; init; } = ObserverTraceVocabulary.SchemaVersion;
    [JsonPropertyName("runId")] public string RunId { get; init; } = "";
    [JsonPropertyName("engineCommit")] public string EngineCommit { get; init; } = "unknown";
    [JsonPropertyName("godotVersion")] public string GodotVersion { get; init; } = "";
    [JsonPropertyName("startTime")] public string StartTime { get; init; } = "";
    [JsonPropertyName("agentRoster")] public IReadOnlyList<string> AgentRoster { get; init; } = Array.Empty<string>();
    [JsonPropertyName("cadenceHz")] public float CadenceHz { get; init; }
    [JsonPropertyName("tickUnit")] public string TickUnit { get; init; } = "frame";
    [JsonPropertyName("synthetic")] public bool? Synthetic { get; init; }

    /// <summary>A run id that sorts by start time and does not collide across same-second runs.</summary>
    public static string NewRunId(DateTime utcNow)
        => $"run-{utcNow:yyyyMMdd'T'HHmmss'Z'}-{Guid.NewGuid().ToString("N")[..4]}";
}

/// <summary>Base for every record after the header. <see cref="Type"/> is the wire discriminator.</summary>
public abstract class TraceRecord
{
    protected TraceRecord(string type) => Type = type;

    // Not virtual: an override would not inherit the attribute, and System.Text.Json would then
    // write the discriminator twice ("Type" and "type"). First on the line, for people reading it.
    [JsonPropertyName("type"), JsonPropertyOrder(-1)] public string Type { get; }
}

public sealed class TickRecord : TraceRecord
{
    public TickRecord() : base("tick") { }
    [JsonPropertyName("tick")] public int Tick { get; init; }
    [JsonPropertyName("agentId")] public string AgentId { get; init; } = "";
    [JsonPropertyName("scene")] public TraceScene Scene { get; init; } = new();
    [JsonPropertyName("position")] public TraceVector Position { get; init; } = new();
    [JsonPropertyName("velocity")] public TraceVector Velocity { get; init; } = new();
}

public sealed class PerceptionSentRecord : TraceRecord
{
    public PerceptionSentRecord() : base("perception_sent") { }
    [JsonPropertyName("tick")] public int Tick { get; init; }
    [JsonPropertyName("agentId")] public string AgentId { get; init; } = "";
    [JsonPropertyName("messageId")] public string? MessageId { get; init; }
    [JsonPropertyName("visibleEntities")] public int? VisibleEntities { get; init; }
}

public sealed class IntentRecord : TraceRecord
{
    public IntentRecord() : base("intent") { }
    [JsonPropertyName("messageId")] public string MessageId { get; init; } = "";
    [JsonPropertyName("agentId")] public string AgentId { get; init; } = "";
    [JsonPropertyName("observedTick")] public int ObservedTick { get; init; }
    [JsonPropertyName("verb")] public string Verb { get; init; } = "";
    [JsonPropertyName("targetId")] public string? TargetId { get; init; }
    [JsonPropertyName("ticksBehind")] public int? TicksBehind { get; init; }
    [JsonPropertyName("decisionMs")] public long? DecisionMs { get; init; }
}

public sealed class ResultRecord : TraceRecord
{
    public ResultRecord() : base("result") { }
    [JsonPropertyName("intentMessageId")] public string IntentMessageId { get; init; } = "";
    [JsonPropertyName("agentId")] public string? AgentId { get; init; }
    [JsonPropertyName("tick")] public int? Tick { get; init; }
    [JsonPropertyName("status")] public string Status { get; init; } = "";
    [JsonPropertyName("stage")] public string Stage { get; init; } = ObserverTraceVocabulary.StagePhysical;
    [JsonPropertyName("governanceCode")] public string? GovernanceCode { get; init; }
    [JsonPropertyName("reason")] public string? Reason { get; init; }
}

public sealed class DecisionFailedRecord : TraceRecord
{
    public DecisionFailedRecord() : base("decision_failed") { }
    [JsonPropertyName("agentId")] public string AgentId { get; init; } = "";
    [JsonPropertyName("tick")] public int Tick { get; init; }
    [JsonPropertyName("httpStatus")] public int? HttpStatus { get; init; }
    [JsonPropertyName("error")] public string? Error { get; init; }
}

public sealed class SceneTransitionRecord : TraceRecord
{
    public SceneTransitionRecord() : base("scene_transition") { }
    [JsonPropertyName("agentId")] public string AgentId { get; init; } = "";
    [JsonPropertyName("from")] public string From { get; init; } = "";
    [JsonPropertyName("to")] public string To { get; init; } = "";
    [JsonPropertyName("tick")] public int Tick { get; init; }
}

public sealed class TraceEntity
{
    [JsonPropertyName("id")] public string Id { get; init; } = "";
    [JsonPropertyName("kind")] public string Kind { get; init; } = "";
    [JsonPropertyName("position")] public TraceVector Position { get; init; } = new();
    [JsonPropertyName("affordances")] public IReadOnlyList<string> Affordances { get; init; } = Array.Empty<string>();
}

public sealed class SceneEntitiesRecord : TraceRecord
{
    public SceneEntitiesRecord() : base("scene_entities") { }
    [JsonPropertyName("scene")] public string Scene { get; init; } = "";
    [JsonPropertyName("tick")] public int? Tick { get; init; }
    [JsonPropertyName("entities")] public IReadOnlyList<TraceEntity> Entities { get; init; } = Array.Empty<TraceEntity>();
}

/// <summary>Where trace records go. Hook points write here and never check whether tracing is on.</summary>
public interface ITraceSink
{
    /// <summary>False for the no-op sink, so a hook can skip building a costly record.</summary>
    bool Enabled { get; }

    void Write(TraceRecord record);
}

/// <summary>The default: tracing off, nothing written, nothing allocated by callers that check
/// <see cref="Enabled"/>.</summary>
public sealed class NullTraceSink : ITraceSink
{
    public static readonly NullTraceSink Instance = new();

    private NullTraceSink() { }

    public bool Enabled => false;

    public void Write(TraceRecord record) { }
}

/// <summary>
/// Writes one JSON object per line: the header, then each record as it is written.
///
/// Thread-safe, because <c>FusionHttpLink</c> reports from background tasks while the driver
/// writes ticks on the main thread. Flushes after every line: headless Godot is stopped with
/// SIGHUP, which runs no shutdown code, so anything still buffered would be lost.
///
/// Never throws from <see cref="Write"/>: a trace only reports, so a full disk must not fail the
/// decision path that called it. The first I/O error stops tracing and is kept in
/// <see cref="Error"/>.
/// </summary>
public sealed class ObserverTraceWriter : ITraceSink, IDisposable
{
    private static readonly JsonSerializerOptions JsonOptions = new()
    {
        DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull,
        // Reasons are engine-authored prose; keep apostrophes and arrows readable in the file.
        Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping,
    };

    private readonly TextWriter _out;
    private readonly bool _ownsWriter;
    private readonly object _lock = new();
    private bool _disposed;

    public ObserverTraceWriter(TextWriter output, TraceHeader header, bool ownsWriter = false)
    {
        _out = output ?? throw new ArgumentNullException(nameof(output));
        _ownsWriter = ownsWriter;
        Header = header ?? throw new ArgumentNullException(nameof(header));
        WriteLine(JsonSerializer.Serialize(header, JsonOptions));
    }

    /// <summary>Open (and create the folder for) a trace file. Overwrites a file already there.</summary>
    public static ObserverTraceWriter Open(string path, TraceHeader header)
    {
        var folder = Path.GetDirectoryName(Path.GetFullPath(path));
        if (!string.IsNullOrEmpty(folder))
            Directory.CreateDirectory(folder);
        var stream = new StreamWriter(path, append: false, new UTF8Encoding(false)) { NewLine = "\n" };
        return new ObserverTraceWriter(stream, header, ownsWriter: true) { FilePath = path };
    }

    public TraceHeader Header { get; }

    /// <summary>The file being written, or null when writing to a caller's <see cref="TextWriter"/>.</summary>
    public string? FilePath { get; private init; }

    /// <summary>Records written after the header.</summary>
    public int RecordCount { get; private set; }

    /// <summary>The I/O error that stopped tracing, or null.</summary>
    public Exception? Error { get; private set; }

    public bool Enabled => !_disposed && Error == null;

    public void Write(TraceRecord record)
    {
        if (record == null)
            return;
        // Serialise as the runtime type: the declared base type has only the discriminator.
        var line = JsonSerializer.Serialize(record, record.GetType(), JsonOptions);
        lock (_lock)
        {
            if (!Enabled)
                return;
            try
            {
                WriteLine(line);
                RecordCount++;
            }
            catch (Exception e) when (e is IOException or ObjectDisposedException)
            {
                Error = e;
            }
        }
    }

    private void WriteLine(string line)
    {
        _out.Write(line);
        _out.Write('\n');
        _out.Flush();
    }

    public void Dispose()
    {
        lock (_lock)
        {
            if (_disposed)
                return;
            _disposed = true;
            _out.Flush();
            if (_ownsWriter)
                _out.Dispose();
        }
    }
}
