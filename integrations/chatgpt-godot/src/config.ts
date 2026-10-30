import path from "node:path";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
export const REPO_ROOT = path.resolve(here, "../../..");

function existingProjectRoot(): string {
  const candidate = process.env.GODOT_PROJECT_PATH
    ? path.resolve(process.env.GODOT_PROJECT_PATH)
    : path.join(REPO_ROOT, "world-engine-godot");
  return candidate;
}

export const PROJECT_ROOT = existingProjectRoot();
export const GODOT_BIN = process.env.GODOT_BIN ?? (process.platform === "win32" ? "godot.exe" : "godot");
export const DOTNET_BIN = process.env.DOTNET_BIN ?? "dotnet";
export const HOST = process.env.MCP_HOST ?? "127.0.0.1";
export const PORT = Number.parseInt(process.env.MCP_PORT ?? "8787", 10);
export const READ_ONLY = process.env.GODOT_MCP_READ_ONLY !== "0";
export const BRIDGE_PACKAGE = process.env.GODOT_MCP_PACKAGE ?? "@npgamedev/godot-mcp-server@1.0.4";

export function assertProjectRoot(): void {
  if (!Number.isInteger(PORT) || PORT < 1 || PORT > 65535) {
    throw new Error("MCP_PORT must be a valid TCP port.");
  }
  if (HOST !== "127.0.0.1" && HOST !== "::1" && HOST !== "localhost") {
    throw new Error("The local MCP server must bind to loopback. Use Secure MCP Tunnel for remote ChatGPT access.");
  }
}
