using NltWorldEngine;
using NltWorldEngine.Agents;
using Godot;
using NltWorldEngine.Feed;
using NltWorldEngine.Observer;

/// <summary>
/// Composition root. The world comes from <see cref="WorldView"/> (the open world, Phase B); the
/// observer is added on top of it (Phase D).
///
/// The two are deliberately separate systems talking one direction. <see cref="FeedTransport"/>
/// reads documents that already exist; it never writes to the world, never advances a clock Fusion
/// owns, and never derives a value it was not given.
/// </summary>
public partial class Main : NltWorldEngine.WorldView, IPortalTransit
{
	private FeedTransport _feed = null!;
	private ObserverRoot _observer = null!;
	private bool _following;
	private string _followTargetId = "";
	private const string LocalAvatarTargetId = "__local_avatar__";
	private string _sceneId = "";
	/// <summary>
	/// The scene the avatars are physically in — what <see cref="ShowScene"/> was given, not what
	/// the feed says. They differ on the Fusion tour, which always shows the open world while its
	/// feed names an interior; keying spawn, anchors and the fall reset off the feed put the avatar
	/// at room coordinates under the island terrain.
	/// </summary>
	private string _shownSceneId = "";
	private string _shownSceneKind = "";
	/// <summary>
	/// When true, spawn a live Jolt avatar per feed agent. Off by default so the observer
	/// fixture path is unchanged until the loop is validated.
	/// </summary>
	[Export] public bool EnableLiveAvatars { get; set; } = false;

	/// <summary>Enable the opt-in single local-avatar Fusion loop for end-to-end testing.</summary>
	[Export] public bool EnableFusionAgentLoop { get; set; } = false;

	private PackedScene? _avatarScene;

	private readonly System.Collections.Generic.Dictionary<string, AvatarCharacter> _avatars = new();
	private AgentLoopDriver? _agentLoopDriver;
	/// <summary>Observer trace (nlt.observer-trace.v1); null unless NLT_OBSERVER_TRACE is set.</summary>
	private ObserverTraceRecorder? _trace;
	private System.Collections.Generic.List<TaskAnchor> _worldAnchors = new();
	private SceneAnchorSets _sceneAnchors = null!;


	public override void _ExitTree()
	{
		// Write whatever the trace still has queued; a killed run keeps what was already flushed.
		_trace?.Dispose();
		_trace = null;
		base._ExitTree();
	}

	public override void _Ready()
	{
		base._Ready();
		EnableFusionAgentLoop |= OS.GetEnvironment("NLT_AGENT_LOOP_ENABLED") == "1";

		_feed = new FeedTransport { Name = "FeedTransport" };
		AddChild(_feed);

		_observer = new ObserverRoot { Name = "Observer" };
		AddChild(_observer);
		_observer.Attach(_feed, this);

		// The world view follows the feed's scene (B.3): swap to the room the agents are in.
		_feed.DocumentChanged += OnDocumentChanged;

		// The observer loads its fixture during its own _Ready, which runs before we subscribe, so seed
		// the scene and the residents from whatever is already current rather than waiting a tick.
		OnDocumentChanged(_feed.Current);

		// Inert unless --capture is passed; see ObserverCapture.
		var capture = ObserverCapture.TryCreate(this);
		if (capture != null)
		{
			capture.TickSource = () => _agentLoopDriver?.Tick ?? 0;
			if (capture.RequestedFollow)
				ToggleFollow();
		}
		// Inert unless --trace-truth / --trace-occupy is passed; test tools for the observer trace.
		TraceTestTools.TryCreate(this, () => _agentLoopDriver);
		_observer.LevelChanged += ApplyRequestedLevel;
		_observer.FocusRequested += ToggleFollow;
		_observer.FollowTargetChanged += SelectFollowTarget;
		ApplyRequestedLevel();
	}

	private void ApplyRequestedLevel()
	{
		if (_observer == null)
			return;
		var capture = GetNodeOrNull<ObserverCapture>("ObserverCapture");
		if (capture != null)
			_observer.SetReadingLevel(capture.RequestedLevel);
	}

