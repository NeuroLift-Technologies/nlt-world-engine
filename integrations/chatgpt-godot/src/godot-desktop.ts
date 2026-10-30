import { Client } from "@modelcontextprotocol/sdk/client/index.js";
import { StdioClientTransport } from "@modelcontextprotocol/sdk/client/stdio.js";
import { BRIDGE_PACKAGE, PROJECT_ROOT, READ_ONLY } from "./config.js";

type RemoteTool = {
  name: string;
  description?: string;
  inputSchema?: Record<string, unknown>;
  annotations?: Record<string, unknown>;
};

let client: Client | undefined;
let transport: StdioClientTransport | undefined;
let connecting: Promise<Client> | undefined;

function bridgeCommand(): { command: string; args: string[] } {
  if (process.platform === "win32") {
    return { command: process.env.ComSpec ?? "cmd.exe", args: ["/d", "/s", "/c", "npx", "-y", BRIDGE_PACKAGE] };
  }
  return { command: process.env.NPX_BIN ?? "npx", args: ["-y", BRIDGE_PACKAGE] };
}

function childEnvironment(): Record<string, string> {
  const inherited = Object.fromEntries(
    Object.entries(process.env).filter((entry): entry is [string, string] => typeof entry[1] === "string")
  );
  return {
    ...inherited,
    GODOT_MCP_CONFIG_VERSION: "1",
    GODOT_MCP_PROJECT_PATH: PROJECT_ROOT,
    ...(READ_ONLY ? { GODOT_MCP_READ_ONLY: "1" } : {})
  };
}

export async function getDesktopClient(): Promise<Client> {
  if (client) return client;
  if (connecting) return connecting;

  connecting = (async () => {
    const launch = bridgeCommand();
    transport = new StdioClientTransport({
      command: launch.command,
      args: launch.args,
      cwd: PROJECT_ROOT,
      env: childEnvironment()
    });
    const next = new Client({ name: "nlt-chatgpt-godot", version: "0.1.0" });
    await next.connect(transport);
    client = next;
    return next;
  })();

  try {
    return await connecting;
  } finally {
    connecting = undefined;
  }
}

export async function desktopStatus(): Promise<Record<string, unknown>> {
  try {
    const connected = await getDesktopClient();
    const result = await connected.listTools();
    return {
      connected: true,
      projectRoot: PROJECT_ROOT,
      bridgePackage: BRIDGE_PACKAGE,
      readOnly: READ_ONLY,
      toolCount: result.tools.length,
      tools: result.tools.map((tool) => tool.name)
    };
  } catch (error) {
    return {
      connected: false,
      projectRoot: PROJECT_ROOT,
      bridgePackage: BRIDGE_PACKAGE,
      readOnly: READ_ONLY,
      reason: error instanceof Error ? error.message : String(error),
      hint: "Open the Godot 4.7.2 .NET editor with the Godot MCP Toolkit enabled, then retry."
    };
  }
}

export async function listDesktopTools(): Promise<RemoteTool[]> {
  const connected = await getDesktopClient();
  const result = await connected.listTools();
  return result.tools as RemoteTool[];
}

export async function callDesktopReadOnlyTool(name: string, args: Record<string, unknown>): Promise<unknown> {
  const connected = await getDesktopClient();
  const tools = await connected.listTools();
  const selected = tools.tools.find((tool) => tool.name === name);
  if (!selected) {
    throw new Error(`Unknown desktop Godot tool: ${name}. Call desktop_list_tools first.`);
  }
  if (selected.annotations?.readOnlyHint !== true || selected.annotations?.destructiveHint === true) {
    throw new Error("This operation is not explicitly annotated read-only by the Godot MCP Toolkit. Use desktop_call_tool and obtain user approval.");
  }
  return connected.callTool({ name, arguments: args });
}

export async function callDesktopTool(name: string, args: Record<string, unknown>): Promise<unknown> {
  const connected = await getDesktopClient();
  const tools = await connected.listTools();
  const selected = tools.tools.find((tool) => tool.name === name);
  if (!selected) {
    throw new Error(`Unknown desktop Godot tool: ${name}. Call desktop_list_tools first.`);
  }
  if (READ_ONLY && selected.annotations?.readOnlyHint !== true) {
    throw new Error("This session is read-only. Only tools explicitly annotated readOnlyHint=true are allowed. Set GODOT_MCP_READ_ONLY=0 locally and restart only if you explicitly authorize mutations.");
  }
  return connected.callTool({ name, arguments: args });
}
