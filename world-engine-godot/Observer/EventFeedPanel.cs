using System;
using System.Collections.Generic;
using Godot;
using NltWorldEngine.Feed;

namespace NltWorldEngine.Observer;

/// <summary>
/// The dashboard's Recent Events list: timestamped rows of what actually happened, newest first.
///
/// <para>
/// The panel has no vocabulary of its own. Every row's wording comes from
/// <see cref="PlainLanguage.EventWord"/>, its shape from <see cref="PlainLanguage.EventGlyph"/> and
/// its colour from <see cref="PlainLanguage.EventColour"/> — the same mapping the timeline already
/// draws with, so an event looks the same wherever it appears. That is also what keeps the panel
/// honest: it cannot describe an event the feed vocabulary has no word for, because it has nowhere
/// to put one.
/// </para>
///
/// <para>
/// Rows accumulate rather than replacing per document. The feed advances at roughly 1 Hz while an
/// operator reads at neither rate, so a panel that swapped its contents on every document would only
/// ever show the last few seconds. The newest row is at the top, and the rows belonging to the
/// document on show are marked.
/// </para>
/// </summary>
public partial class EventFeedPanel : ObserverPanel
{
	/// <summary>Rows drawn. Older events fall off the bottom; the feed itself still holds them.</summary>
	private const int MaxRows = 40;

	/// <summary>
	/// How many rows are held in memory beyond what is drawn. Bounded so a long session cannot grow
	/// the list without limit; the feed remains the record of everything.
	/// </summary>
	private const int MaxHeld = 160;

	private readonly List<FeedEvent> _rows = new();
	private int _lastTick = -1;

	public override string PanelTitle => "Recent events";

	/// <summary>
	/// One line of context in the header: how many events are held, so the reader can tell a short
	/// feed from a trimmed one rather than guessing from the row count.
	/// </summary>
	protected override string Subtitle() =>
		_rows.Count == 0 ? "none yet" : $"{_rows.Count} held";

	protected override void Populate(VBoxContainer body)
	{
		Harvest();

		if (_rows.Count == 0)
		{
			body.AddChild(Ui.Paragraph(
				"No events yet. They appear here as the feed reports them.",
				A11y.Font(Ui.SmallFont), P.TextMuted));
			return;
		}

		// Newest first. The list is append-ordered, so walk it backwards rather than reversing.
		int shown = 0;
		for (int i = _rows.Count - 1; i >= 0 && shown < MaxRows; i--, shown++)
		{
			var row = _rows[i];
			var line = Ui.InlineRow(6);

			var icon = new RowIcon
			{
				Glyph = PlainLanguage.EventGlyph(row.Kind),
				Tint = PlainLanguage.EventColour(P, row.Kind),
				CustomMinimumSize = new Vector2(14f, 0),
				MouseFilter = MouseFilterEnum.Ignore,
			};
			line.AddChild(icon);

			string who = AgentName(row.AgentId);
			string text = PlainLanguage.EventWord(row.Kind);
			if (Level != ReadingLevel.Simple)
				text += $" — {who}";
			// Coach is the level that says whether the Aide's help actually landed, so that is where
			// the outcome belongs. Technical shows the raw tick beside the plain-language offset.
			if (Level == ReadingLevel.Coach && row.Helped.HasValue)
				text += $" ({PlainLanguage.OutcomeWord(row.Helped)})";

			var body2 = Ui.Text(text, A11y.Font(Ui.SmallFont), P.Text);
			body2.VerticalAlignment = VerticalAlignment.Center;
			body2.TooltipText = who;
			line.AddChild(body2);

			bool current = row.Tick == _lastTick;
			string stamp = Level == ReadingLevel.Technical
				? $"t{row.Tick}"
				: PlainLanguage.Ago(Math.Max(0, _lastTick - row.Tick));

			// Freshness is a position and a mark, never a colour: newest is the top row, and rows
			// from the document on show carry a leading dot.
			line.AddChild(Ui.Inline(current ? $"● {stamp}" : stamp,
				A11y.Font(Ui.TinyFont), current ? P.Text : P.TextMuted));

			body.AddChild(line);
		}
	}

	/// <summary>
	/// Fold events we have not shown yet into the running list.
	///
	/// A tick that goes backwards means the feed was restarted or the operator stepped to an earlier
	/// document. Restarting clears the list, because those are new events from a new run and keeping
	/// the old ones would present two histories as one; stepping back does not, because those events
	/// have already been read.
	/// </summary>
	private void Harvest()
	{
		var doc = Doc;
		if (doc == null)
			return;

		if (_lastTick >= 0 && doc.Tick < _lastTick)
		{
			_rows.Clear();
			_lastTick = -1;
		}

		foreach (var e in doc.Events)
		{
			if (e.Tick <= _lastTick)
				continue;
			_rows.Add(e);
			_lastTick = Math.Max(_lastTick, e.Tick);
		}

		while (_rows.Count > MaxHeld)
			_rows.RemoveAt(0);
	}

	/// <summary>The agent's display name when the document carries one, else the raw id.</summary>
	private string AgentName(string agentId)
	{
		var agent = Doc?.Agent(agentId);
		if (agent == null)
			return agentId;
		return string.IsNullOrEmpty(agent.Name) ? agentId : agent.Name;
	}
}

/// <summary>
/// A fixed-width cell that draws one <see cref="Glyph"/>. Event rows put a shape before the wording,
/// and this is the smallest thing that can do that without a themed control per row.
/// </summary>
public partial class RowIcon : Control
{
	/// <summary>Shape drawn at the centre. Shape, not colour, is what identifies the event kind.</summary>
	public Glyph Glyph { get; set; } = Glyph.Circle;

	/// <summary>Fill. Always paired with the shape and the wording beside it.</summary>
	public Color Tint { get; set; } = Colors.White;

	/// <summary>
	/// Outline. Defaults to the fill, matching how the timeline draws its event marks: these glyphs
	/// are small, and an outline in a second colour reads as a second, unrelated indicator rather
	/// than as the edge of the first one.
	/// </summary>
	public Color Outline { get; set; }

	public override void _Ready() => MouseFilter = MouseFilterEnum.Ignore;

	public override void _Draw()
	{
		Color outline = Outline.A <= 0f ? Tint : Outline;
		Ui.DrawGlyph(this, Glyph, new Vector2(Size.X * 0.5f, Size.Y * 0.5f), 5f, Tint, outline);
	}
}