	/// <summary>
	/// Toggle the world camera following the agent the observer is showing.
	///
	/// Routed through here rather than letting the observer reach into the camera: the observer reads
	/// the world, it does not drive it (see <see cref="WorldView.Camera"/>). The composition root owns
	/// both systems, so it is the one place that may connect them.
	/// </summary>
	private void ToggleFollow()
	{
		_following = !_following;
		if (_following)
			Follow(CurrentFollowTargetPoint);
		else
			Follow(null);
		_observer.SetFocusActive(_following);
	}

	private void SelectFollowTarget(string targetId)
	{
		_followTargetId = targetId;
		_observer.SetFollowTargets(_feed.Current?.Agents ?? System.Array.Empty<AgentState>(),
			_followTargetId, EnableLiveAvatars);
		if (_following)
			Follow(CurrentFollowTargetPoint);
	}

	/// <summary>Read the selected subject's current world position.</summary>
	private Vector3? CurrentFollowTargetPoint()
	{
		if (_followTargetId == "__none__")
			return null;
		// Mid-transition the view already shows the destination while the avatar is still held at
		// its old spot; following it there would swing the camera away and back (AGENT-LOOP-002 T4).
		// Null holds the camera until the avatar is placed.
		if (_transiting && _followTargetId is LocalAvatarTargetId or "")
			return null;
		// While the spectator peeks into a room, following anyone (the avatar outdoors, or a feed agent
		// placed in the feed's scene) would pull the camera out of the room the spectator chose.
		if (_peekFrom != null)
			return null;
		if (_followTargetId == LocalAvatarTargetId)
		{
			if (_avatars.TryGetValue(LocalAvatarTargetId, out AvatarCharacter? local) && IsInstanceValid(local))
				return local.GlobalPosition;
			return null;
		}

		if (string.IsNullOrEmpty(_followTargetId))
			return _avatars.TryGetValue(LocalAvatarTargetId, out AvatarCharacter? defaultLocal)
				&& IsInstanceValid(defaultLocal)
				? defaultLocal.GlobalPosition
				: FeedTransport.PrimaryAvatar(_feed.Current)?.Position3();

		AgentState? selected = _feed.Current?.Agent(_followTargetId);
		return selected?.Position3();
	}

	/// <summary>
	/// Follow the feed (RENDERER-PLAN.md B.2/B.3): swap the world view when the scene changes, and
	/// re-place the residents on every document.
	///
	/// The scene swap is guarded on the id so a manual camera orbit is not fought on every document —
	/// only a real scene change re-frames. Residents get every document, because an agent moving inside
	/// the same room still has to be re-placed and re-animated.
	/// </summary>
	private void OnDocumentChanged(NltWorldEngine.StateFeed? doc)
	{
		if (doc == null)
			return;

		if (EnableFusionAgentLoop)
		{
			// Loop on: the viewer shows the scene the loop avatar is physically in (AGENT-LOOP-002
			// T1), and the feed's scene never overrides it — a feed that says "Home" would otherwise
			// show a room while the avatar it follows is outdoors. Checked on every document but
			// idempotent, so a manual orbit is not fought. A --scene capture pin still wins inside
			// ShowScene: precedence is pin > loop avatar > feed.
			_sceneId = doc.Scene.Id;
			ShowLoopAvatarScene();
		}
		else if (doc.Scene.Id != _sceneId)
		{
			_sceneId = doc.Scene.Id;
			_shownSceneId = doc.Scene.Id;
			_shownSceneKind = doc.Scene.Kind;
			ShowScene(doc.Scene.Id, doc.Scene.Kind);
		}

		Residents.Sync(doc, ReducedMotion);

		SyncLiveAvatars(doc);
		if (EnableFusionAgentLoop && _agentLoopDriver == null)
			StartFusionAgentLoop();
		ReconcileFollowTarget(doc);
		_observer.SetFollowTargets(doc.Agents, _followTargetId,
			EnableLiveAvatars || EnableFusionAgentLoop);
		if (_following)
			Follow(CurrentFollowTargetPoint);
	}

