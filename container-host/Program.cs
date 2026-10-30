using System.Diagnostics;
using System.Security.Cryptography;
using System.Text;
using System.Text.Json;

// Container entrypoint: supervises the exported headless Godot server and serves HTTP.
var port = Environment.GetEnvironmentVariable("PORT") is { Length: > 0 } p ? p : "80";
var godotBinary = Environment.GetEnvironmentVariable("NLT_GODOT_BIN")
    ?? "/app/engine/nlt-world-engine.x86_64";
var runToken = Environment.GetEnvironmentVariable("NLT_RUN_TOKEN") ?? "";
const int MaxBodyBytes = 1 << 20;

var builder = WebApplication.CreateBuilder(args);
builder.WebHost.UseUrls($"http://0.0.0.0:{port}");
builder.Services.AddSingleton(new GodotSupervisor(godotBinary));
builder.Services.AddHostedService(sp => sp.GetRequiredService<GodotSupervisor>());
var app = builder.Build();

// Liveness for the platform and callers. 503 once the engine process has exited.
app.MapGet("/health", (GodotSupervisor godot) =>
{
    var body = new { status = godot.Running ? "ok" : "engine_down", godot = godot.Running, uptimeSeconds = godot.UptimeSeconds, exitCode = godot.ExitCode };
    return Results.Json(body, statusCode: godot.Running ? 200 : 503);
});

// Fails closed: with no NLT_RUN_TOKEN configured the endpoint is disabled, never open.
app.MapPost("/run", async (HttpRequest req) =>
{
    if (runToken.Length == 0)
        return Results.Json(new { error = "run_disabled", detail = "NLT_RUN_TOKEN is not set" }, statusCode: 503);

    var supplied = req.Headers.Authorization.ToString();
    var expected = "Bearer " + runToken;
    if (!CryptographicOperations.FixedTimeEquals(Encoding.UTF8.GetBytes(supplied), Encoding.UTF8.GetBytes(expected)))
        return Results.Json(new { error = "unauthorized" }, statusCode: 401);

    if (req.ContentLength is > MaxBodyBytes)
        return Results.Json(new { error = "payload_too_large" }, statusCode: 413);
    try
    {
        using var doc = await JsonDocument.ParseAsync(req.Body);
    }
    catch (JsonException)
    {
        return Results.Json(new { error = "invalid_json" }, statusCode: 400);
    }

    // The engine has no request ingress yet. What /run does (drive a scenario, forward an intent to
    // IntentIngress, return a feed slice) is an architecture decision for Joshua, so say so rather than guess.
    return Results.Json(new { error = "not_implemented", detail = "engine ingress for /run is not defined (see docs/escalations)" }, statusCode: 501);
});

app.Run();

/// <summary>Runs the exported Godot server for the life of the host and stops it on shutdown.</summary>
sealed class GodotSupervisor(string executable) : BackgroundService
{
    private Process? _proc;
    private DateTime _started;

    public bool Running => _proc is { HasExited: false };
    public int? ExitCode => _proc is { HasExited: true } ? _proc.ExitCode : null;
    public double UptimeSeconds => Running ? (DateTime.UtcNow - _started).TotalSeconds : 0;

    protected override async Task ExecuteAsync(CancellationToken stop)
    {
        var psi = new ProcessStartInfo(executable)
        {
            // Output is inherited so it lands in the platform's runtime logs.
            UseShellExecute = false,
            WorkingDirectory = Path.GetDirectoryName(executable) ?? "/app/engine",
        };
        foreach (var a in new[] { "--headless", "--audio-driver", "Dummy" })
            psi.ArgumentList.Add(a);

        try
        {
            _proc = Process.Start(psi);
        }
        catch (Exception ex) when (ex is System.ComponentModel.Win32Exception or InvalidOperationException)
        {
            // Stay up so /health can report engine_down (503) and the cause is in the logs.
            Console.Error.WriteLine($"Godot server failed to start: {ex.Message}");
            return;
        }
        if (_proc is null) return;
        _started = DateTime.UtcNow;
        try { await _proc.WaitForExitAsync(stop); }
        catch (OperationCanceledException) { }
    }

    public override async Task StopAsync(CancellationToken cancellationToken)
    {
        if (_proc is { HasExited: false })
        {
            _proc.Kill(entireProcessTree: true);
            await _proc.WaitForExitAsync(cancellationToken);
        }
        await base.StopAsync(cancellationToken);
    }
}
