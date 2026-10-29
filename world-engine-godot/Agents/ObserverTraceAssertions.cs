using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text.Json;
using System.Threading;

namespace NltWorldEngine.Agents;

/// <summary>
/// Checks for the <c>nlt.observer-trace.v1</c> format and writer, as plain static methods so the
/// out-of-engine harness can run them (see <see cref="ActionAssertions"/> for why).
/// </summary>
public static class ObserverTraceAssertions
{
    private static int _passed;
    private static int _failed;

    /// <summary>The golden file, relative to world-engine-godot/.</summary>
    public const string GoldenRelativePath = "fixtures/observer-trace/golden-v1.jsonl";

    /// <summary>Run every check. <paramref name="projectDir"/> is world-engine-godot/.</summary>
    public static bool RunAll(string projectDir)
    {
        _passed = 0;
        _failed = 0;
        Console.WriteLine("\n=== NLT observer-trace self-test ===");

        GoldenFormat(projectDir);
        EveryRecordIsOneJsonObject();
        NonFiniteIsNull();
        SizeCapEndsWithTruncated();
        StalledDiskNeverBlocks();

        Console.WriteLine($"\n=== {_passed} passed, {_failed} failed ===");
        return _failed == 0;
    }

    /// <summary>One record of every type, in a fixed order, for the golden file.</summary>
    public static IReadOnlyList<string> GoldenRecords() => new[]
    {
        ObserverTraceFormat.Header(new TraceHeader(
            "run-20261029T000000Z-golden00", "44ddd6f0000000000000000000000000000000000",
            "4.7.2.stable.mono.official", new DateTime(2026, 10, 29, 0, 0, 0, 125, DateTimeKind.Utc),
            10, 64L * 1024 * 1024,
            new[] { new TraceAgent("stay_alert_001", "__local_avatar__", "Local Model", "fusion-agent-loop") })),
        ObserverTraceFormat.Tick(1, "stay_alert_001", "open_world", "open_world",
            2.5f, 7.375f, -1.25f, 0f, -0.5f, 0f),
        ObserverTraceFormat.PerceptionSent(1, "stay_alert_001", "obs-1-__local_avatar__-0"),
        ObserverTraceFormat.Intent("intent-1-stay_alert_001", "stay_alert_001", 1, "approach", "plaza", 4),
        ObserverTraceFormat.Result("intent-1-stay_alert_001", "stay_alert_001", 1, "accepted", "accepted",
            "clean", null, 5),
        ObserverTraceFormat.Intent("intent-9-stay_alert_001", "stay_alert_001", 9, "sit", "well", 11),
        ObserverTraceFormat.Result("intent-9-stay_alert_001", "stay_alert_001", 9, "rejected", "physical",
            "clean", "target 'well' is occupied", 12),
        ObserverTraceFormat.Intent("intent-13-stay_alert_001", "stay_alert_001", 13, "wait", null, 14),
        ObserverTraceFormat.Result("intent-13-stay_alert_001", "stay_alert_001", 13, "rejected", "protocol",
            null, "protocol: intent observedTick is stale or does not match observation", 14),
        ObserverTraceFormat.DecisionFailed("stay_alert_001", 17, 429, "http_status", null, 18),
        ObserverTraceFormat.DecisionFailed("stay_alert_001", 21, null, "timeout", "TaskCanceledException", 40),
        ObserverTraceFormat.SceneTransition("stay_alert_001", "open_world", "workplace_2", 60),
        ObserverTraceFormat.Truncated("size_cap", 1048320, 9001),
    };

    private static void GoldenFormat(string projectDir)
    {
        Console.WriteLine("\n[golden file]");
        string path = Path.Combine(projectDir, GoldenRelativePath);
        string expected = string.Join("\n", GoldenRecords()) + "\n";
        if (Environment.GetEnvironmentVariable("NLT_UPDATE_GOLDEN") == "1")
        {
            Directory.CreateDirectory(Path.GetDirectoryName(path)!);
            File.WriteAllText(path, expected);
            Console.WriteLine($"  wrote {path}");
        }
        Check(File.Exists(path), $"golden file exists ({GoldenRelativePath})");
        if (!File.Exists(path))
            return;
        string actual = File.ReadAllText(path).Replace("\r\n", "\n");
        Check(actual == expected, "the encoder reproduces the golden file byte for byte");
        if (actual != expected)
        {
            var a = actual.Split('\n');
            var e = expected.Split('\n');
            for (int i = 0; i < Math.Min(a.Length, e.Length); i++)
                if (a[i] != e[i])
                {
                    Console.WriteLine($"  line {i + 1}\n    golden:  {a[i]}\n    encoder: {e[i]}");
                    break;
                }
        }
    }

