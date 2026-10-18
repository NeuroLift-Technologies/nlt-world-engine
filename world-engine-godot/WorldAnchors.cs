using System;
using System.Collections.Generic;
using Godot;

namespace NltWorldEngine;

/// <summary>
/// Builds the world's real <see cref="TaskAnchor"/> set from features that already exist in the
/// open world, replacing the single synthetic "agent loop test target" the loop used to carry.
///
/// Why this exists: the agent loop's decision sources pick places to go to. With only a test anchor
/// five metres in front of the avatar there was nothing to choose between, so the loop could not
/// demonstrate traversal at all — it could only prove the socket connected. Anchors derived from the
/// settlement, the plaza, and the lakeshore give it a real destination set to tour.
///
/// Anchors are renderer-owned by contract (see <see cref="TaskAnchor"/>): affordance axes describe
/// the place, not the agent, and deliberately do not appear in <c>nlt.state-feed.v1</c>.
/// </summary>
public static class WorldAnchorBuilder
{
	/// <summary>
	/// Anchors for the open world. Deterministic: same seed and same world geometry every run, so
	/// the avatar tours the same route and a regression is reproducible rather than a lucky walk.
	/// </summary>
	public static List<TaskAnchor> BuildOpenWorld()
	{
		var anchors = new List<TaskAnchor>();

		// --- Settlement centre ------------------------------------------------------
		// The plaza is the busiest place in the world by construction: roads converge on it and
		// the well and benches sit inside it. High social density and noise, low privacy.
		anchors.Add(At("plaza", "The plaza",
			new AffordanceAxes { NoiseLevel = 0.75f, SocialDensity = 0.8f, Privacy = 0.15f },
			WorldConstants.SettleX, WorldConstants.SettleZ));

		// The well is off to one side of the plaza rather than dead centre, so the tour has to
		// cross the square to reach it.
		anchors.Add(At("well", "The well",
			new AffordanceAxes { NoiseLevel = 0.6f, SocialDensity = 0.55f, Privacy = 0.3f },
			WorldConstants.SettleX + 8f, WorldConstants.SettleZ + 3f));

		// --- Building doorways ------------------------------------------------------
		// Reuse the settlement's own placement pass rather than inventing coordinates: these are
		// the buildings that were actually built, and reusing the seed keeps anchors and geometry
		// from drifting apart if either side is retuned.
		var plans = SettlementBuilder.BuildPlans(new SimulationRng((uint)WorldConstants.Seed));
		int index = 0;
		foreach (var plan in plans)
		{
			// Not (BuildingKind)plan.Kind: that field is a [0,1) random draw, so the cast was always 0
			// and every door perceived as a home while the renderer drew offices, shops and schools.
			var kind = SettlementBuilder.KindAt(index);
			var label = SettlementBuilder.KindLabel(kind);
			// Stand the anchor outside the door, not at the building's centre: the centre sits
			// inside the new collision box, so a tour target there is unreachable — the avatar
			// would stall against the wall outside its arrival radius. Front + 1.7 m lands just
			// past the portal entry point on the door axis, which the archetype keeps clear.
			float front = BuildingArchetypes.FrontOffset(kind, plan);
			float fx = MathF.Sin(plan.Rot), fz = MathF.Cos(plan.Rot);
			float ax = plan.X + fx * (front + 1.7f), az = plan.Z + fz * (front + 1.7f);
			// The door leads into this building's own room: the same scene id the settlement gives
			// its portal (SettlementBuilder.Build), and the same index into the world portal list.
			anchors.Add(At(
				$"door_{index}_{label.ToLowerInvariant()}",
				$"{label} door",
				AxesForBuilding(kind),
				ax, az,
				new PortalLink(SettlementBuilder.SceneIdFor(kind, index), index)));
			index++;
		}

		// --- Lakeshore ---------------------------------------------------------------
		// Quiet and screened: the inverse of the plaza on every axis. Gives the tour somewhere to
		// go that is not another building, and exercises a long traverse across open ground.
		for (int i = 0; i < 4; i++)
		{
			var angle = i / 4f * Mathf.Tau + 0.7f;
			var shore = WorldGeometry.ShorePoint(WorldConstants.LakeX, WorldConstants.LakeZ, angle);
			anchors.Add(At(
				$"shore_{i}",
				"The lakeshore",
				new AffordanceAxes { NoiseLevel = 0.15f, SocialDensity = 0.12f, Privacy = 0.8f },
				shore.X, shore.Y));
		}

		// --- Open ground -------------------------------------------------------------
		// Walkable clearings spread across the island. Without these the tour never leaves the
		// settlement ring, and the avatar looks like it is pacing a car park.
		var rng = new SimulationRng((uint)WorldConstants.Seed + 4242);
		for (int i = 0; i < 6; i++)
		{
			if (!TryFindClearSpot(rng, out float x, out float z))
				continue;
			var stimulating = i % 2 == 0;
			anchors.Add(At(
				$"clearing_{i}",
				stimulating ? "Open meadow" : "Wooded edge",
				stimulating
					? new AffordanceAxes { NoiseLevel = 0.6f, SocialDensity = 0.65f, Privacy = 0.2f }
					: new AffordanceAxes { NoiseLevel = 0.25f, SocialDensity = 0.2f, Privacy = 0.7f },
				x, z));
		}

		return anchors;
	}

