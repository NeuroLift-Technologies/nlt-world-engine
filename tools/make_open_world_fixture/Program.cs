using System;
using System.Globalization;
using System.IO;
using NltWorldEngine;

// Writes fixtures/replay/open-world-day.json — an open-world replay bundle.
//
// Why it exists: every existing fixture under fixtures/replay/ declares scene.kind "interior", so the
// observer has only ever been able to boot into a room. The open_world scene is valid per
// docs/contracts/state-feed-v1.md §3 ("open_world" with scene.id "open_world") and WorldView already
// renders it, but nothing exercised that path — which left GP-1 (world fidelity) with no way to take
// a screenshot of the procedural world and compare it against the dashboard target.
//
// The positions below are placed on the real settlement terrain and the y is read from
// WorldGeometry.HeightAt rather than invented, so a resident stands on the ground rather than in it.
// This is the same function TerrainBuilder meshes the ground from, which is the only reason the number
// is trustworthy.

var frames = new System.Text.StringBuilder();
const int frameCount = 12;
const int startTick = 700;
const double secondsPerTick = 1.0;   // the feed's own cadence, matching the other bundles

// Two agents walking out from the settlement centre toward the plaza. Real coordinates: the
// settlement is at (-66, 46) at y 7.2 (WorldConstants), so these start on flat plaza and stay
// walkable — a path out into the lake or up a cliff would show a resident standing in water, which is
// a fixture bug masquerading as a rendering bug.
const double settleX = WorldConstants.SettleX;
const double settleZ = WorldConstants.SettleZ;

// The residents' path: a slow circle about their own starting offset. Radius and angular speed are
// named because the velocity below is derived from them.
const double PathRadius = 1.6;
const double PathOmega = 0.35;

// Phase offset rather than a per-agent speed: the two residents walk the same path at the same
// walking speed, offset in time. A per-agent speed multiplier (1.15x / 1.05x, as an earlier draft
// had) desynchronised velocity from position and tripped the walk-speed warning.
var agents = new[]
{
    (id: "avatar_01", name: "Jamie", role: "avatar", dx: -2.0, dz: 1.0, phase: 0.0),
    (id: "aide_01", name: "Rowan", role: "aide", dx: 2.0, dz: -1.5, phase: 1.9),
};

