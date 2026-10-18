using System;
using Godot;

namespace NltWorldEngine;

/// <summary>
/// The rules of an engine-owned scene transition (AGENT-LOOP-002 T3), kept free of the scene tree so
/// the harness checks them directly. <c>Main</c> runs the transition; this decides whether one may
/// start and where the avatar lands.
/// </summary>
public static class SceneTransitRules
{
	/// <summary>
	/// Why a doorway cannot be used right now, or null when it can. Checked at ingress, before the
	/// avatar walks: a refusal is reported as the intent's rejection and the avatar is not moved.
	/// </summary>
	/// <param name="link">Where the doorway leads.</param>
	/// <param name="interiorLevelExists">Whether a level can be loaded for an interior scene id.</param>
	/// <param name="worldPortalCount">How many building doorways the open world has.</param>
	/// <param name="pinnedSceneId">The <c>--scene</c> capture pin, or null.</param>
	/// <param name="busy">True while another transition is still running.</param>
	public static string? Check(PortalLink link, Func<string, bool> interiorLevelExists, int worldPortalCount,
		string? pinnedSceneId, bool busy)
	{
		if (busy)
			return "already moving between scenes";
		if (pinnedSceneId != null)
			return $"a --scene capture pin ('{pinnedSceneId}') holds the view; scene transitions are off";
		if (!SceneCatalog.TryKindFor(link.TargetSceneId, out string kind))
			return $"doorway leads to unknown scene '{link.TargetSceneId}'";
		if (link.BuildingIndex < 0 || link.BuildingIndex >= worldPortalCount)
			return $"doorway belongs to unknown building {link.BuildingIndex}";
		if (kind == SceneCatalog.InteriorKind && !interiorLevelExists(link.TargetSceneId))
			return $"no interior level for '{link.TargetSceneId}'";
		return null;
	}

	/// <summary>
	/// Where an avatar entering a room stands: the room's exit anchor, just inside the doorway, facing
	/// into the room. The room's <see cref="Portal.Facing"/> points out of it.
	/// </summary>
	public static (Vector3 Position, Vector3 Facing) IndoorArrival(Portal roomExit)
		=> (roomExit.Position - roomExit.Facing * SceneAnchorSets.ExitApproachDepth, -roomExit.Facing);

	/// <summary>
	/// Where an avatar leaving a room stands: its building's <see cref="Portal.EntryPoint"/>, outside
	/// the door, facing away from it.
	/// </summary>
	public static (Vector3 Position, Vector3 Facing) OutdoorArrival(Portal buildingDoor)
		=> (buildingDoor.EntryPoint, buildingDoor.Facing);
}