	/// <summary>
	/// Show the loop avatar's own scene. Before the avatar exists that is the open world, where it
	/// is about to spawn (<see cref="LiveSpawn"/>). An id the catalog cannot name is refused rather
	/// than shown as a guess.
	/// </summary>
	private void ShowLoopAvatarScene()
	{
		// Mid-transition the view already shows the destination while the avatar's own scene is
		// still the old one; the transition settles both.
		if (_transiting)
			return;
		string sceneId = LoopAvatarScene;
		if (_peekFrom != null)
		{
			// The spectator is looking into a room. That holds until they come back, or until the
			// avatar itself changes scene, when the view goes with it.
			if (sceneId == _peekFrom)
				return;
			EndPeekState();
		}
		if (sceneId == _shownSceneId)
			return;
		if (!SceneCatalog.TryKindFor(sceneId, out string kind))
		{
			GD.PushError($"Main: loop avatar is in unknown scene '{sceneId}'; the view is left as it is.");
			return;
		}
		_shownSceneId = sceneId;
		_shownSceneKind = kind;
		ShowScene(SceneCatalog.IsOpenWorld(sceneId) ? "" : sceneId, kind);
		SyncAvatarVisibility();
	}

	/// <summary>The scene the loop avatar is in, or the open world before it exists.</summary>
	private string LoopAvatarScene
		=> _avatars.TryGetValue(LocalAvatarTargetId, out AvatarCharacter? local)
			&& IsInstanceValid(local) && !string.IsNullOrEmpty(local.SceneId)
				? local.SceneId
				: SceneCatalog.OpenWorldId;

	// --- Spectator peek (Joshua, 2026-10-21) ------------------------------------------------------
	// While the loop runs the view belongs to the avatar, but a click on a building still shows the
	// room inside — only the view: the avatar keeps living where it is, and nothing it does changes.
	// Physics stays with the avatar (OpenWorldBodiesLive), so the room shown is display-only. Only
	// one interior can be loaded at a time, so the spectator can look into rooms only while the
	// avatar is outdoors: with the avatar inside, its room is the one that must stay loaded.

	/// <summary>The avatar's scene when the spectator started peeking, or null when not peeking.</summary>
	private string? _peekFrom;

	/// <inheritdoc />
	protected override bool SpectatorDoor(string sceneId, string kind)
	{
		if (_transiting)
		{
			SetViewNotice("The avatar is going through a door; try again in a moment.", 4);
			return false;
		}
		// A --scene capture pin holds the view: a peek could be shown but never undone.
		if (PinnedSceneId != null)
		{
			SetViewNotice($"The view is pinned to {PinnedSceneId} for capture; doors are not used.", 4);
			return false;
		}
		string avatarScene = LoopAvatarScene;
		if (_peekFrom != null && (sceneId.Length == 0 || sceneId == avatarScene))
		{
			EndPeekState();
			ShowLoopAvatarScene();
			GD.Print($"[Spectator] back with the avatar in {avatarScene}");
			return true;
		}
		if (!SceneCatalog.IsOpenWorld(avatarScene))
		{
			SetViewNotice($"The avatar is inside ({avatarScene}); the view stays with it until it leaves.", 5);
			GD.Print($"[Spectator] door refused: the avatar is inside {avatarScene}");
			return false;
		}
		if (sceneId.Length == 0 || !ShowScene(sceneId, kind))
			return false;
		_peekFrom = avatarScene;
		_shownSceneId = sceneId;
		_shownSceneKind = kind;
		SyncAvatarVisibility();
		SetViewNotice($"Looking inside ({sceneId}). The avatar is still outside: press E or click the exit to go back.");
		GD.Print($"[Spectator] peeking into {sceneId}; the avatar stays in {avatarScene}");
		return true;
	}

	private void EndPeekState()
	{
		_peekFrom = null;
		SetViewNotice(null);
	}

	/// <summary>
	/// With the loop on, a live avatar is drawn only in the scene on show: one walking the open world
	/// while the spectator looks into a room would otherwise float among the room's furniture.
	/// </summary>
	private void SyncAvatarVisibility()
	{
		foreach (var avatar in _avatars.Values)
			if (IsInstanceValid(avatar))
				avatar.Visible = !EnableFusionAgentLoop || avatar.SceneId == _shownSceneId;
	}

	// --- Engine-owned scene transition (AGENT-LOOP-002 T3) --------------------------------------

	private string? _transitScene;
	private bool _transiting;

	/// <inheritdoc />
	public string? CanTransit(AvatarCharacter avatar, PortalLink link)
		=> SceneTransitRules.Check(link, InteriorLevelExists, WorldPortals.Count, PinnedSceneId, _transiting);

