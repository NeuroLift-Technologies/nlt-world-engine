# Transport

Explicit, versioned contracts between simulation state and the viewer. Reuse existing
contracts in `docs/contracts/state-feed-v1.md` (observer/projection feed) and
`docs/contracts/agent-loop-v1.md` (physical perception/intent boundary). Keep observer/
presentation data distinct from agent-loop execution requests. Never expose loopback
`POST /agent-loop/perception` publicly; viewer uses an authorized observer feed/relay.
