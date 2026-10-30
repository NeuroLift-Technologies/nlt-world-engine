import { createServer } from "node:http";
import { McpServer } from "@modelcontextprotocol/sdk/server/mcp.js";
import { StreamableHTTPServerTransport } from "@modelcontextprotocol/sdk/server/streamableHttp.js";
import { z } from "zod";
import { assertProjectRoot, HOST, PORT, PROJECT_ROOT, READ_ONLY, REPO_ROOT } from "./config.js";
import { callDesktopReadOnlyTool, callDesktopTool, desktopStatus, listDesktopTools } from "./godot-desktop.js";
import { headlessStatus, runHeadless, validateHeadless } from "./headless.js";
import { listSkillFiles, readSkillFile } from "./skill.js";

assertProjectRoot();

const server = new McpServer({
  name: "NLT Godot for ChatGPT",
  version: "0.1.0"
});

const empty = z.object({});
const commandResult = z.object({
  command: z.string(),
  args: z.array(z.string()),
  exitCode: z.number().nullable(),
  signal: z.string().nullable(),
  timedOut: z.boolean(),
  durationMs: z.number(),
  stdout: z.string(),
  stderr: z.string()
});

server.registerTool("godot_connection_status", {
  title: "Godot connection status",
  description: "Report the local Godot project, desktop MCP bridge availability, headless binary availability, and session safety mode.",
  inputSchema: empty,
  annotations: { readOnlyHint: true, destructiveHint: false, idempotentHint: true }
}, async () => {
  const [desktop, headless] = await Promise.all([desktopStatus(), headlessStatus().catch((error) => ({ available: false, reason: String(error) }))]);
  return { content: [{ type: "text", text: JSON.stringify({ projectRoot: PROJECT_ROOT, readOnly: READ_ONLY, desktop, headless }, null, 2) }] };
});

server.registerTool("desktop_list_tools", {
  title: "List desktop Godot tools",
  description: "Discover the live tools exposed by the existing Godot MCP Toolkit in the running desktop editor. Does not change the project.",
  inputSchema: empty,
  annotations: { readOnlyHint: true, destructiveHint: false, idempotentHint: true }
}, async () => {
  const tools = await listDesktopTools();
  return { content: [{ type: "text", text: JSON.stringify(tools, null, 2) }] };
});

server.registerTool("desktop_call_readonly_tool", {
  title: "Call a read-only desktop Godot tool",
  description: "Invoke only a Godot MCP Toolkit tool explicitly annotated readOnlyHint=true and not destructive. Use this for inspection in the default read-only session.",
  inputSchema: {
    tool_name: z.string().min(1),
    arguments: z.record(z.unknown()).default({})
  },
  annotations: { readOnlyHint: true, destructiveHint: false, idempotentHint: true }
}, async ({ tool_name, arguments: args }) => {
  const result = await callDesktopReadOnlyTool(tool_name, args);
  return { content: [{ type: "text", text: JSON.stringify(result, null, 2) }] };
});

server.registerTool("desktop_call_tool", {
  title: "Call a desktop Godot tool",
  description: "Invoke one named tool from the running Godot MCP Toolkit. This generic dispatcher is marked destructive because the remote tool may mutate the project; inspect desktop_list_tools and obtain user authorization before calling write-capable operations.",
  inputSchema: {
    tool_name: z.string().min(1),
    arguments: z.record(z.unknown()).default({})
  },
  annotations: { readOnlyHint: false, destructiveHint: true, idempotentHint: false }
}, async ({ tool_name, arguments: args }) => {
  const result = await callDesktopTool(tool_name, args);
  return { content: [{ type: "text", text: JSON.stringify(result, null, 2) }] };
});

server.registerTool("headless_validate_project", {
  title: "Validate Godot project headlessly",
  description: "Run the repo's .NET build, Godot headless asset import, and a headless project startup/quit check. Writes normal build and import outputs; no arbitrary shell commands are accepted.",
  inputSchema: empty,
  annotations: { readOnlyHint: false, destructiveHint: true, idempotentHint: false }
}, async () => {
  const results = await validateHeadless();
  const passed = results.length === 3 && results.every((item) => item.exitCode === 0 && !item.timedOut);
  return { content: [{ type: "text", text: JSON.stringify({ passed, results }, null, 2) }], isError: !passed };
});