	/// <inheritdoc />
	/// <remarks>Called from the avatar's arrival (inside its physics step), so the work is deferred.</remarks>
	public void Transit(AvatarCharacter avatar, PortalLink link)
	{
		if (_transiting)
			return;
		_transiting = true;
		// The view goes with the avatar: a spectator's peek ends here.
		EndPeekState();
		avatar.HoldForTransition();
		Callable.From(() => RunTransit(avatar, link)).CallDeferred();
	}

	/// <summary>
	/// Take <paramref name="avatar"/> through a doorway: show the destination (which switches the
	/// physics to it), wait for its collision to be in the physics space, find the floor under the
	/// arrival point, and place the avatar there. If the destination cannot be shown the avatar is
	/// released where it stood and nothing else changes.
	/// </summary>
	private async void RunTransit(AvatarCharacter avatar, PortalLink link)
	{
		string from = avatar.SceneId;
		string target = link.TargetSceneId;
		try
		{
			if (!SceneCatalog.TryKindFor(target, out string kind))
				throw new System.InvalidOperationException($"unknown destination '{target}'");
			bool indoor = kind == SceneCatalog.InteriorKind;

			_transitScene = target;
			if (!ShowScene(indoor ? target : "", kind))
				throw new System.InvalidOperationException($"'{target}' could not be shown");
			_shownSceneId = target;
			_shownSceneKind = kind;

			Portal? doorway = indoor ? ShownInteriorExit : WorldPortals[link.BuildingIndex];
			if (doorway == null)
				throw new System.InvalidOperationException($"'{target}' has no exit to arrive at");
			var (arrival, facing) = indoor
				? SceneTransitRules.IndoorArrival(doorway)
				: SceneTransitRules.OutdoorArrival(doorway);

			// Two physics frames: one for the destination's bodies to enter the space, one for
			// queries to see them. Placing the body earlier drops it through the floor.
			await ToSignal(GetTree(), SceneTree.SignalName.PhysicsFrame);
			await ToSignal(GetTree(), SceneTree.SignalName.PhysicsFrame);
			if (!IsInstanceValid(avatar))
				return;

			var landing = new Vector3(arrival.X, FloorBelow(avatar, arrival, indoor) + 0.05f, arrival.Z);
			avatar.TransitionTo(landing, target, facing);
			_trace?.SceneTransition(avatar, from, target);
			SyncAvatarVisibility();
			avatar.InteriorRecoveryPoint = indoor ? landing : null;
			// Inside, the wander fallback roams the room rather than heading for the exit.
			avatar.Anchors = indoor ? System.Array.Empty<TaskAnchor>() : _worldAnchors;
			// The room's furniture, built once its collision is live (AGENT-LOOP-002 T5).
			if (indoor && !_sceneAnchors.HasFurniture(target))
				BuildRoomFurniture(target, avatar);
			// After the furniture exists, so the record lists what perception can now offer.
			_trace?.SceneEntities(avatar, target, _sceneAnchors.For(target));
			GD.Print($"[SceneTransit] {avatar.AgentId}: {from} -> {target}, placed at {landing}");
			WarnStrandedAvatars(avatar, target);
		}
		catch (System.InvalidOperationException e)
		{
			GD.PushWarning($"[SceneTransit] {avatar.AgentId} stays in {from}: {e.Message}");
			_transitScene = null;
			if (_shownSceneId != from && SceneCatalog.TryKindFor(from, out string fromKind)
				&& ShowScene(SceneCatalog.IsOpenWorld(from) ? "" : from, fromKind))
			{
				_shownSceneId = from;
				_shownSceneKind = fromKind;
			}
			avatar.ReleaseHold();
		}
		finally
		{
			// Any failure before placement (not only the expected ones caught above) must not
			// leave the avatar frozen: ingress rejects every intent while it is held.
			if (IsInstanceValid(avatar) && avatar.InTransition)
				avatar.ReleaseHold();
			_transitScene = null;
			_transiting = false;
			RefreshWorldPhysics();
		}
	}