for (int f = 0; f < frameCount; f++)
{
    double t = f * secondsPerTick;
    string tick = (startTick + f).ToString(CultureInfo.InvariantCulture);
    string iso = new DateTime(2026, 3, 11, 9, 30, 0, DateTimeKind.Utc).AddSeconds(t)
        .ToString("yyyy-MM-ddTHH:mm:ssZ", CultureInfo.InvariantCulture);

    frames.Append("    {\n");
    frames.Append($"      \"schemaVersion\": \"nlt.state-feed.v1\",\n");
    frames.Append($"      \"tick\": {tick},\n");
    frames.Append($"      \"simTimeIso\": \"{iso}\",\n");
    frames.Append("      \"scene\": { \"id\": \"open_world\", \"kind\": \"open_world\" },\n");

    frames.Append("      \"agents\": [\n");
    for (int a = 0; a < agents.Length; a++)
    {
        var ag = agents[a];
        // A short walk out of the plaza, not a lap of the world: the point of this fixture is the
        // scene, and a resident 200 m away is a dot on a screenshot.
        double x = settleX + ag.dx + Math.Cos((t + ag.phase) * PathOmega) * PathRadius;
        double z = settleZ + ag.dz + Math.Sin((t + ag.phase) * PathOmega) * PathRadius;
        float y = WorldGeometry.HeightAt((float)x, (float)z);

        // Velocity is the derivative of the position above, not a separate guess: x = a + cos(ωt)·r
        // gives dx/dt = −sin(ωt)·r·ω. That matters because FeedReader warns on any implied speed
        // faster than a person walks, and multiplying by a per-agent speed factor produced exactly
        // that — the first run warned on every frame. Peak speed is now r·ω = 1.6 × 0.35 ≈ 0.56 m/s,
        // and the two agents differ by phase offset rather than by an inconsistent speed.
        double vx = -Math.Sin((t + ag.phase) * PathOmega) * PathRadius * PathOmega;
        double vz = Math.Cos((t + ag.phase) * PathOmega) * PathRadius * PathOmega;

        // Needs drift slightly so the bars move; the values stay inside the 0..1 range the loader
        // validates, and they are deliberately plausible rather than decorative.
        double need = 0.55 + 0.18 * Math.Sin(t * 0.5 + a);

        frames.Append("        {\n");
        frames.Append($"          \"id\": \"{ag.id}\",\n");
        frames.Append($"          \"name\": \"{ag.name}\",\n");
        frames.Append($"          \"role\": \"{ag.role}\",\n");
        frames.Append("          \"scene\": \"open_world\",\n");
        frames.Append(CultureInfo.InvariantCulture, $"          \"position\": {{ \"x\": {x:0.###}, \"y\": {y:0.###}, \"z\": {z:0.###} }},\n");
        frames.Append(CultureInfo.InvariantCulture, $"          \"velocity\": {{ \"x\": {vx:0.###}, \"y\": 0.0, \"z\": {vz:0.###} }},\n");
        frames.Append($"          \"appearance\": {{ \"body\": \"{ag.id}\", \"walkPhase\": {t:0.###} }},\n");
        frames.Append($"          \"levels\": {{ \"attentionEnergy\": {0.68 - 0.05 * a:0.###}, \"stressLevel\": {0.34 + 0.06 * a:0.###}, \"confidence\": 0.61, \"cognitiveLoad\": 0.44, \"independenceScore\": 0.67, \"supportNeedLevel\": 0.29 }},\n");
        frames.Append($"          \"needs\": {{ \"quiet\": {need:0.###}, \"rest\": {0.61 - 0.04 * a:0.###}, \"social\": {0.58 + 0.05 * a:0.###}, \"stimulation\": 0.52 }},\n");
        frames.Append("          \"state\": \"settled\",\n");
        frames.Append($"          \"stateSince\": {startTick - 40},\n");
        frames.Append("          \"currentGoal\": \"Walk to the waterfront\",\n");
        frames.Append("          \"currentTask\": \"Walk to the waterfront\",\n");
        frames.Append("          \"struggleSignals\": [],\n");
        frames.Append("          \"learnedStrategies\": [],\n");
        frames.Append("          \"burnout\": false,\n");
        frames.Append($"          \"supportIndex\": {(a == 0 ? 0 : 1)}\n");
        frames.Append(a == agents.Length - 1 ? "        }\n" : "        },\n");
    }
    frames.Append("      ],\n");

    // The pair's real shape, read off a frame that loads today (fixtures/replay/stayalert-day.json).
    // An earlier draft wrote a plausible-looking {since, focusAgentId, supportLevel} object and the
    // reader rejected the whole bundle for a missing required key 'overallScore' — the pair block is
    // a Fusion gate report, not a relationship summary. Dimensions are the contract's own six
    // FusionDimensions; the scores are plausible-but-not-passing so the Fusion Gate panel reads as a
    // still-growing stage rather than inventing readiness.
    frames.Append("      \"pairs\": [\n");
    frames.Append("        {\n");
    frames.Append("          \"avatarId\": \"avatar_01\",\n");
    frames.Append("          \"aideId\": \"aide_01\",\n");
    frames.Append("          \"ready\": false,\n");
    frames.Append("          \"overallScore\": 0.34,\n");
    frames.Append("          \"blockingDimensions\": [\"EXPERIENTIAL_DEPTH\", \"INDEPENDENCE_LEVEL\", \"STRATEGY_INTERNALISATION\"],\n");
    frames.Append("          \"dimensions\": {\n");
    frames.Append("            \"EXPERIENTIAL_DEPTH\": { \"score\": 0.22, \"passes\": false },\n");
    frames.Append("            \"COACHING_EFFECTIVENESS\": { \"score\": 0.41, \"passes\": false },\n");
    frames.Append("            \"INDEPENDENCE_LEVEL\": { \"score\": 0.38, \"passes\": false },\n");
    frames.Append("            \"EMOTIONAL_RESILIENCE\": { \"score\": 0.56, \"passes\": true },\n");
    frames.Append("            \"STRATEGY_INTERNALISATION\": { \"score\": 0.19, \"passes\": false },\n");
    frames.Append("            \"BURNOUT_MANAGEMENT\": { \"score\": 0.61, \"passes\": true }\n");
    frames.Append("          },\n");
    frames.Append("          \"recommendations\": [\"Need more experiences (current: 22%, target: 60%)\"]\n");
    frames.Append("        }\n");
    frames.Append("      ],\n");

    frames.Append("      \"burnoutEpisodes\": [],\n");
    frames.Append("      \"selfRecognitions\": [],\n");

    // One event on the first frame and one partway through, so the Recent Events panel has something
    // real to show in the open world rather than an empty list. Kinds are from the feed's own
    // vocabulary (FeedVocabulary.EventKinds); nothing here is invented outside it.
    frames.Append("      \"events\": [\n");
    if (f == 0)
    {
        frames.Append($"        {{ \"tick\": {startTick}, \"agentId\": \"avatar_01\", \"kind\": \"scene_enter\", \"severity\": \"low\", \"text\": \"Jamie and Focus Aide stepped out into the open world.\" }}");
    }
    else if (f == frameCount / 2)
    {
        frames.Append($"        {{ \"tick\": {startTick + f}, \"agentId\": \"aide_01\", \"kind\": \"task_start\", \"severity\": \"low\", \"text\": \"Rowan started walking alongside Jamie.\" }}");
    }
    if (f == 0 || f == frameCount / 2)
        frames.Append("\n");
    frames.Append("      ]\n");
    frames.Append(f == frameCount - 1 ? "    }\n" : "    },\n");
}

