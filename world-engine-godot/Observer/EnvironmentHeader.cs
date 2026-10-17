using Godot;
using NltWorldEngine.Feed;

namespace NltWorldEngine.Observer;

/// <summary>
/// The dashboard's environment header: the top-right strip of status chips.
///
/// <para>
/// Four chips, and the rule that governs all of them is that each one states something the running
/// process can actually prove. A dashboard that says "Persistent World" over a paused replay of a
/// fixture is decoration dressed as telemetry, and the observer's audience is people who will read
/// it as telemetry. So every chip here derives its value from live state — the document on show, the
/// agent count in it, the physics backend the project is configured for, and the scenario the feed
/// names — and prints the real value next to the claim.
/// </para>
///
/// <para>
/// Drawn rather than composed from controls because it floats over the 3D view and must not take
/// layout space from it. Like the rest of the observer it is palette-only (no ad-hoc hex), carries a
/// glyph as well as a colour so the indicator does not depend on hue, and honours all three reading
/// levels and high contrast. It never flashes, and under reduced motion it does not animate at all.
/// </para>
/// </summary>
public partial class EnvironmentHeader : Control
{
	private AccessibilitySettings _a11y = null!;
	private FeedTransport _feed = null!;

	/// <summary>
	/// Mirrors <see cref="ObserverRoot"/>'s top-bar height so the strip sits below the bar rather than
	/// reading as part of it. Kept as a literal because the bar's height is set by its own contents.
	/// </summary>
	private const float TopBarHeight = 44f;

	private const float Margin = 12f;
	private const float ChipGap = 8f;
	private const float ChipPad = 10f;
	private const float ChipHeight = 46f;
	private const float IconSize = 11f;

	public void Attach(FeedTransport feed, AccessibilitySettings a11y)
	{
		_feed = feed;
		_a11y = a11y;

		// Purely informational: it must never intercept a click meant for the world camera, which
		// is why this is Ignore rather than Pass. WorldView._Input runs ahead of GUI processing, so
		// a Stop here would fight the orbit as well as the click.
		MouseFilter = MouseFilterEnum.Ignore;
		SetAnchorsAndOffsetsPreset(LayoutPreset.TopRight);
		_a11y.Changed += QueueRedraw;
		_feed.StatusChanged += QueueRedraw;
		_feed.DocumentChanged += _ => QueueRedraw();
	}

	public override void _Ready()
	{
		MouseFilter = MouseFilterEnum.Ignore;
		// ObserverRoot.PlaceDashboardChrome is the single authority on this control's rect: it sets
		// the anchors and the offsets, and a Control's size is derived from the two. Anything set
		// here would be overwritten, and anything read back here after placement would already be the
		// moved box rather than the intended one.
	}

	public override void _Process(double delta) => QueueRedraw();

	/// <summary>One chip: a claim, the live value behind it, and the shape that carries the status.</summary>
	public readonly record struct Chip(Glyph Glyph, Color Tint, string Claim, string Value);

	public override void _Draw()
	{
		if (_a11y == null || _feed == null)
			return;

		var p = _a11y.Palette;
		var doc = _feed.Current;
		var font = ThemeDB.FallbackFont;
		int claimSize = _a11y.Font(Ui.TinyFont);
		int valueSize = _a11y.Font(Ui.SmallFont);

		var chips = new[]
		{
			// Claim + the fact that makes it true or false. Every value below is read from live state.
			new Chip(Glyph.Hexagon, p.Accent, "Persistent World",
				$"seed {WorldConstants.Seed}"),
			new Chip(Glyph.Circle, p.Pass, "Multi-Agent",
				doc == null ? "no document" : $"{doc.Agents.Count} agent{(doc.Agents.Count == 1 ? "" : "s")}"),
			new Chip(Glyph.Square, p.Cool, "Real-Time Physics",
				PhysicsBackend()),
			new Chip(Glyph.Diamond, p.Focus, "Scenario",
				doc?.Scene.SceneLabel() ?? "-"),
		};

		// Measure the strip before drawing it, and lay the chips out left to right from x = 0. The
		// control is exactly as wide as the chips need (ObserverRoot sizes it from this same
		// measurement), so nothing is clipped and nothing overflows into the rail beside it.
		var measured = Measure(chips, font, claimSize, valueSize);

		float x = 0f;
		foreach (var chip in chips)
		{
			DrawChip(chip, new Vector2(x, TopBarHeight + Margin), p, font, claimSize, valueSize);
			x += ChipWidth(chip, font, claimSize, valueSize) + ChipGap;
		}

		// Reported rather than assumed: if the chips ever need more room than the strip was given,
		// the next placement sizes from this number instead of silently clipping the last chip.
		ContentWidth = measured;
	}

	/// <summary>Width the chips actually needed on the last draw, in pixels.</summary>
	public float ContentWidth { get; private set; }

	/// <summary>Width of one chip: the wider of its two lines, plus the icon and its padding.</summary>
	private static float ChipWidth(Chip chip, Font font, int claimSize, int valueSize)
	{
		float claimW = font.GetStringSize(chip.Claim, HorizontalAlignment.Left, -1, claimSize).X;
		float valueW = font.GetStringSize(chip.Value, HorizontalAlignment.Left, -1, valueSize).X;
		return Mathf.Max(claimW, valueW) + ChipPad * 2f + IconSize * 2f + 6f;
	}

	/// <summary>Total width the chips need, including the gaps between them.</summary>
	public static float Measure(Chip[] chips, Font font, int claimSize, int valueSize)
	{
		float total = ChipGap * (chips.Length - 1);
		foreach (var chip in chips)
			total += ChipWidth(chip, font, claimSize, valueSize);
		return total;
	}

	/// <summary>Draw one chip and return the x it ends at.</summary>
	private void DrawChip(Chip chip, Vector2 at, Palette p, Font font, int claimSize, int valueSize)
	{
		var rect = new Rect2(at, new Vector2(ChipWidth(chip, font, claimSize, valueSize), ChipHeight));

		DrawRect(rect, p.Backdrop with { A = 0.78f });
		DrawRect(rect, p.Border, false, p.BorderWidth);

		// Shape first, colour second: the glyph is what survives a colour vision deficiency, and the
		// two together are still only reinforcement for the text beside them.
		var icon = new Vector2(rect.Position.X + ChipPad + IconSize, rect.Position.Y + ChipHeight * 0.5f);
		Ui.DrawGlyph(this, chip.Glyph, icon, IconSize, chip.Tint, p.Text);

		var textX = icon.X + IconSize + 6f;
		DrawString(font, new Vector2(textX, rect.Position.Y + 16f), chip.Claim,
			HorizontalAlignment.Left, -1, claimSize, p.TextMuted);
		DrawString(font, new Vector2(textX, rect.Position.Y + 33f), chip.Value,
			HorizontalAlignment.Left, -1, valueSize, p.Text);
	}

	/// <summary>
	/// The physics backend the project is configured for, read from the live project settings.
	///
	/// PHYS-001 records that this is Jolt. Reading the setting rather than hard-coding the string
	/// means the chip cannot quietly disagree with the engine if the backend is ever changed, and it
	/// is honest about a project setting that is absent rather than asserting a default it did not
	/// find.
	/// </summary>
	private static string PhysicsBackend()
	{
		string backend = ProjectSettings.GetSetting("physics/3d/physics_engine", "").AsString();
		return backend.Length == 0 ? "default" : backend.Replace(" Physics", "");
	}
}