	/// <summary>
	/// Height of the floor under <paramref name="at"/>: a ray cast down onto the destination's own
	/// collision, never a hard-coded Y. Indoors it starts below the 3.5 m ceilings; where it finds
	/// nothing, the backstop is <c>AvatarGround</c> (y = 0) indoors and the terrain outside.
	/// </summary>
	private float FloorBelow(AvatarCharacter avatar, Vector3 at, bool indoor)
	{
		float top = indoor ? 2.5f : WorldGeometry.HeightAt(at.X, at.Z) + 3f;
		float bottom = indoor ? -6f : WorldGeometry.HeightAt(at.X, at.Z) - 3f;
		var query = PhysicsRayQueryParameters3D.Create(new Vector3(at.X, top, at.Z), new Vector3(at.X, bottom, at.Z));
		query.Exclude = new Godot.Collections.Array<Rid> { avatar.GetRid() };
		var hit = GetWorld3D().DirectSpaceState.IntersectRay(query);
		if (hit.Count > 0)
			return ((Vector3)hit["position"]).Y;
		return indoor ? 0f : WorldGeometry.HeightAt(at.X, at.Z);
	}

	/// <summary>
	/// Build <paramref name="sceneId"/>'s furniture anchors from the loaded level's meshes
	/// (<see cref="InteriorAnchors"/>), probing the room's live collision for each approach point.
	/// </summary>
	private void BuildRoomFurniture(string sceneId, AvatarCharacter avatar)
	{
		if (ShownInteriorLevel is not { } level)
			return;
		var meshes = new System.Collections.Generic.List<InteriorAnchors.LevelMesh>();
		CollectMeshes(level, meshes);
		var unplaced = new System.Collections.Generic.List<string>();
		var furniture = InteriorAnchors.Build(meshes, (candidate, centre) => ProbeApproach(avatar, candidate, centre), unplaced);
		_sceneAnchors.SetFurniture(sceneId, furniture);
		int sit = 0, use = 0;
		foreach (var a in furniture)
		{
			if (System.Linq.Enumerable.Contains(a.Affords!, "sit")) sit++;
			if (System.Linq.Enumerable.Contains(a.Affords!, "use")) use++;
		}
		GD.Print($"[SceneAnchors] {sceneId}: {furniture.Count} furniture anchors ({sit} to sit on, {use} to use)" +
			(unplaced.Count > 0 ? $"; no clear approach for {string.Join(", ", unplaced)}" : ""));
	}

	private static void CollectMeshes(Node node, System.Collections.Generic.List<InteriorAnchors.LevelMesh> into)
	{
		foreach (Node child in node.GetChildren())
		{
			if (child is MeshInstance3D mesh && mesh.Mesh != null && mesh.IsVisibleInTree())
			{
				Aabb box = mesh.GlobalTransform * mesh.GetAabb();
				into.Add(new InteriorAnchors.LevelMesh(mesh.Name, box.Position + box.Size * 0.5f, box.Size));
			}
			CollectMeshes(child, into);
		}
	}

	/// <summary>
	/// Can an agent stand at <paramref name="candidate"/> and reach the object centred at
	/// <paramref name="objectCentre"/>? Needs standing-height floor under it (not a table top), room for
	/// the avatar's capsule, and nothing — a wall, say — between it and the object. Returns the point on
	/// the floor, or null.
	/// </summary>
	private Vector3? ProbeApproach(AvatarCharacter avatar, Vector3 candidate, Vector3 objectCentre)
	{
		var space = GetWorld3D().DirectSpaceState;
		var exclude = new Godot.Collections.Array<Rid> { avatar.GetRid() };

		var down = PhysicsRayQueryParameters3D.Create(new Vector3(candidate.X, 2.5f, candidate.Z), new Vector3(candidate.X, -6f, candidate.Z));
		down.Exclude = exclude;
		var floorHit = space.IntersectRay(down);
		if (floorHit.Count == 0)
			return null;
		float floorY = ((Vector3)floorHit["position"]).Y;
		if (floorY > 0.35f)
			return null;

		var body = new PhysicsShapeQueryParameters3D
		{
			Shape = new CapsuleShape3D { Radius = 0.4f, Height = 1.8f },
			Transform = new Transform3D(Basis.Identity, new Vector3(candidate.X, floorY + 0.95f, candidate.Z)),
			Exclude = exclude,
		};
		if (space.IntersectShape(body, 1).Count > 0)
			return null;

		var from = new Vector3(candidate.X, floorY + 1f, candidate.Z);
		var to = new Vector3(objectCentre.X, floorY + 1f, objectCentre.Z);
		var reach = PhysicsRayQueryParameters3D.Create(from, to);
		reach.Exclude = exclude;
		var reachHit = space.IntersectRay(reach);
		if (reachHit.Count > 0 && from.DistanceTo((Vector3)reachHit["position"]) < InteriorAnchors.ApproachGap - 0.15f)
			return null;

		return new Vector3(candidate.X, floorY, candidate.Z);
	}

