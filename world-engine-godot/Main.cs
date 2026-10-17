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
public partial class Main : NltWorldEngine.WorldView
{
	private FeedTransport _feed = null!;
	private ObserverRoot _observer = null!;
	private bool _following;
	private string _followTargetId = "";
	private const string LocalAvatarTargetId = "__local_avatar__";
	private string _sceneId = "";
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
	private System.Collections.Generic.List<TaskAnchor> _worldAnchors = new();


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
		ObserverCapture.TryCreate(this);
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

		if (doc.Scene.Id != _sceneId)
		{
			_sceneId = doc.Scene.Id;
			// The Fusion tour walks the open world (its destinations are WorldAnchorBuilder's
			// open-world anchors), so that is what the observer sees; a feed that says "Home"
			// would otherwise show a room while the avatar it follows is outdoors.
			if (EnableFusionAgentLoop)
				ShowScene("", "open_world");
			else
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
		_worldAnchors = WorldAnchorBuilder.BuildOpenWorld();

		// Hand the avatar the anchor set so its fallback controller has real destinations. Fusion
		// picks *which* place to visit; this is what lets it move between decisions rather than
		// standing still whenever Fusion has nothing to say.
		avatar.Anchors = _worldAnchors;

		// The avatar already attaches a UtilityAgentController in its own _Ready. Leaving that in
		// place is deliberate: if Fusion is slow, down, or mid-restart, the avatar keeps moving on
		// its own instead of freezing on an IdleController. Fusion intents replace it when they
		// arrive.
		_agentLoopDriver = new AgentLoopDriver
		{
			Name = "AgentLoopDriver",
			Enabled = true,
			TargetAgentId = LocalAvatarTargetId,
			Anchors = _worldAnchors,
		};
		var endpoint = OS.GetEnvironment("NLT_AGENT_LOOP_ENDPOINT");
		if (!string.IsNullOrWhiteSpace(endpoint))
			_agentLoopDriver.FusionEndpoint = endpoint;
		AddChild(_agentLoopDriver);
		GD.Print($"Fusion agent loop enabled for {LocalAvatarTargetId}; endpoint: " +
			$"{_agentLoopDriver.FusionEndpoint}; destinations: {_worldAnchors.Count} anchors");
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
			// Feed positions are scene-local: in an interior document they are room coordinates, and
			// used as open-world coordinates they put the tour's avatar in empty ground far from any
			// anchor. Start an open-world tour on the plaza unless the feed is itself open-world.
			Vector3 spawn = doc.Scene.Kind == "open_world" && primary != null
				? primary.Position3()
				: WorldGeometry.PlazaSpawn();
			localAvatar.GlobalPosition = spawn + new Vector3(2f, 1f, 0f);
			localAvatar.Observe(localAvatar.GlobalPosition, new[] { 0.5f, 0.5f, 0.5f, 0.5f }, doc.Scene.Id);
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
				avatar.GlobalPosition = agent.Position3() + new Vector3(2f, 1f, 0f);
				avatar.Observe(avatar.GlobalPosition,
					new[] { 0.5f, 0.5f, 0.5f, 0.5f }, doc.Scene.Id);
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
	protected override bool OpenWorldBodiesLive => _avatars.Count > 0;

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
