using System;
using System.Collections.Generic;

namespace NltWorldEngine;

/// <summary>
/// The anchors that exist in each scene (AGENT-LOOP-002 T2). Perception and the execution re-check
/// ask for the avatar's own scene, so an agent in a room never sees the plaza, and one outside never
/// sees a room's exit. Interiors are instanced at the world origin, so mixing the sets would put
/// open-world anchors "inside" a room.
///
/// The open world's set is fixed. An interior's set is its exit, which is known only once the level
/// is loaded (<see cref="WorldView"/> finds the door in the level's own geometry), so it is built on
/// first request from the shown interior's exit portal and kept.
/// </summary>
public sealed class SceneAnchorSets
{
	/// <summary>
	/// How far inside the room the exit's approach point sits, measured from the doorway along its
	/// inward axis. Clear of the wall's collision; the doorway itself is left open by
	/// <see cref="InteriorPhysicalBoundary"/>, which skips door proxies.
	/// </summary>
	public const float ExitApproachDepth = 1.6f;

	private readonly IReadOnlyList<TaskAnchor> _openWorld;
	private readonly Func<string, Portal?> _shownExitFor;
	private readonly Dictionary<string, TaskAnchor> _exits = new();

	/// <param name="openWorld">The open world's anchors (<see cref="WorldAnchorBuilder.BuildOpenWorld"/>).</param>
	/// <param name="shownExitFor">The exit portal of <c>sceneId</c> if that interior is the one loaded,
	/// else null.</param>
	public SceneAnchorSets(IReadOnlyList<TaskAnchor> openWorld, Func<string, Portal?> shownExitFor)
	{
		_openWorld = openWorld;
		_shownExitFor = shownExitFor;
	}

	/// <summary>Stable id of an interior's exit anchor, e.g. <c>exit_personal_1</c>.</summary>
	public static string ExitIdFor(string sceneId) => $"exit_{sceneId}";

	/// <summary>
	/// The anchors in <paramref name="sceneId"/>: the open world's set, or a single exit for an
	/// interior whose exit is known. Empty for an unknown scene, or an interior not yet loaded.
	/// </summary>
	public IReadOnlyList<TaskAnchor> For(string sceneId)
	{
		if (SceneCatalog.IsOpenWorld(sceneId))
			return _openWorld;
		if (!SceneCatalog.TryBuildingIndexFor(sceneId, out int building))
			return Array.Empty<TaskAnchor>();
		if (!_exits.TryGetValue(sceneId, out TaskAnchor? exit))
		{
			if (_shownExitFor(sceneId) is not { } portal)
				return Array.Empty<TaskAnchor>();
			exit = ExitAnchor(sceneId, building, portal);
			_exits[sceneId] = exit;
		}
		if (!_furniture.TryGetValue(sceneId, out var furniture) || furniture.Count == 0)
			return new[] { exit };
		var all = new List<TaskAnchor>(furniture.Count + 1) { exit };
		all.AddRange(furniture);
		return all;
	}

	private readonly Dictionary<string, IReadOnlyList<TaskAnchor>> _furniture = new();

	/// <summary>True once <see cref="SetFurniture"/> has run for <paramref name="sceneId"/>.</summary>
	public bool HasFurniture(string sceneId) => _furniture.ContainsKey(sceneId);

	/// <summary>
	/// Register a room's furniture anchors (AGENT-LOOP-002 T5), built from the loaded level once its
	/// collision is live. Each building's room keeps its own set, so a chair taken in one home is free
	/// in the next.
	/// </summary>
	public void SetFurniture(string sceneId, IReadOnlyList<TaskAnchor> furniture) => _furniture[sceneId] = furniture;

	/// <summary>
	/// The exit anchor for a room: <see cref="ExitApproachDepth"/> inside the doorway (the portal's
	/// <see cref="Portal.Facing"/> points out of the room), leading back to the open world through
	/// the building the room belongs to.
	/// </summary>
	public static TaskAnchor ExitAnchor(string sceneId, int buildingIndex, Portal exitPortal) =>
		new(ExitIdFor(sceneId), "Exit", AffordanceAxes.Neutral)
		{
			// The same spot an entering avatar is placed at, so an avatar that has just come in is
			// already standing at the exit.
			Position = SceneTransitRules.IndoorArrival(exitPortal).Position,
			Link = new PortalLink(SceneCatalog.OpenWorldId, buildingIndex),
		};
}
