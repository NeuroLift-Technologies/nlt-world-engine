// Lets Node load the viewer's own TypeScript in tests. The viewer is written for a bundler, so it
// imports './types' (no extension) or './types.js' for a .ts file; Node needs the real name.
export async function resolve(specifier, context, nextResolve) {
  try {
    return await nextResolve(specifier, context);
  } catch (err) {
    if (err?.code !== 'ERR_MODULE_NOT_FOUND' || !specifier.startsWith('.')) throw err;
    const guess = specifier.endsWith('.js') ? specifier.slice(0, -3) + '.ts' : specifier + '.ts';
    try {
      return await nextResolve(guess, context);
    } catch {
      throw err;
    }
  }
}
