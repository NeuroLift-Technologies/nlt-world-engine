# vercel/ workspace

Dedicated Vercel application workspace for the NLT World Engine. The existing `web/`
public-facing website is unchanged; this workspace hosts the interactive World Engine
Viewer as a separate deployable application.

## Boundaries
- Godot World Engine: authoritative physical state, world time/space, collision, movement.
- AI-Fusion: semantic intelligence, agent-loop reasoning, intent generation, training.
- ASFDK-C#: governance enforcement at the applicable execution boundary.
- MCP Worker: one component, not final authority.
- Viewer: human-facing observation/presentation only; never an alternative simulation authority.
- Transport: explicit, versioned contracts between simulation state and viewer.

Principle: Fusion owns semantic reality; the World Engine owns physical reality.

## Structure
- viewer/ — interactive World Engine Viewer (Vercel root candidate)
- python/ — optional API/feed source; hosting TBD (not a persistent Vercel service by default)
- transport/ — observer feed contracts and transport adapters

## Security
- `POST /agent-loop/perception` is loopback-only and must not be exposed publicly.
- A deployed Vercel frontend cannot reach 127.0.0.1; use an explicit authorized transport
  (e.g. server-side relay / signed observer feed), never a public proxy of localhost.
