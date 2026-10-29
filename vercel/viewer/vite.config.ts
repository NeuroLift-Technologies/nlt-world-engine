import { defineConfig } from 'vite';
import { resolve, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const here = dirname(fileURLToPath(import.meta.url));

export default defineConfig({
  root: '.',
  base: './',
  build: {
    outDir: 'dist',
    emptyOutDir: true,
    sourcemap: false,
    minify: 'oxc',
    target: 'es2022',
    chunkSizeWarningLimit: 900,
    rollupOptions: {
      input: {
        main: resolve(here, 'index.html'),
        trace: resolve(here, 'trace.html'),
      },
    },
  },
  server: {
    port: 5173,
    strictPort: false,
    // trace.html's built-in trace is the shared contract fixture, outside this app's root. Allow
    // that one folder, not the repo: the dev server would otherwise serve any file under it.
    fs: { allow: ['.', '../../fixtures/observer-trace'] },
  },
});