	/// <summary>
	/// One live scene at a time: any other physical avatar left in the scene being switched off will
	/// fall. Accepted for a single avatar (AGENT-LOOP-002 decisions); said out loud when it happens.
	/// </summary>
	private void WarnStrandedAvatars(AvatarCharacter mover, string target)
	{
		foreach (var other in _avatars.Values)
			if (other != mover && IsInstanceValid(other) && other.SceneId != target)
				GD.PushWarning($"[SceneTransit] {other.AgentId} is still in {other.SceneId}, whose physics " +
					$"is now off while {mover.AgentId} is in {target}.");
	}

	/// <summary>
	/// While the loop runs, the displayed scene is the avatar's, so a spectator door must not swap
	/// it: entering a room would show one scene while the avatar walks in another.
	/// </summary>
	protected override bool SpectatorDoorsLocked => EnableFusionAgentLoop;

	private void ReconcileFollowTarget(NltWorldEngine.StateFeed doc)
	{
		if (_followTargetId == "__none__")
			return;

		if (_followTargetId == LocalAvatarTargetId)
		{
			if (_avatars.TryGetValue(LocalAvatarTargetId, out AvatarCharacter? selectedLocal)
				&& IsInstanceValid(selectedLocal))
				return;
		}
		else if (!string.IsNullOrEmpty(_followTargetId) && doc.Agent(_followTargetId) != null)
		{
			return;
		}

		// With the loop on, the subject is the loop avatar: the feed's own avatar is a replay ghost
		// whose positions belong to the feed's scene, not to the scene on show (AGENT-LOOP-002 T4).
		if (EnableFusionAgentLoop && _avatars.TryGetValue(LocalAvatarTargetId, out AvatarCharacter? loopAvatar)
			&& IsInstanceValid(loopAvatar))
		{
			_followTargetId = LocalAvatarTargetId;
			return;
		}
		_followTargetId = FeedTransport.PrimaryAvatar(doc)?.Id
			?? FirstAgentId(doc)
			?? "__none__";
	}

	private static string? FirstAgentId(NltWorldEngine.StateFeed doc)
	{
		foreach (AgentState agent in doc.Agents)
			return agent.Id;
		return null;
	}

