// All tunables in one place. Nothing else hardcodes world constants.
export const CONFIG = {
  world: {
    size: 512,            // world extent in meters (square)
    segments: 256,        // terrain mesh resolution
    heightScale: 26,      // max terrain elevation
    seaLevel: 2.2,        // water plane height
    seed: 1337,
  },

  sky: {
    sunElevationDeg: 42,
    sunAzimuthDeg: 135,
    exposure: 0.6,
    // FogExp2 density by time-of-day / weather state.
    // Larger value = shorter view distance (denser fog).
    fog: {
      densityNoon:  0.0016,  // exp2 density (~550 m visibility)
      densityNight: 0.0048,  // denser at night — terrain melts to darkness
      densityRain:  0.0035,  // extra density during rain / overcast
    },
  },

  // ── Atmosphere ──────────────────────────────────────────────────────────
  atmosphere: {
    clouds: {
      altitude:   110,           // metres above sea level
      radius:     1800,          // cloud plane half-extent (m); should exceed draw distance
      coverage:   0.42,          // 0 = clear sky, 1 = 100% covered (overcast overrides)
      density:    2.8,           // FBM threshold sharpness (higher = harder cloud edges)
      windDir:    { x: 1.0, y: 0.4 }, // horizontal wind direction (will be normalised)
      windSpeed:  1.0,           // multiplier applied to scrolling speed
    },
    rain: {
      poolSize:    14000,        // max simultaneous rain droplets
      spawnRadius: 120,          // horizontal spawn box half-size around camera (m)
      spawnHeight: 55,           // how far above camera droplets spawn (m)
      fallSpeed:   26,           // base fall speed (m/s)
      windDriftX:  1.8,          // lateral wind drift on rain (m/s)
    },
  },

  water: {
    colorShallow: 0x2e8b9a,
    colorDeep:    0x0b3d5c,
    opacity:      0.82,
    normalScale:  0.6,
    ior:          1.33,
    transmission: 0.3,
  },

  vegetation: {
    treeCount:   700,
    grassCount:  9000,
    rockCount:   220,
    textureSize: 256,
  },

  player: {
    walkSpeed:        14,
    sprintMultiplier: 2.4,
    eyeHeight:        2.4,
  },

  quality: {
    pixelRatioMax: 2,
    shadows: true,
    shadowMapSize: 2048,
    antialias: true,
  },
  pbr: {
    textureSize: 512,
    terrainDetailSize: 512, // resolution of procedural terrain detail maps
    terrainTileSize: 8,     // meters per terrain detail tile (tiling repeat)
    terrainNormalScale: 1.6, // strength of terrain normal-map perturbation
  },
  // ── HDR environment lighting (Image-Based Lighting) ─────────────────────
  // HDRIs were sourced by searching https://polyhaven.com/hdris. All CC0;
  // "Pure Sky" equirectangular HDRIs so sky reflections stay clean and don't
  // clash with the engine's own terrain/water. Two presets drive the IBL:
  //   * clear    — midday, clear, high-contrast sky (default daytime lighting)
  //   * overcast — flat overcast sky (used for overcast + rain weather states)
  // `loadEnvironment` (render/pipeline.js) loads the `default` preset at boot,
  // `preloadPresets` eager-loads the rest, and `setEnvironmentPreset` swaps
  // at runtime when the weather changes. If a download fails the procedural
  // gradient fallback keeps the world lit (no black screen).
  envMap: {
    presets: {
      clear:    'https://dl.polyhaven.org/file/ph-assets/HDRIs/hdr/2k/kloofendal_43d_clear_puresky_2k.hdr',
      overcast: 'https://dl.polyhaven.org/file/ph-assets/HDRIs/hdr/2k/kloofendal_overcast_puresky_2k.hdr',
    },
    default: 'clear',
    envMapIntensity: 1.0,
    pmremBlur:  0.4,
    procedural: true,            // fallback if a preset HDR fails to load
  },

  // ── GLB character models ────────────────────────────────────────────────
  // Animated humans replacing the procedural resident bodies. `model` is a
  // shared GLB loaded once and cloned per resident; `height` is the target
  // standing height (m) the GLB is auto-scaled to. The soldier from the three.js
  // examples is free + no-account (Mixamo rig: TPose/Idle/Walk/Run). Swap for a
  // civilian GLB (e.g. Xbot.glb) to change the look — see CHARACTER_MANIFEST.
  characters: {
    model:  'https://threejs.org/examples/models/gltf/Soldier.glb',
    height: 1.8,
  },
};
