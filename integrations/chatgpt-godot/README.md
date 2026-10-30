# NLT Godot for ChatGPT

A local-first ChatGPT app/plugin for the NLT World Engine. It exposes one MCP endpoint with two execution adapters:

- **Desktop adapter:** delegates to the repository's existing Godot MCP Toolkit through its pinned companion bridge. It does not reimplement editor operations.
- **Headless adapter:** invokes a narrow, allowlisted set of Godot 4.7.2 .NET and .NET CLI operations for build, import, startup validation, and bounded simulation runs.

The existing `.claude/skills/godot-senior-engineer` directory remains the source of engineering knowledge. ChatGPT reads the skill and references in place through MCP tools; this integration does not fork or rewrite the skill.

## Architecture

```text
ChatGPT
  |
  | MCP over Secure MCP Tunnel
  v
Local MCP endpoint (127.0.0.1:8787/mcp)
  |
  +-- Desktop adapter --> @npgamedev/godot-mcp-server@1.0.4
  |                         |
  |                         v
  |                    Godot MCP Toolkit
  |                    running in Godot Editor
  |
  +-- Headless adapter --> Godot 4.7.2 .NET CLI
  |
  +-- Skill reader ------> .claude/skills/godot-senior-engineer
```

ChatGPT cannot launch a local process itself. The local MCP endpoint therefore stays on the developer machine and is connected to ChatGPT through OpenAI Secure MCP Tunnel. Do not expose this server directly to the public internet or bind it to a LAN interface.

## Requirements

- Node.js 22+
- Godot 4.7.2 .NET (mono) on PATH, or configure `GODOT_BIN`
- .NET 8 SDK on PATH
- The repository's vendored `world-engine-godot/addons/godot_mcp_toolkit` enabled in the Godot Editor for desktop operations
- The toolkit's pinned bridge package, fetched by npx on first desktop connection

## Install and run

From the repository root:

```bash
cd integrations/chatgpt-godot
npm install
npm run build
npm start
```

For development:

```bash
npm run dev
```

The server binds only to `127.0.0.1:8787`. Check `http://127.0.0.1:8787/healthz` locally. The MCP endpoint is `http://127.0.0.1:8787/mcp`.

## Connect ChatGPT

Use OpenAI's **Secure MCP Tunnel** for the local MCP endpoint. Configure the tunnel to forward to `http://127.0.0.1:8787/mcp`, then create a custom MCP app/plugin in ChatGPT using the tunnel connection. Do not use a public unauthenticated reverse proxy.

ChatGPT custom MCP app setup is currently performed from ChatGPT on the web; Secure MCP Tunnel and custom-app availability depend on OpenAI account/workspace access. The repository includes the server implementation; it does not create or publish an app inside a ChatGPT account.

## Tools

| Tool | Adapter | Behavior |
|---|---|---|
| `godot_connection_status` | Both | Reports desktop bridge and headless binary status |
| `desktop_list_tools` | Desktop | Discovers the live toolkit tool list |
| `desktop_call_readonly_tool` | Desktop | Calls only tools explicitly annotated read-only by the toolkit |
| `desktop_call_tool` | Desktop | Calls a named toolkit tool; marked destructive because the selected operation may mutate |
| `headless_validate_project` | Headless | .NET build, Godot import, and startup/quit validation |
| `headless_run_project` | Headless | Runs the project for a bounded number of main-loop iterations |
| `godot_skill_list` | Knowledge | Lists the original Claude skill files |
| `godot_skill_read` | Knowledge | Reads the original skill or a reference file |
| `nlt_project_context` | Knowledge | Reads project governance and agent-loop documents |

## Safety model

- The HTTP listener rejects non-loopback bind addresses.
- Secure MCP Tunnel is the intended ChatGPT connection path.
- Desktop bridge starts in **read-only mode by default** (`GODOT_MCP_READ_ONLY=1`). The toolkit itself hides destructive tools in that mode.
- `desktop_call_readonly_tool` accepts only toolkit operations explicitly annotated `readOnlyHint=true`.
- `desktop_call_tool` is annotated destructive so ChatGPT can require confirmation. Read the discovered tool metadata before invoking it.
- Headless operations accept no shell strings, arbitrary executable paths, or arbitrary Godot arguments. Only fixed command templates are used.
- Headless build/import/run tools are marked destructive because they execute code and write normal build/import outputs.
- No LLM provider, cloud deployment, credentials, or project data store is introduced.
- The toolkit's own token authentication, loopback binding, and append-only audit log remain in force for desktop control.

To explicitly enable desktop mutations, set `GODOT_MCP_READ_ONLY=0` in the local process environment and restart this server. This does not remove ChatGPT's tool approval prompts or the toolkit's audit log.

## Configuration

| Variable | Default | Purpose |
|---|---|---|
| `GODOT_PROJECT_PATH` | repo's `world-engine-godot` | Godot project directory |
| `GODOT_BIN` | `godot.exe` on Windows, otherwise `godot` | Godot .NET executable |
| `DOTNET_BIN` | `dotnet` | .NET SDK executable |
| `MCP_HOST` | `127.0.0.1` | Must remain loopback |
| `MCP_PORT` | `8787` | Local MCP HTTP port |
| `GODOT_MCP_READ_ONLY` | enabled | Set to `0` only to allow toolkit mutations |
| `GODOT_MCP_PACKAGE` | `@npgamedev/godot-mcp-server@1.0.4` | Pinned desktop bridge package |

## Known boundaries

- The desktop adapter requires a running Godot Editor with the MCP Toolkit enabled. It cannot control a desktop editor that is closed.
- Headless execution is a separate process and does not expose editor-only APIs. It does not pretend editor tools are available in headless mode.
- The initial headless runner targets this repository's Godot project and C# build. General multi-project selection is intentionally not exposed yet.
- This first implementation does not deploy a public server, provision OAuth, create a Vercel project, or install the app in ChatGPT.
- No Fusion connection is created. Fusion remains outside the reviewer and Godot desktop-control boundary.

## References

- [Godot MCP Toolkit README](../../world-engine-godot/addons/godot_mcp_toolkit/README.md)
- [Toolkit compatibility matrix](../../world-engine-godot/addons/godot_mcp_toolkit/docs/compatibility.md)
- [Toolkit security recommendations](../../world-engine-godot/addons/godot_mcp_toolkit/docs/security-recommendations.md)
- [Senior Godot Engineer skill](../../.claude/skills/godot-senior-engineer/SKILL.md)
- [OpenAI custom MCP server guide](https://developers.openai.com/api/docs/guides/custom-mcp-server)
- [OpenAI Apps SDK quickstart](https://developers.openai.com/plugins/build/app-quickstart)
- [OpenAI Secure MCP Tunnel](https://developers.openai.com/api/docs/guides/secure-mcp-tunnel)