// Written relative to this tool's own directory (dotnet run sets it), so the path climbs from
// tools/make_open_world_fixture/ back to the repo root before entering the Godot project.
string outPath = Path.GetFullPath(Path.Combine("..", "..", "world-engine-godot", "fixtures", "replay", "open-world-day.json"));
// The BUNDLE's schemaVersion is the replay wrapper, not the document schema. Each frame inside it is
// a complete nlt.state-feed.v1 document with its own schemaVersion (below). FixtureFeedSource
// dispatches on the top-level value to decide whether to unwrap frames[] or read a single snapshot,
// so writing the document schema at the top level makes it treat the whole bundle as one document and
// reject it for missing 'tick' — which is exactly what it did on the first run.
File.WriteAllText(outPath, $@"{{
  ""schemaVersion"": ""nlt.state-feed.replay.v1"",
  ""name"": ""open-world-day"",
  ""title"": ""Open world — a walk out of the settlement"",
  ""provenance"": {{
    ""authored"": true,
    ""authoringTool"": ""tools/make_open_world_fixture"",
    ""generatedUtc"": ""{DateTime.UtcNow:yyyy-MM-ddTHH:mm:ss}Z"",
    ""note"": ""Synthetic fixture. Exists so the open_world scene kind is reachable: every other bundle under fixtures/replay/ is an interior, so the observer could only ever boot into a room and GP-1 had no world to screenshot. Agent y values are read from WorldGeometry.HeightAt, the same function the terrain mesh is built from, so residents stand on the ground rather than in it.""
  }},
  ""frameCount"": {frameCount},
  ""frames"": [
{frames}  ]
}}
");

Console.WriteLine($"wrote {outPath}");