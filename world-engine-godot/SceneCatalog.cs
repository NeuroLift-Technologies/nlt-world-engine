using System;
using System.Globalization;

namespace NltWorldEngine;

/// <summary>
/// The one mapping from a scene id to its kind (AGENT-LOOP-002 T1). Perception, the viewer and the
/// fall reset all ask here instead of guessing from the id's spelling.
///
/// There are two shapes of id. <see cref="OpenWorldId"/> is the procedural island. Interiors are
/// <c>&lt;prefix&gt;_&lt;n&gt;</c>, where the prefix is one of the four level kinds and <c>n</c> is the
/// building's index + 1, exactly as <see cref="SettlementBuilder.SceneIdFor(SettlementBuilder.BuildingKind, int)"/>
/// writes them (<c>personal_1</c>, <c>workplace_7</c>, …). Anything else is unknown and is rejected,
/// not guessed: the old <c>Contains("open")</c> test called <c>workplace_open</c> the open world and any
/// typo an interior.
/// </summary>
public static class SceneCatalog
{
	/// <summary>Scene id of the procedural open world, as the replay fixtures write it.</summary>
	public const string OpenWorldId = "open_world";

	/// <summary>Contract scene kind for the open world (<c>nlt.agent-loop.v1</c> §2).</summary>
	public const string OpenWorldKind = "open_world";

	/// <summary>Contract scene kind for a building's room (<c>nlt.agent-loop.v1</c> §2).</summary>
	public const string InteriorKind = "interior";

	// The level prefixes SettlementBuilder.SceneIdFor emits, one per building kind. The harness
	// checks every id the settlement generates against this list, so the two cannot drift apart.
	private static readonly string[] InteriorPrefixes = { "personal", "workplace", "social", "academic" };

	/// <summary>True for the open-world id only.</summary>
	public static bool IsOpenWorld(string? sceneId) => sceneId == OpenWorldId;

	/// <summary>
	/// Resolve <paramref name="sceneId"/> to its contract kind. Returns false, with an empty
	/// <paramref name="kind"/>, for an id that is neither the open world nor a well-formed interior.
	/// </summary>
	public static bool TryKindFor(string? sceneId, out string kind)
	{
		kind = "";
		if (sceneId == OpenWorldId)
		{
			kind = OpenWorldKind;
			return true;
		}
		if (string.IsNullOrEmpty(sceneId))
			return false;

		int underscore = sceneId.LastIndexOf('_');
		if (underscore <= 0 || underscore == sceneId.Length - 1)
			return false;
		if (Array.IndexOf(InteriorPrefixes, sceneId[..underscore]) < 0)
			return false;
		if (!int.TryParse(sceneId[(underscore + 1)..], NumberStyles.None, CultureInfo.InvariantCulture, out int number)
			|| number < 1)
			return false;

		kind = InteriorKind;
		return true;
	}

	/// <summary>
	/// The settlement building an interior belongs to: <c>personal_4</c> is building 3. This is how
	/// an exit knows which door to return through — the id already records the origin, so nothing
	/// else has to. False for the open world and for unknown ids.
	/// </summary>
	public static bool TryBuildingIndexFor(string? sceneId, out int buildingIndex)
	{
		buildingIndex = -1;
		if (sceneId == null || !TryKindFor(sceneId, out string kind) || kind != InteriorKind)
			return false;
		string number = sceneId[(sceneId.LastIndexOf('_') + 1)..];
		buildingIndex = int.Parse(number, NumberStyles.None, CultureInfo.InvariantCulture) - 1;
		return true;
	}

	/// <summary>
	/// The contract kind for <paramref name="sceneId"/>. Throws for an unknown id; callers that must
	/// not throw (the loop driver's per-frame path) use <see cref="TryKindFor"/> and fail closed.
	/// </summary>
	public static string KindFor(string sceneId)
		=> TryKindFor(sceneId, out string kind)
			? kind
			: throw new ArgumentException($"SceneCatalog: unknown scene id '{sceneId}'", nameof(sceneId));
}
