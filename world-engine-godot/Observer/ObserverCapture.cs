using System;
using System.Collections.Generic;
using Godot;

namespace NltWorldEngine.Observer;

/// <summary>
/// Offscreen capture, for evidence rather than for the app.
///
/// Phase D is a visual deliverable, and "the panels compile" is not verification — the plan's own
/// history is a run of claims that turned out to be untrue when someone actually looked. This node
/// makes looking cheap and repeatable: run the project with a capture flag, get a PNG of the real
/// rendered observer at a chosen reading level.
///
/// It is inert unless the flag is present, and it never runs in normal play:
///
/// <code>
/// Godot_v4.7.2-stable_mono_win64.exe --path world-engine-godot -- --capture out.png --level technical
/// </code>
///
/// Args are read from <c>OS.GetCmdlineUserArgs()</c>, i.e. after a bare <c>--</c>, so the engine's
/// own switches are untouched.
/// </summary>
public partial class ObserverCapture : Node
{
    private string _path = "";
    private ReadingLevel _level = ReadingLevel.Simple;
    private int _frames = 90;
    private int _seen;
    private bool _done;
    private bool _selfTest;

    /// <summary>
    /// The replay bundle to load, from <c>--fixture</c>, or null for the observer's default.
    ///
    /// <para>
    /// <see cref="TryCreate"/> sets this, but <c>TryCreate</c> runs late — <c>Main._Ready</c> has
    /// already called <c>ObserverRoot.Attach</c>, which is what loads the default bundle. So the
    /// command line is also read here, directly, because the override has to be known before the
    /// first document is loaded rather than after. <see cref="TryCreate"/> still sets it, so the two
    /// cannot disagree: both read the same argument.
    /// </para>
    /// </summary>
    public static string? RequestedFixture { get; private set; } = FixtureFromCommandLine();

    /// <summary>Parse <c>--fixture &lt;res://path.json&gt;</c> from the user args, or null.</summary>
    private static string? FixtureFromCommandLine()
    {
        string? value = ValueAfter(OS.GetCmdlineUserArgs(), "--fixture");
        if (value == null)
            return null;
        // Accept a bare relative name as well as a full res:// path, because typing
        // --fixture stayalert-day.json is the obvious thing to try and a silent fallback to the
        // default would look like the flag did nothing.
        return value.Contains("://", StringComparison.Ordinal)
            ? value
            : $"res://fixtures/replay/{value}.json";
    }

    public static ObserverCapture? TryCreate(Node parent)
    {
        var args = OS.GetCmdlineUserArgs();
        bool selfTest = System.Array.IndexOf(args, "--selftest") >= 0;
        if (System.Array.IndexOf(args, "--capture") < 0 && !selfTest)
            return null;

        var capture = new ObserverCapture { Name = "ObserverCapture", _selfTest = selfTest };
        capture._path = ValueAfter(args, "--capture") ?? "";

        // Case-insensitive: the usage line documents `--level technical` in lower case, and
        // Enum.TryParse is case-sensitive by default, so the documented example silently stayed at
        // Simple.
        if (Enum.TryParse(ValueAfter(args, "--level"), ignoreCase: true, out ReadingLevel parsed))
            capture._level = parsed;

        if (int.TryParse(ValueAfter(args, "--frames"), out int f))
            capture._frames = Math.Max(1, f);

        // Read into the same static the property initialiser reads, so there is one source of truth for it
        // however the capture node happens to be created.
        RequestedFixture = ValueAfter(args, "--fixture") is string f0 ? FixtureFromCommandLine() : null;

        parent.AddChild(capture);
        return capture;
    }

    /// <summary>
    /// The argument following <paramref name="flag"/>, or null if the flag is absent or has no value.
    ///
    /// <para>
    /// One helper because every hand-written version of this got it subtly wrong the same way.
    /// <c>Array.IndexOf</c> returns <b>-1</b> for an absent flag, and <c>-1 + 1</c> is <c>0</c>, so
    /// the natural <c>if (at + 1 &lt; args.Length)</c> guard reads <c>args[0]</c> — some unrelated
    /// argument — as the flag's value. With <c>--fixture</c> that meant a plain <c>--selftest</c> run
    /// tried to open <c>res://fixtures/replay/--selftest.json</c>, reported a missing file, and laid
    /// the transport toolbar out one button wider than the window. The same shape sat in the
    /// <c>--capture</c>, <c>--level</c> and <c>--frames</c> reads below, where it happened to be
    /// harmless only because the value failed to parse.
    /// </para>
    /// </summary>
    internal static string? ValueAfter(string[] args, string flag)
    {
        int at = Array.IndexOf(args, flag);
        return at >= 0 && at + 1 < args.Length && args[at + 1].Length > 0 ? args[at + 1] : null;
    }

