import assert from 'node:assert/strict';
import { readdirSync, readFileSync, statSync } from 'node:fs';
import { join } from 'node:path';
import { describe, it } from 'node:test';

// This package is "type": "module". Vercel runs api/ as native ES modules, where a relative
// import must name its file extension. TypeScript and these tests accept the bare form, so the
// failure only shows up as FUNCTION_INVOCATION_FAILED after deploy. Catch it here instead.

function sources(dir: string): string[] {
  return readdirSync(dir).flatMap((name) => {
    const path = join(dir, name);
    if (statSync(path).isDirectory()) return sources(path);
    return path.endsWith('.ts') ? [path] : [];
  });
}

const RELATIVE_IMPORT = /\b(?:from|import)\s*\(?\s*['"](\.{1,2}\/[^'"]*)['"]/g;

describe('api/ relative imports', () => {
  for (const file of sources(new URL('../api', import.meta.url).pathname)) {
    it(`${file.split('/api/')[1]} names the extension on every relative import`, () => {
      const text = readFileSync(file, 'utf8');
      const bare = [...text.matchAll(RELATIVE_IMPORT)].map((m) => m[1]).filter((spec) => !/\.[cm]?[jt]s$/.test(spec));
      assert.deepEqual(bare, []);
    });
  }

  it('the check itself catches a bare specifier', () => {
    const sample = "import { x } from './_lib/thing';\nimport { y } from './ok.js';";
    const bare = [...sample.matchAll(RELATIVE_IMPORT)].map((m) => m[1]).filter((spec) => !/\.[cm]?[jt]s$/.test(spec));
    assert.deepEqual(bare, ['./_lib/thing']);
  });
});