	private void StartFusionAgentLoop()
	{
		var avatar = _avatars.TryGetValue(LocalAvatarTargetId, out AvatarCharacter? local)
			&& IsInstanceValid(local)
				? local
				: null;
		if (avatar == null)
		{
			GD.PushError("Fusion agent loop requires the local avatar, but it was not created.");
			return;
		}

		// Real destinations instead of the old synthetic "agent loop test target" sphere. The loop
		// needs a choice of places to exist at all; with one anchor five metres away it could only
		// ever prove the socket connected, never that the avatar traverses the world.
		//
		// Scene-aware: interiors carry no open-world destinations. An avatar inside personal_1
		// (or any room) must not chase plaza/door/lakeshore anchors that sit outside its walls —
		// it wanders or idles locally until the feed moves it back to open_world.
		_worldAnchors = _shownSceneKind == SceneCatalog.OpenWorldKind
			? WorldAnchorBuilder.BuildOpenWorld()
			: new System.Collections.Generic.List<TaskAnchor>();

		// Hand the avatar the anchor set so its fallback controller has real destinations. Fusion
		// picks *which* place to visit; this is what lets it move between decisions rather than
		// standing still whenever Fusion has nothing to say.
		avatar.Anchors = _worldAnchors;

		// Perception and ingress ask per scene (AGENT-LOOP-002 T2): the open world's anchors outside,
		// a room's exit inside, built from the exit WorldView finds when it loads the level.
		_sceneAnchors = new SceneAnchorSets(_worldAnchors,
			sceneId => sceneId == ShownInteriorSceneId ? ShownInteriorExit : null);

		// The avatar already attaches a UtilityAgentController in its own _Ready. Leaving that in
		// place is deliberate: if Fusion is slow, down, or mid-restart, the avatar keeps moving on
		// its own instead of freezing on an IdleController. Fusion intents replace it when they
		// arrive.
		_agentLoopDriver = new AgentLoopDriver
		{
			Name = "AgentLoopDriver",
			Enabled = true,
			TargetAgentId = LocalAvatarTargetId,
			AnchorsFor = _sceneAnchors.For,
			Transit = this,
		};
		var endpoint = OS.GetEnvironment("NLT_AGENT_LOOP_ENDPOINT");
		if (!string.IsNullOrWhiteSpace(endpoint))
			_agentLoopDriver.FusionEndpoint = endpoint;
		// Fusion decides only for roster ids it registered (AGENT-LOOP-003 F0). The internal
		// LocalAvatarTargetId key stays; only the perception's agentId changes.
		_agentLoopDriver.PerceptionAgentId = OS.GetEnvironment("NLT_AGENT_LOOP_AGENT_ID").Trim();
		if (_agentLoopDriver.PerceptionAgentId.Length == 0)
			GD.PushWarning("NLT_AGENT_LOOP_AGENT_ID is not set: perceptions carry the internal id " +
				$"{LocalAvatarTargetId}, which Fusion does not serve, so no intent will be applied. " +
				"Set it to a registered roster id, e.g. stay_alert_001.");
		// Opt-in observer trace: inert unless NLT_OBSERVER_TRACE names a file. Physical fields only.
		_trace = ObserverTraceRecorder.TryCreateFromEnvironment(new[]
		{
			new TraceAgent(PerceptionBuilder.WireAgentId(LocalAvatarTargetId, _agentLoopDriver.PerceptionAgentId),
				LocalAvatarTargetId, "Local Model", "fusion-agent-loop"),
		});
		_agentLoopDriver.Trace = _trace;
		if (_trace != null && _avatars.TryGetValue(LocalAvatarTargetId, out AvatarCharacter? traced)
			&& IsInstanceValid(traced))
			_trace.SceneEntities(traced, LoopAvatarScene, _sceneAnchors.For(LoopAvatarScene));
		AddChild(_agentLoopDriver);
		GD.Print($"Fusion agent loop enabled for {LocalAvatarTargetId} as " +
			$"'{PerceptionBuilder.WireAgentId(LocalAvatarTargetId, _agentLoopDriver.PerceptionAgentId)}'; " +
			$"endpoint: {_agentLoopDriver.FusionEndpoint}; destinations: {_worldAnchors.Count} anchors");
	}

