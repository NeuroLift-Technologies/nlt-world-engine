import { defineConfig } from 'vite';

export default defineConfig({
  root: '.',
  base: './',
  build: {
    outDir: 'dist',
    emptyOutDir: true,
    sourcemap: false,
    minify: 'oxc',
  },
  server: {
    port: 5173,
    strictPort: false,
    // The built-in trace is the shared contract fixture, outside this app's root. Allow that one
    // folder, not the repo: the dev server would otherwise serve any file under it.
    fs: { allow: ['.', '../../fixtures/observer-trace'] },
  },
});
