import fs from "node:fs/promises";
import path from "node:path";
import { REPO_ROOT } from "./config.js";

const SKILL_ROOT = path.join(REPO_ROOT, ".claude", "skills", "godot-senior-engineer");

export async function listSkillFiles(): Promise<string[]> {
  const found: string[] = [];
  async function walk(dir: string): Promise<void> {
    for (const entry of await fs.readdir(dir, { withFileTypes: true })) {
      const absolute = path.join(dir, entry.name);
      if (entry.isDirectory()) await walk(absolute);
      else if (entry.isFile() && /\.(md|py|json)$/i.test(entry.name)) {
        found.push(path.relative(SKILL_ROOT, absolute).split(path.sep).join("/"));
      }
    }
  }
  await walk(SKILL_ROOT);
  return found.sort();
}

export async function readSkillFile(relativePath: string): Promise<string> {
  if (!relativePath || path.isAbsolute(relativePath) || relativePath.includes("\\") || relativePath.split("/").some((part) => part === ".." || part === ".")) {
    throw new Error("Use a relative path inside the godot-senior-engineer skill.");
  }
  if (!/\.(md|py|json)$/i.test(relativePath)) {
    throw new Error("Only Markdown, Python reference scripts, and JSON skill assets can be read.");
  }
  const target = path.resolve(SKILL_ROOT, relativePath);
  if (!target.startsWith(SKILL_ROOT + path.sep)) {
    throw new Error("Skill path escapes the approved skill directory.");
  }
  return fs.readFile(target, "utf8");
}