	/// <summary>
	/// Spawn/sync one <see cref="AvatarCharacter"/> per feed agent when live avatars are
	/// enabled. Feed <see cref="Resident"/> ghosts keep rendering unchanged — avatars are
	/// additive, offset +2 m on X so both are visible side by side for comparison.
	/// No transport, no Fusion, no ASFDK here: default UtilityAgentController only.
	/// </summary>
	private void SyncLiveAvatars(NltWorldEngine.StateFeed doc)
	{
		if (!EnableLiveAvatars && !EnableFusionAgentLoop)
			return;

		_avatarScene ??= GD.Load<PackedScene>("res://Agents/avatar.tscn");
		if (_avatarScene == null)
			return;

		EnsureAvatarGround();

		const string localId = LocalAvatarTargetId;
		if (!_avatars.TryGetValue(localId, out AvatarCharacter? localAvatar) || !IsInstanceValid(localAvatar))
		{
			localAvatar = _avatarScene.Instantiate<AvatarCharacter>();
			localAvatar.Name = localId;
			localAvatar.DisplayName = "Local Model";
			localAvatar.ReducedMotion = ReducedMotion;
			AddChild(localAvatar);
			AgentState? primary = FeedTransport.PrimaryAvatar(doc);
			localAvatar.GlobalPosition = LiveSpawn(primary) + new Vector3(2f, 1f, 0f);
			localAvatar.Observe(localAvatar.GlobalPosition, new[] { 0.5f, 0.5f, 0.5f, 0.5f }, _shownSceneId);
			// Assigned here as well as in StartFusionAgentLoop: the loop builds the anchor set, but
			// an avatar can be spawned on a later document, and one created without anchors would
			// wander blind while its siblings tour properly.
			localAvatar.Anchors = _worldAnchors;
			_avatars[localId] = localAvatar;
			RefreshWorldPhysics();
		}

		if (!EnableLiveAvatars)
			return;

		var seen = new System.Collections.Generic.HashSet<string> { localId };
		foreach (var agent in doc.Agents)
		{
			seen.Add(agent.Id);
			if (!_avatars.TryGetValue(agent.Id, out var avatar) || !IsInstanceValid(avatar))
			{
				avatar = _avatarScene.Instantiate<AvatarCharacter>();
				avatar.Name = agent.Id;
				avatar.DisplayName = agent.Name;
				avatar.ReducedMotion = ReducedMotion;
				AddChild(avatar);
				// Offset so the live body doesn't z-fight the feed ghost.
				avatar.GlobalPosition = LiveSpawn(agent) + new Vector3(2f, 1f, 0f);
				avatar.Observe(avatar.GlobalPosition,
					new[] { 0.5f, 0.5f, 0.5f, 0.5f }, _shownSceneId);
				avatar.Anchors = _worldAnchors;
				_avatars[agent.Id] = avatar;
			}
			else
			{
				avatar.ReducedMotion = ReducedMotion;
			}
		}

		var gone = new System.Collections.Generic.List<string>();
		foreach (var id in _avatars.Keys)
			if (!seen.Contains(id))
				gone.Add(id);
		foreach (var id in gone)
		{
			if (IsInstanceValid(_avatars[id]))
				_avatars[id].QueueFree();
			_avatars.Remove(id);
		}
	}

	/// <summary>
	/// Flat Jolt ground so <c>IsOnFloor()</c> has something to stand on: a backstop under the
	/// interiors' own UCX floors. Disabled while the open world shows (<see cref="SyncAvatarGround"/>).
	/// </summary>
	/// <summary>Live avatars walk the open world, so its physics must stay on while they exist.</summary>
	/// <remarks>
	/// With the loop on, physics follows the loop avatar's scene (AGENT-LOOP-002 T3) — or, while a
	/// transition is running, its destination, so the room's collision is live before the avatar is
	/// placed in it. One live scene at a time (Joshua, 2026-10-17): inside a room the open world's
	/// bodies are switched off.
	/// </remarks>
	protected override bool OpenWorldBodiesLive => _avatars.Count > 0
		&& (!EnableFusionAgentLoop || SceneCatalog.IsOpenWorld(LoopAvatarPhysicsScene));

	private string LoopAvatarPhysicsScene => _transitScene
		?? (_avatars.TryGetValue(LocalAvatarTargetId, out AvatarCharacter? local) && IsInstanceValid(local)
			&& !string.IsNullOrEmpty(local.SceneId)
				? local.SceneId
				: SceneCatalog.OpenWorldId);

	/// <summary>
	/// Where a live avatar starts, in the scene actually shown. In the open world that is always the
	/// middle of town (Joshua, 2026-10-17): feed positions are scene-local, and the tour shows the
	/// open world over an interior feed, so a room position used here put the avatar under the
	/// island terrain. Inside a room the feed's room coordinates are valid as-is.
	/// </summary>
	private Vector3 LiveSpawn(AgentState? feedAgent)
		=> _shownSceneKind == SceneCatalog.OpenWorldKind
			? WorldGeometry.PlazaSpawn()
			: feedAgent?.Position3() ?? Vector3.Zero;

	private void EnsureAvatarGround()
	{
		if (GetNodeOrNull<StaticBody3D>(AvatarGroundName) != null)
			return;
		var ground = new StaticBody3D { Name = AvatarGroundName };
		var shape = new CollisionShape3D();
		var box = new BoxShape3D { Size = new Vector3(500f, 1f, 500f) };
		shape.Shape = box;
		ground.AddChild(shape);
		ground.Position = new Vector3(0f, -0.5f, 0f);
		AddChild(ground);
		// Off in the open world (it made the lake walkable), on inside interiors.
		SyncAvatarGround();
	}
}