    /// <summary>Reading level to show, applied once the observer exists.</summary>
    public ReadingLevel RequestedLevel => _level;

    public override void _Ready()
    {
        if (_path.Length == 0 && !_selfTest)
        {
            GD.PushWarning("ObserverCapture: --capture given with no path; ignoring.");
            QueueFree();
        }
    }

    public override void _Process(double delta)
    {
        if (_done)
            return;
        if (++_seen < _frames)
            return;

        _done = true;
        if (_selfTest)
            SelfTest();
        else
            Save();
    }

    /// <summary>
    /// Assert the observer's layout invariants and report which controls have a non-mouse path.
    ///
    /// <para>
    /// It deliberately does <b>not</b> claim to test clicking. Synthetic mouse events do not reach
    /// Godot's GUI in this environment: a bare probe <c>Button</c> added outside the observer is
    /// equally unclickable, which means a click-based result says nothing about the observer and
    /// would be a false negative. Click behaviour is verified by a person; what is checked here is
    /// everything a machine can check honestly.
    /// </para>
    /// </summary>
    private void SelfTest()
    {
        var buttons = new System.Collections.Generic.List<Button>();
        Collect(GetTree().Root, buttons);
        Vector2 viewport = GetViewport().GetVisibleRect().Size;

        int problems = 0;
        int withoutShortcut = 0;

        foreach (var b in buttons)
        {
            if (!b.IsVisibleInTree())
                continue;

            Rect2 r = b.GetGlobalRect();
            if (r.Size.X < 4f || r.Size.Y < 4f)
            {
                problems++;
                GD.Print($"[selftest] FAIL  '{b.Text}' has no usable size ({r.Size})");
            }
            else if (r.Position.X < -1f || r.Position.Y < -1f
                     || r.End.X > viewport.X + 1f || r.End.Y > viewport.Y + 1f)
            {
                problems++;
                GD.Print($"[selftest] FAIL  '{b.Text}' sits outside the window: {r} in {viewport}");
            }

            if (b.Shortcut == null)
            {
                withoutShortcut++;
                GD.Print($"[selftest] WARN  '{b.Text}' has no keyboard shortcut");
            }
        }

        // The popup bug this replaced: a panel "opened" with a negative height and was invisible,
        // which reads as a dead button.
        var observer = FindObserver(GetTree().Root);
        if (observer == null)
        {
            GD.Print("[selftest] FAIL  ObserverRoot not found in the tree");
            problems++;
        }
        else
        {
            problems += observer.CheckPopups(viewport);
        }

        GD.Print($"[selftest] {buttons.Count} control(s); {withoutShortcut} without a keyboard shortcut");
        GD.Print($"[selftest] {(problems == 0 ? "LAYOUT OK" : problems + " LAYOUT PROBLEM(S)")}");
        GetTree().Quit(problems == 0 ? 0 : 1);
    }

    private static ObserverRoot? FindObserver(Node n)
    {
        foreach (var c in n.GetChildren())
        {
            if (c is ObserverRoot o)
                return o;
            var found = FindObserver(c);
            if (found != null)
                return found;
        }
        return null;
    }

    private static void Collect(Node n, System.Collections.Generic.List<Button> into)
    {
        foreach (var c in n.GetChildren())
        {
            if (c is Button b)
                into.Add(b);
            Collect(c, into);
        }
    }

    private async void Save()
    {
        // Wait for the frame to reach the screen, otherwise the texture read comes back empty.
        await ToSignal(RenderingServer.Singleton, RenderingServer.SignalName.FramePostDraw);

        var viewport = GetViewport();
        if (viewport == null)
        {
            GD.PushError("ObserverCapture: no viewport to capture.");
            GetTree().Quit(1);
            return;
        }

        var image = viewport.GetTexture()?.GetImage();
        if (image == null)
        {
            GD.PushError("ObserverCapture: viewport has no image.");
            GetTree().Quit(1);
            return;
        }

        string target = ProjectSettings.GlobalizePath(_path);
        var err = image.SavePng(target);
        if (err != Error.Ok)
        {
            GD.PushError($"ObserverCapture: could not write {target}: {err}");
            GetTree().Quit(1);
            return;
        }

        GD.Print($"ObserverCapture: wrote {target} ({image.GetWidth()}x{image.GetHeight()}) "
                 + $"at reading level {_level}");
        GetTree().Quit(0);
    }
}