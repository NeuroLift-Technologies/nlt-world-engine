# Multiplayer and networking

## High-level multiplayer (scene replication)
- Peers:
  - `ENetMultiplayerPeer` (UDP) for desktop and console.
  - `WebSocketMultiplayerPeer` for web clients or simple relays.
  - `WebRTCMultiplayerPeer` for browser peer-to-peer, which needs a signaling server.
  - `OfflineMultiplayerPeer` is the default.
  - Assign the peer with `multiplayer.multiplayer_peer = peer`.
- Peer ID 1 is the server or host. Check `multiplayer.is_server()` and `multiplayer.get_unique_id()`. React to the `peer_connected`, `peer_disconnected`, `connected_to_server` and `connection_failed` signals.
- **Authority:** each node has a multiplayer authority (default 1). Set it with `set_multiplayer_authority(peer_id)`, usually on the player's root node, named after the peer ID so the paths match on every peer. Check it with `is_multiplayer_authority()`.
- **RPCs (Godot 4):**
  - Annotate with `@rpc("any_peer" | "authority", "call_local" | "call_remote", "reliable" | "unreliable" | "unreliable_ordered", channel)`.
  - Call with `my_func.rpc(args)` or `my_func.rpc_id(peer, args)`.
  - The default is authority-only, remote, reliable.
  - In a handler, `multiplayer.get_remote_sender_id()` tells you who called it. **Validate it on the server. Never trust `any_peer` input.**
- **`MultiplayerSpawner`**: replicates instancing of scenes on its spawnable list under its `spawn_path`. Only the authority adds the nodes; the others get them automatically. Use `spawn_function` for custom data.
- **`MultiplayerSynchronizer`**: replicates the properties listed in its `SceneReplicationConfig` (on spawn, always, or on change). Use visibility filters for interest management. Synchronizers sync state; RPCs carry events.
- RPCs and synchronizers resolve by **NodePath**, so the paths must be identical on every peer. Most "node not found" RPC errors come from mismatched names or spawn order.

## Architecture advice
- **Server-authoritative** for anything competitive: clients send inputs, and the server simulates and replicates state. Client-side prediction and reconciliation for the local player. Interpolate remote entities a little behind the latest state (about 100 ms buffer).
- Host-authoritative listen servers are fine for co-op.
- Choose reliable/unreliable per message type: inputs and transforms unreliable or unreliable_ordered; game events reliable. Use separate channels so a reliable backlog doesn't stall movement.
- Physics is not deterministic across machines, Jolt included. Don't rely on lockstep physics. Replicate the results.
- Bandwidth: quantize, send changes only, and use lower-rate updates for far entities.
- NAT traversal and lobbies are outside the engine: use Steam networking (GodotSteam), Epic Online Services, WebRTC with a signaling and TURN server, or a relay.
- Dedicated servers: export with the dedicated-server feature tag or `--headless`, and strip visuals using the "dedicated server" export mode.

## Low-level
- `PacketPeerUDP`, `StreamPeerTCP`, `TCPServer`, `HTTPRequest` (node), `HTTPClient` (low-level). `HTTPRequest` is the right default for REST calls. Use it with `await request_completed`.
- `JSON.parse_string()`/`JSON.stringify()`. For binary data, `var_to_bytes`/`bytes_to_var`. Never deserialize objects from untrusted peers: keep `allow_objects` false.