	/// <summary>
	/// Affordance axes for a building, derived from what the building is for rather than assigned
	/// arbitrarily. A home is private and quiet; a shop is the opposite on both.
	/// </summary>
	private static AffordanceAxes AxesForBuilding(SettlementBuilder.BuildingKind kind) => kind switch
	{
		SettlementBuilder.BuildingKind.Apartment =>
			new AffordanceAxes { NoiseLevel = 0.2f, SocialDensity = 0.25f, Privacy = 0.75f },
		SettlementBuilder.BuildingKind.Office =>
			new AffordanceAxes { NoiseLevel = 0.5f, SocialDensity = 0.65f, Privacy = 0.45f },
		SettlementBuilder.BuildingKind.Shop =>
			new AffordanceAxes { NoiseLevel = 0.7f, SocialDensity = 0.8f, Privacy = 0.2f },
		SettlementBuilder.BuildingKind.School =>
			new AffordanceAxes { NoiseLevel = 0.65f, SocialDensity = 0.75f, Privacy = 0.35f },
		_ => AffordanceAxes.Neutral,
	};

	/// <summary>
	/// Create an anchor standing on the terrain at (x, z). Height comes from the same
	/// <see cref="WorldGeometry"/> the terrain mesh was built from, so an anchor never floats or
	/// sinks — which would otherwise let the avatar walk into the ground on approach.
	/// </summary>
	private static TaskAnchor At(string id, string displayName, AffordanceAxes axes, float x, float z,
		PortalLink? link = null) =>
		new(id, displayName, axes)
		{
			Position = new Vector3(x, WorldGeometry.HeightAt(x, z), z),
			Link = link,
		};

	/// <summary>
	/// Rejection-sample a walkable clearing: flat enough to stand on and above the waterline.
	/// The guard bounds the search so degenerate terrain cannot hang the load.
	/// </summary>
	private static bool TryFindClearSpot(SimulationRng rng, out float x, out float z)
	{
		const float halfWorld = WorldConstants.World * 0.5f;
		for (int attempt = 0; attempt < 400; attempt++)
		{
			float cx = rng.Range(-halfWorld, halfWorld);
			float cz = rng.Range(-halfWorld, halfWorld);
			if (!WorldGeometry.Walkable(cx, cz))
				continue;

			// Keep clearings out of the settlement ring: building doorways already cover that
			// ground, and clearings there would crowd the plaza's affordances.
			float ds = MathF.Sqrt(
				(cx - WorldConstants.SettleX) * (cx - WorldConstants.SettleX) +
				(cz - WorldConstants.SettleZ) * (cz - WorldConstants.SettleZ));
			if (ds < WorldConstants.SettleR * 1.4f)
				continue;

			x = cx;
			z = cz;
			return true;
		}
		x = 0f;
		z = 0f;
		return false;
	}
}
