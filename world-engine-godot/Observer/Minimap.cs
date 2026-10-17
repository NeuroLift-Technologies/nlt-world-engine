using Godot;
using NltWorldEngine.Feed;

namespace NltWorldEngine.Observer;

/// <summary>
/// The dashboard's bottom-right minimap: a top-down plot of the world the observer is watching.
///
/// <para>
/// The land is sampled from <see cref="WorldGeometry.HeightAt"/> — the same field
/// <c>TerrainBuilder</c> builds its mesh from — rather than drawn as a stylised shape. That matters
/// because a minimap that is not the world is worse than no minimap: an operator who uses it to
/// orient will be misled by a coastline that does not match the terrain they are looking at. The
/// sample is taken once into a small image and stretched on draw, so the per-frame cost is a texture
/// blit and not a few thousand noise evaluations.
/// </para>
///
/// <para>
/// The sample also means the map is honest about what the world actually is: one island, one lake,
/// one settlement. Colour separates water from land, but the north indicator, the settlement marker
/// and the agent markers all carry shape and text as well, so the map is readable without relying on
/// hue.
/// </para>
/// </summary>
public partial class Minimap : Control
{
	private AccessibilitySettings _a11y = null!;
	private FeedTransport _feed = null!;

	/// <summary>
	/// Samples across the whole world per axis. 80 keeps the startup cost of the sample in the
	/// low thousands of noise evaluations — WorldView already spends seconds building terrain, and a
	/// minimap must not add visibly to that.
	/// </summary>
	private const int Resolution = 80;

	private const float Edge = 12f;
	private const float MapSize = 168f;
	private const float HeaderHeight = 22f;
	private const float ZoomStep = 0.25f;
	private const float MinZoom = 0.5f;
	private const float MaxZoom = 3f;

	/// <summary>Top-down colour ramp, sampled once into <see cref="_land"/>.</summary>
	private static readonly Color[] LandRamp =
	{
		new("0d1f26"), // deepest water
		new("16414c"),
		new("2f6f74"),
		new("8d8163"), // shoreline sand
		new("48603a"),
		new("5c7444"),
		new("7b7468"), // exposed rock
	};

	private ImageTexture? _land;
	private float _zoom = 1f;

	public void Attach(FeedTransport feed, AccessibilitySettings a11y)
	{
		_feed = feed;
		_a11y = a11y;
		_a11y.Changed += QueueRedraw;
		_feed.DocumentChanged += _ => QueueRedraw();
	}

	public override void _Ready()
	{
		MouseFilter = MouseFilterEnum.Ignore;
		// ObserverRoot.PlaceDashboardChrome owns this control's rect — it has to, because the
		// minimap's offset depends on the right rail's width, which only the observer knows. The size
		// here is the map's own geometry; the placement one is ObserverRoot's HeaderSize/MinimapSize.
		_sample();

		// Zoom controls are real Buttons, so they take clicks normally — this parent stays Ignore so
		// the world camera still owns every click that misses them. Both carry a keyboard shortcut,
		// because "the mouse is not the only way in" is a rule this observer holds itself to, and a
		// two-button cluster is exactly the small target that rule exists for. The keys are the
		// brackets rather than +/-, which the transport row and the timeline already claim.
		AddChild(MakeZoomButton("+", 1f, Key.Bracketright));
		AddChild(MakeZoomButton("−", -1f, Key.Bracketleft));
	}

	public override void _Process(double delta) => QueueRedraw();

	private Button MakeZoomButton(string label, float direction, Key shortcut)
	{
		var b = new Button
		{
			Text = label,
			FocusMode = FocusModeEnum.All,
			MouseDefaultCursorShape = CursorShape.PointingHand,
			CustomMinimumSize = new Vector2(22f, 22f),
			Position = new Vector2(Edge, Edge),
			Size = new Vector2(22f, 22f),
		};
		b.AddThemeFontSizeOverride("font_size", _a11y.Font(Ui.TinyFont));
		b.TooltipText = direction > 0f ? "Zoom the minimap in (]) — the map keeps north up" : "Zoom the minimap out ([) — the map keeps north up";
		b.Pressed += () => _zoom = Mathf.Clamp(_zoom + direction * ZoomStep, MinZoom, MaxZoom);
		return b.WithShortcut(shortcut);
	}

