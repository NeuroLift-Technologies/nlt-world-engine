// Copies the Godot project's own assets into public/godot/ so the viewer serves
// the same files the engine uses, rather than committed copies that could drift.
// Runs before dev and build. Fails loudly if a source is missing: a viewer that
// silently shipped without the world's fixtures would misrepresent what it shows.
import { cpSync, existsSync, mkdirSync, rmSync, statSync } from 'node:fs';
import { dirname, join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const here = dirname(fileURLToPath(import.meta.url));
const repo = resolve(here, '../../..');
const godot = join(repo, 'world-engine-godot');
const out = resolve(here, '../public/godot');

// [source relative to world-engine-godot, destination relative to public/godot]. A source starting
// with '/' is relative to the repo root instead.
const FILES = [
  // A real headless engine run, recorded as nlt.observer-trace.v1 (fixtures/observer-trace/README.md).
  ['/fixtures/observer-trace/sample.jsonl', 'fixtures/observer-trace-sample.jsonl'],
  ['fixtures/replay/stayalert-day.json', 'fixtures/stayalert-day.json'],
  ['fixtures/replay/open-world-day.json', 'fixtures/open-world-day.json'],
  ['fixtures/replay/collapse-only.json', 'fixtures/collapse-only.json'],
  ['fixtures/replay/rescue-only.json', 'fixtures/rescue-only.json'],
  // Self-authored Blender probe resident (ASSET-MANIFEST.md row: project-owned).
  ['assets/characters/_pipeline_probe/nlt_resident_walk.glb', 'characters/nlt_resident_walk.glb'],
  // Project-owned interior levels (ASSET-MANIFEST.md rows: self-authored UE exports).
  ['assets/levels/Personal_Level.fbx', 'levels/Personal_Level.fbx'],
  ['assets/levels/Workplace_Level.fbx', 'levels/Workplace_Level.fbx'],
  ['assets/levels/Social_Level.fbx', 'levels/Social_Level.fbx'],
  ['assets/levels/Academic_Level.fbx', 'levels/Academic_Level.fbx'],
];

const from = (src) => (src.startsWith('/') ? join(repo, src) : join(godot, src));
const missing = FILES.filter(([src]) => !existsSync(from(src)));
if (missing.length) {
  console.error('[sync-godot-assets] missing:\n  ' + missing.map(([s]) => (s.startsWith('/') ? s.slice(1) : `world-engine-godot/${s}`)).join('\n  '));
  console.error('If this build runs on Vercel, enable "Include files outside the Root Directory".');
  process.exit(1);
}
rmSync(out, { recursive: true, force: true });
let bytes = 0;
for (const [src, dst] of FILES) {
  mkdirSync(dirname(join(out, dst)), { recursive: true });
  cpSync(from(src), join(out, dst));
  bytes += statSync(join(out, dst)).size;
}
console.log(`[sync-godot-assets] ${FILES.length} files, ${(bytes / 1024).toFixed(0)} KB -> public/godot/`);