server.registerTool("headless_run_project", {
  title: "Run Godot headlessly",
  description: "Run the authoritative Godot project without rendering for a bounded number of main-loop iterations. This launches the simulation process and is marked destructive.",
  inputSchema: { iterations: z.number().int().min(1).max(1_000_000).default(120) },
  annotations: { readOnlyHint: false, destructiveHint: true, idempotentHint: false }
}, async ({ iterations }) => {
  const result = await runHeadless(iterations);
  const passed = result.exitCode === 0 && !result.timedOut;
  return { content: [{ type: "text", text: JSON.stringify({ passed, result }, null, 2) }], isError: !passed };
});

server.registerTool("godot_skill_list", {
  title: "List Godot engineering skill files",
  description: "List the source files in the existing .claude/skills/godot-senior-engineer directory. ChatGPT reads these directly; the skill is not copied or forked.",
  inputSchema: empty,
  annotations: { readOnlyHint: true, destructiveHint: false, idempotentHint: true }
}, async () => {
  const files = await listSkillFiles();
  return { content: [{ type: "text", text: JSON.stringify({ source: ".claude/skills/godot-senior-engineer", files }, null, 2) }] };
});

server.registerTool("godot_skill_read", {
  title: "Read Godot engineering guidance",
  description: "Read SKILL.md, a subsystem reference, evaluation asset, or API checker from the existing .claude/skills/godot-senior-engineer directory. Paths are restricted to that directory.",
  inputSchema: { relative_path: z.string().min(1) },
  annotations: { readOnlyHint: true, destructiveHint: false, idempotentHint: true }
}, async ({ relative_path }) => {
  const content = await readSkillFile(relative_path);
  return { content: [{ type: "text", text: content }] };
});

server.registerTool("nlt_project_context", {
  title: "Read NLT project authority",
  description: "Read project governance and architecture context needed before implementing Godot changes. Supports AGENTS.md, NLT-DEV-OTOI.md, README.md, and the Godot agent-loop contract.",
  inputSchema: {
    document: z.enum(["AGENTS.md", "NLT-DEV-OTOI.md", "README.md", "docs/agent-loop.md", "docs/contracts/agent-loop-v1.md"])
  },
  annotations: { readOnlyHint: true, destructiveHint: false, idempotentHint: true }
}, async ({ document }) => {
  const target = document.startsWith("docs/") ? pathJoin(REPO_ROOT, document) : pathJoin(REPO_ROOT, document);
  const content = await import("node:fs/promises").then((fs) => fs.readFile(target, "utf8"));
  return { content: [{ type: "text", text: content }] };
});

function pathJoin(root: string, relative: string): string {
  return root + "/" + relative;
}

const transport = new StreamableHTTPServerTransport({
  sessionIdGenerator: undefined
});
await server.connect(transport);

const httpServer = createServer(async (request, response) => {
  if (request.url === "/healthz" && request.method === "GET") {
    response.writeHead(200, { "content-type": "application/json" });
    response.end(JSON.stringify({ ok: true, name: "NLT Godot for ChatGPT", version: "0.1.0" }));
    return;
  }
  if (request.url !== "/mcp") {
    response.writeHead(404);
    response.end("Not found");
    return;
  }
  try {
    await transport.handleRequest(request, response);
  } catch (error) {
    if (!response.headersSent) response.writeHead(500, { "content-type": "text/plain" });
    response.end(error instanceof Error ? error.message : String(error));
  }
});

httpServer.listen(PORT, HOST, () => {
  process.stderr.write(`NLT Godot for ChatGPT listening at http://${HOST}:${PORT}/mcp\n`);
  process.stderr.write(`Project: ${PROJECT_ROOT}\nRead-only desktop bridge: ${READ_ONLY}\nSecure MCP Tunnel is required for ChatGPT access.\n`);
});

for (const signal of ["SIGINT", "SIGTERM"] as const) {
  process.on(signal, () => {
    httpServer.close();
    void transport.close();
    void server.close();
  });
}