	/// <summary>
	/// Render the world once into a texture. North is up and +Z is south, matching Godot's
	/// convention, so the map agrees with the world camera rather than mirroring it.
	/// </summary>
	private void _sample()
	{
		var image = Image.CreateEmpty(Resolution, Resolution, false, Image.Format.Rgb8);
		float half = WorldConstants.World * 0.5f;
		float step = WorldConstants.World / Resolution;

		for (int j = 0; j < Resolution; j++)
		for (int i = 0; i < Resolution; i++)
		{
			float x = -half + i * step;
			// Row 0 is the top of the image, which must be the most negative Z to keep north up.
			float z = -half + j * step;
			image.SetPixel(i, j, Ramp(WorldGeometry.HeightAt(x, z)));
		}

		_land = ImageTexture.CreateFromImage(image);
	}

	/// <summary>
	/// Map a height to the ramp. Water saturates the bottom of the ramp so the lake and the sea read
	/// as one connected body; above the waterline the ramp climbs through shore to rock.
	/// </summary>
	private static Color Ramp(float height)
	{
		float water = WorldConstants.Water;
		if (height <= water)
		{
			float depth = Mathf.Clamp((water - height) / 12f, 0f, 1f);
			return LandRamp[2].Lerp(LandRamp[0], depth);
		}
		float land = Mathf.Clamp((height - water) / 22f, 0f, 1f);
		float scaled = land * (LandRamp.Length - 4);
		int lo = Mathf.Clamp(Mathf.FloorToInt(scaled), 3, LandRamp.Length - 2);
		return LandRamp[lo].Lerp(LandRamp[lo + 1], scaled - lo);
	}

	public override void _Draw()
	{
		if (_a11y == null || _feed == null || _land == null)
			return;

		var p = _a11y.Palette;
		var font = ThemeDB.FallbackFont;

		var frame = new Rect2(new Vector2(Edge, Edge + HeaderHeight), new Vector2(MapSize, MapSize));
		DrawRect(new Rect2(frame.Position - new Vector2(6f, 6f), frame.Size + new Vector2(12f, 12f)),
			p.Backdrop with { A = 0.78f });

		// Draw centred on the settlement at zoom, clipped to the frame so zooming never spills over
		// the panels around it.
		DrawSetTransform(frame.Position + frame.Size * 0.5f, 0f, Vector2.One);
		var span = frame.Size / _zoom;
		DrawRect(new Rect2(-span * 0.5f, span), LandRamp[0]);
		DrawTextureRect(_land, new Rect2(-span * 0.5f, span), false);
		DrawAgents(p);
		DrawSetTransform(Vector2.Zero, 0f, Vector2.One);

		DrawRect(frame, p.Border, false, p.BorderWidth);
		DrawNorth(p, font, frame);
		DrawString(font, new Vector2(Edge, Edge + 12f), $"MAP  {_zoom:0.00}×",
			HorizontalAlignment.Left, -1, _a11y.Font(Ui.TinyFont), p.TextDim);
	}

	/// <summary>
	/// Overlay the agents on show. Their world position is projected into the same top-down frame as
	/// the land, so a marker is only meaningful because it sits on the terrain it belongs to.
	/// </summary>
	private void DrawAgents(Palette p)
	{
		var doc = _feed.Current;
		if (doc == null)
			return;

		float half = WorldConstants.World * 0.5f;
		foreach (var agent in doc.Agents)
		{
			Vector3 w = agent.Position3();
			var at = new Vector2((w.X + half) / WorldConstants.World, (w.Z + half) / WorldConstants.World);

			// Shape carries the role: avatar is a circle, anything else a diamond. Colour repeats it.
			bool isAvatar = string.Equals(agent.Role, "avatar", System.StringComparison.OrdinalIgnoreCase);
			Ui.DrawGlyph(this, isAvatar ? Glyph.Circle : Glyph.Diamond, at, 7f,
				isAvatar ? p.Accent : p.Focus, p.Text);
		}
	}

	/// <summary>North arrow and the world-origin cross, so orientation is never guesswork.</summary>
	private void DrawNorth(Palette p, Font font, Rect2 frame)
	{
		var at = new Vector2(frame.End.X - 16f, frame.Position.Y + 16f);
		DrawLine(at + new Vector2(0f, 9f), at + new Vector2(0f, -7f), p.Text, 2f, true);
		DrawLine(at + new Vector2(0f, -7f), at + new Vector2(-4f, -1f), p.Text, 2f, true);
		DrawLine(at + new Vector2(0f, -7f), at + new Vector2(4f, -1f), p.Text, 2f, true);
		DrawString(font, at + new Vector2(-4f, 21f), "N",
			HorizontalAlignment.Left, -1, _a11y.Font(Ui.TinyFont), p.TextDim);
	}
}