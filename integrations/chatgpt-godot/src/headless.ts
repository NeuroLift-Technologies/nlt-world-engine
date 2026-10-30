import { spawn } from "node:child_process";
import fs from "node:fs";
import path from "node:path";
import { DOTNET_BIN, GODOT_BIN, PROJECT_ROOT } from "./config.js";

export type CommandResult = {
  command: string;
  args: string[];
  exitCode: number | null;
  signal: NodeJS.Signals | null;
  timedOut: boolean;
  durationMs: number;
  stdout: string;
  stderr: string;
};

function requireProject(): void {
  if (!fs.existsSync(path.join(PROJECT_ROOT, "project.godot"))) {
    throw new Error(`No project.godot found at ${PROJECT_ROOT}. Set GODOT_PROJECT_PATH to the Godot project directory.`);
  }
}

export function buildHeadlessArgs(iterations: number): string[] {
  if (!Number.isInteger(iterations) || iterations < 1 || iterations > 1_000_000) {
    throw new Error("iterations must be an integer between 1 and 1,000,000.");
  }
  return ["--headless", "--path", PROJECT_ROOT, "--quit-after", String(iterations)];
}

export function runCommand(command: string, args: string[], timeoutMs = 600_000): Promise<CommandResult> {
  return new Promise((resolve, reject) => {
    const started = Date.now();
    const child = spawn(command, args, {
      cwd: PROJECT_ROOT,
      env: process.env,
      windowsHide: true,
      shell: false,
      stdio: ["ignore", "pipe", "pipe"]
    });
    let stdout = "";
    let stderr = "";
    let timedOut = false;
    const maxOutput = 1_000_000;
    child.stdout.setEncoding("utf8");
    child.stderr.setEncoding("utf8");
    child.stdout.on("data", (chunk: string) => { stdout = (stdout + chunk).slice(-maxOutput); });
    child.stderr.on("data", (chunk: string) => { stderr = (stderr + chunk).slice(-maxOutput); });
    const timer = setTimeout(() => {
      timedOut = true;
      child.kill("SIGTERM");
      setTimeout(() => child.kill("SIGKILL"), 5_000).unref();
    }, timeoutMs);
    child.on("error", (error) => {
      clearTimeout(timer);
      reject(error);
    });
    child.on("close", (exitCode, signal) => {
      clearTimeout(timer);
      resolve({
        command,
        args,
        exitCode,
        signal,
        timedOut,
        durationMs: Date.now() - started,
        stdout,
        stderr
      });
    });
  });
}

export async function headlessStatus(): Promise<Record<string, unknown>> {
  requireProject();
  const [godot, dotnet] = await Promise.all([
    runCommand(GODOT_BIN, ["--version"], 15_000),
    runCommand(DOTNET_BIN, ["--version"], 15_000)
  ]);
  return {
    mode: "headless",
    projectRoot: PROJECT_ROOT,
    godot: { available: godot.exitCode === 0, version: godot.stdout.trim(), error: godot.stderr.trim() },
    dotnet: { available: dotnet.exitCode === 0, version: dotnet.stdout.trim(), error: dotnet.stderr.trim() }
  };
}

export async function validateHeadless(): Promise<CommandResult[]> {
  requireProject();
  const build = await runCommand(DOTNET_BIN, ["build", path.join(PROJECT_ROOT, "world-engine-godot.csproj"), "--nologo"], 600_000);
  if (build.exitCode !== 0 || build.timedOut) return [build];

  const import = await runCommand(GODOT_BIN, ["--headless", "--import", "--path", PROJECT_ROOT], 600_000);
  if (import.exitCode !== 0 || import.timedOut) return [build, import];

  const parse = await runCommand(GODOT_BIN, ["--headless", "--path", PROJECT_ROOT, "--quit"], 120_000);
  return [build, import, parse];
}

export async function runHeadless(iterations: number): Promise<CommandResult> {
  requireProject();
  return runCommand(GODOT_BIN, buildHeadlessArgs(iterations), 120_000);
}
