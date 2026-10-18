using System;
using System.Collections.Generic;
using System.Linq;
using Godot;

namespace NltWorldEngine;

/// <summary>
/// The things inside a room an agent can sit on or use (AGENT-LOOP-002 T5), built from the level's own
/// meshes by object name — the same names <see cref="InteriorStyle"/> dresses. Engine-free: the caller
/// supplies the meshes and a probe that knows the room's collision, so the harness checks the rules
/// with a fake probe and <c>Main</c> runs them against the real level.
///
/// An anchor's <see cref="TaskAnchor.Position"/> is an approach point beside the object, clear of
/// collision — never the object's centre, which sits inside the level's UCX body and could not be
/// reached (the mistake the first open-world door anchors made). The centre is kept as
/// <see cref="TaskAnchor.FacePoint"/> for an agent using it to face.
/// </summary>
public static class InteriorAnchors
{
	/// <summary>One visible level mesh: its node name, and its world-space bounds centre and size.</summary>
	public sealed record LevelMesh(string Name, Vector3 Centre, Vector3 Size);

	private sealed record Rule(string Prefix, string Label, string[] Affords);

	private static readonly string[] Seat = { "sit" };
	private static readonly string[] Lounge = { "sit", "rest" };
	private static readonly string[] Use = { "use" };

	// First matching prefix wins, so a more specific prefix comes before a shorter one that also
	// matches it (DeskChair_ before Desk_). One mesh per object: the seat, the top or the body.
	private static readonly Rule[] Rules =
	{
		// Home
		new("Sofa_Base", "Sofa", Lounge),
		new("Bed_Mattress", "Bed", Lounge),
		new("Dining_Chair_Seat", "Chair", Seat),
		new("Stool_Seat", "Stool", Seat),
		new("Office_Chair_Seat", "Chair", Seat),
		new("Office_Desk", "Desk", Use),
		new("Kit_Counter_Top", "Kitchen counter", Use),
		new("Kit_Stove_Top", "Stove", Use),
		new("Kit_Fridge", "Fridge", Use),
		new("Bath_Sink_Counter", "Sink", Use),
		new("Washing_Machine", "Washing machine", Use),
		new("TV_Stand", "TV", Use),
		// Office
		new("WF_ChairSeat_", "Desk chair", Seat),
		new("WF_DeskTop_", "Desk", Use),
		new("WF_ConfChairSeat_", "Meeting chair", Seat),
		new("WF_ConfTable", "Meeting table", Use),
		new("WF_SofaSeat", "Sofa", Lounge),
		new("WF_Whiteboard", "Whiteboard", Use),
		// Café
		new("Cafe_Chair_", "Chair", Seat),
		new("Cafe_Counter_Top", "Counter", Use),
		new("Cafe_ServiceKiosk", "Order kiosk", Use),
		new("Cafe_Sofa_", "Sofa", Lounge),
		// Classroom
		new("Teacher_Desk", "Teacher's desk", Use),
		new("Teacher_Chair", "Teacher's chair", Seat),
		new("DeskChair_", "Desk chair", Seat),
		new("Desk_", "Desk", Use),
		new("Bookshelf_", "Bookshelf", Use),
		new("StudyChair_", "Study chair", Seat),
		new("StudyTable_", "Study table", Use),
	};

	/// <summary>Clearance kept between an object's bounds and the approach point, in metres.</summary>
	public const float ApproachGap = 0.6f;

	/// <summary>The label and verbs for a level mesh, or null when it is not an anchor-worthy object.</summary>
	public static (string Label, IReadOnlyList<string> Affords)? Classify(string meshName)
	{
		if (meshName.StartsWith("UCX_", StringComparison.Ordinal))
			return null;
		foreach (var rule in Rules)
			if (meshName.StartsWith(rule.Prefix, StringComparison.Ordinal))
				return (rule.Label, rule.Affords);
		return null;
	}

	/// <summary>
	/// The candidate approach points around an object, best first: the four sides and four corners at
	/// <see cref="ApproachGap"/> beyond its bounds, ordered by how directly they face
	/// <paramref name="roomCentre"/>, so a chair against a wall is approached from the room.
	/// </summary>
	public static IEnumerable<Vector3> Candidates(Vector3 centre, Vector3 size, Vector3 roomCentre)
	{
		float hx = size.X * 0.5f + ApproachGap, hz = size.Z * 0.5f + ApproachGap;
		var toRoom = new Vector2(roomCentre.X - centre.X, roomCentre.Z - centre.Z);
		var offsets = new[]
		{
			new Vector2(hx, 0f), new Vector2(-hx, 0f), new Vector2(0f, hz), new Vector2(0f, -hz),
			new Vector2(hx, hz), new Vector2(hx, -hz), new Vector2(-hx, hz), new Vector2(-hx, -hz),
		};
		return offsets
			.OrderByDescending(o => toRoom.LengthSquared() > 0.0001f ? o.Normalized().Dot(toRoom.Normalized()) : 0f)
			.Select(o => new Vector3(centre.X + o.X, centre.Y, centre.Z + o.Y));
	}

	/// <summary>
	/// Build a room's furniture anchors. <paramref name="probe"/> is asked whether an agent could
	/// stand at a candidate point and reach the object from there; it returns the point on the floor,
	/// or null. Objects with no usable candidate get no anchor (and are reported by the caller).
	///
	/// Ids are the label in lower case plus a running number in node-name order (<c>chair_3</c>), so
	/// they are stable across loads, readable to a model, and never equal a level node's name — target
	/// resolution checks anchors first anyway (<c>AgentLoopDriver.ResolveTarget</c>). Meshes that share a
	/// position (the office level duplicates some meeting chairs) become one anchor.
	/// </summary>
	public static List<TaskAnchor> Build(IEnumerable<LevelMesh> meshes, Func<Vector3, Vector3, Vector3?> probe,
		List<string>? unplaced = null)
	{
		var classified = meshes
			.Select(m => (Mesh: m, Rule: Classify(m.Name)))
			.Where(x => x.Rule != null)
			.OrderBy(x => x.Mesh.Name, StringComparer.Ordinal)
			.ToList();
		if (classified.Count == 0)
			return new List<TaskAnchor>();

		var roomCentre = new Vector3(
			classified.Average(x => x.Mesh.Centre.X), 0f, classified.Average(x => x.Mesh.Centre.Z));
		var anchors = new List<TaskAnchor>();
		var counts = new Dictionary<string, int>();
		var seen = new List<Vector3>();
		foreach (var (mesh, rule) in classified)
		{
			if (seen.Any(p => p.DistanceTo(mesh.Centre) < 0.05f))
				continue;
			seen.Add(mesh.Centre);

			Vector3? approach = null;
			foreach (var candidate in Candidates(mesh.Centre, mesh.Size, roomCentre))
				if ((approach = probe(candidate, mesh.Centre)) != null)
					break;
			if (approach == null)
			{
				unplaced?.Add(mesh.Name);
				continue;
			}

			var (label, affords) = rule!.Value;
			string slug = label.ToLowerInvariant().Replace("'", "").Replace(' ', '_');
			counts[slug] = counts.TryGetValue(slug, out int n) ? n + 1 : 1;
			anchors.Add(new TaskAnchor($"{slug}_{counts[slug]}", label, AffordanceAxes.Neutral)
			{
				Position = approach.Value,
				Affords = affords,
				Kind = "object",
				FacePoint = mesh.Centre,
			});
		}
		return anchors;
	}
}