    private static void EveryRecordIsOneJsonObject()
    {
        Console.WriteLine("\n[record shape]");
        var types = new HashSet<string>();
        bool allObjects = true, noNewlines = true, typeFirst = true;
        foreach (string line in GoldenRecords())
        {
            noNewlines &= !line.Contains('\n');
            using var doc = JsonDocument.Parse(line);
            allObjects &= doc.RootElement.ValueKind == JsonValueKind.Object;
            using var props = doc.RootElement.EnumerateObject();
            typeFirst &= props.MoveNext() && props.Current.Name == "type";
            types.Add(doc.RootElement.GetProperty("type").GetString()!);
        }
        Check(allObjects && noNewlines, "every record is one JSON object on one line");
        Check(typeFirst, "every record starts with its type");
        foreach (var t in new[] { "header", "tick", "perception_sent", "intent", "result", "decision_failed",
                     "scene_transition", "truncated" })
            Check(types.Contains(t), $"the golden file has a '{t}' record");

        using var tick = JsonDocument.Parse(ObserverTraceFormat.Tick(3, "a", "open_world", "open_world",
            0.1f, 7.3812f, -64.40001f, 0f, 0f, 0f));
        var pos = tick.RootElement.GetProperty("position");
        Check(pos.GetProperty("x").GetSingle() == 0.1f && pos.GetProperty("y").GetSingle() == 7.3812f
            && pos.GetProperty("z").GetSingle() == -64.40001f,
            "positions round-trip exactly as 32-bit floats");
    }

    private static void NonFiniteIsNull()
    {
        Console.WriteLine("\n[non-finite values]");
        string line = ObserverTraceFormat.Tick(5, "a", "open_world", "open_world",
            float.NaN, 1f, float.PositiveInfinity, 0f, 0f, 0f);
        using var doc = JsonDocument.Parse(line);
        var p = doc.RootElement.GetProperty("position");
        Check(p.GetProperty("x").ValueKind == JsonValueKind.Null && p.GetProperty("z").ValueKind == JsonValueKind.Null
            && p.GetProperty("y").GetSingle() == 1f, "NaN and infinity are written as null, not dropped or thrown");
    }

    private static void SizeCapEndsWithTruncated()
    {
        Console.WriteLine("\n[size cap]");
        string path = Path.Combine(Path.GetTempPath(), $"nlt-trace-cap-{Guid.NewGuid():N}.jsonl");
        const long cap = 4096;
        var writer = new ObserverTraceWriter(path, cap);
        int accepted = 0;
        for (int i = 0; i < 200; i++)
            if (writer.TryWrite(ObserverTraceFormat.Tick(i, "stay_alert_001", "open_world", "open_world",
                    i, 7f, -i, 1f, 0f, 1f)))
                accepted++;
        // Give the writer time to reach the cap, then confirm later lines are refused.
        var sw = Stopwatch.StartNew();
        while (writer.StopReason == null && sw.ElapsedMilliseconds < 5000)
            Thread.Sleep(10);
        bool refusedAfter = !writer.TryWrite("{\"type\":\"tick\"}");
        writer.Dispose();

        var lines = File.ReadAllLines(path);
        long size = new FileInfo(path).Length;
        File.Delete(path);
        Check(size <= cap, $"the file stays within the cap ({size} <= {cap} bytes)");
        using var last = JsonDocument.Parse(lines[^1]);
        Check(last.RootElement.GetProperty("type").GetString() == "truncated"
            && last.RootElement.GetProperty("reason").GetString() == "size_cap",
            "the last line is one truncated record with reason size_cap");
        int markers = 0;
        bool ticksInOrder = true;
        int previous = -1;
        foreach (var l in lines)
        {
            using var d = JsonDocument.Parse(l);
            if (d.RootElement.GetProperty("type").GetString() == "truncated")
                markers++;
            else
            {
                int t = d.RootElement.GetProperty("tick").GetInt32();
                ticksInOrder &= t == previous + 1;
                previous = t;
            }
        }
        Check(markers == 1, "exactly one truncated record");
        Check(ticksInOrder, "everything before it is a gap-free prefix of what was queued");
        Check(last.RootElement.GetProperty("recordsWritten").GetInt64() == lines.Length,
            "its recordsWritten counts every line in the file, itself included");
        Check(refusedAfter, "lines after the cap are refused");
    }

    /// <summary>A stream whose writes wait until released: a disk that has stopped answering.</summary>
    private sealed class StalledStream : MemoryStream
    {
        public readonly ManualResetEventSlim Gate = new(false);

        public override void Write(byte[] buffer, int offset, int count)
        {
            Gate.Wait();
            base.Write(buffer, offset, count);
        }

        public override void Flush() => Gate.Wait();
    }

    private static void StalledDiskNeverBlocks()
    {
        Console.WriteLine("\n[a stalled disk never blocks the caller]");
        var stream = new StalledStream();
        var writer = new ObserverTraceWriter(stream, 64L * 1024 * 1024, queueCapacity: 100);
        string line = ObserverTraceFormat.PerceptionSent(1, "stay_alert_001", "obs-1");
        var sw = Stopwatch.StartNew();
        int accepted = 0;
        for (int i = 0; i < 1000; i++)
            if (writer.TryWrite(line))
                accepted++;
        long ms = sw.ElapsedMilliseconds;
        Check(ms < 200, $"1000 writes against a stalled disk return in {ms} ms");
        Check(writer.StopReason == "queue_full", "the full queue stops the trace (queue_full)");
        Check(accepted <= 101, $"at most the queue's capacity was accepted ({accepted})");
        stream.Gate.Set();
        writer.Close(TimeSpan.FromSeconds(5));
        Check(writer.Dropped >= 1000 - accepted, "everything refused is counted as dropped");
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
