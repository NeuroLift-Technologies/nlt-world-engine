// Weather: rain particle system + overcast mode.
//
// Rain is rendered as a GPU points system using a custom shader.
// Droplets fall from a volume above the camera, wrap around (recycled),
// and streak downward with a length proportional to fall speed.
// An intensity slider fades in/out the effect.
//
// API
//   buildWeather(scene, config) → {
//     update(dt, camera, overcast),
//     setIntensity(0..1),
//     setOvercast(0..1),
//     get intensity, get overcast
//   }
//
import * as THREE from 'three';

// ── Shaders ────────────────────────────────────────────────────────────────

const RAIN_VERT = /* glsl */`
  attribute float aLen;      // streak length
  uniform float uSize;       // world-space pixel scale
  uniform float uTime;
  varying float vAlpha;
  varying float vLen;

  void main() {
    vAlpha = 1.0;
    vLen   = aLen;
    vec4 mvPos = modelViewMatrix * vec4(position, 1.0);
    gl_PointSize = uSize * (1.0 / -mvPos.z);
    gl_Position  = projectionMatrix * mvPos;
  }
`;

const RAIN_FRAG = /* glsl */`
  uniform float uIntensity;
  varying float vAlpha;
  varying float vLen;

  void main() {
    // Elongate each point into a vertical streak
    vec2 uv = gl_PointCoord - 0.5;
    // aspect: each point is square, stretch vertically
    float streak = smoothstep(0.5, 0.0, abs(uv.x) * 6.0)
                 * smoothstep(0.5, 0.0, abs(uv.y) - vLen * 0.5 + 0.5);
    if (streak < 0.05) discard;
    float alpha = streak * uIntensity * 0.55;
    gl_FragColor = vec4(0.72, 0.82, 0.92, alpha);
  }
`;

// ── Constants ──────────────────────────────────────────────────────────────
const POOL_SIZE    = 14000;  // max simultaneous droplets
const SPAWN_RADIUS = 120;    // horizontal spawn box half-size around camera
const SPAWN_HEIGHT = 55;     // how high above camera to spawn
const FALL_SPEED   = 26;     // m/s base fall speed
const WIND_X       = 1.8;    // slight sideways drift
const RECYCLE_Y    = -8;     // recycled when this far below camera

// ── Build ──────────────────────────────────────────────────────────────────
export function buildWeather(scene, config) {
  const intensity = config.intensity ?? 0.0;
  const enabled   = intensity > 0;

  // ── Geometry ─────────────────────────────────────────────────────────────
  const positions = new Float32Array(POOL_SIZE * 3);
  const lengths   = new Float32Array(POOL_SIZE);

  // Randomise initial positions in the spawn volume
  for (let i = 0; i < POOL_SIZE; i++) {
    positions[i * 3]     = (Math.random() - 0.5) * SPAWN_RADIUS * 2;
    positions[i * 3 + 1] = Math.random() * SPAWN_HEIGHT;
    positions[i * 3 + 2] = (Math.random() - 0.5) * SPAWN_RADIUS * 2;
    lengths[i] = 0.28 + Math.random() * 0.32;
  }

  const geo = new THREE.BufferGeometry();
  geo.setAttribute('position', new THREE.BufferAttribute(positions, 3));
  geo.setAttribute('aLen',     new THREE.BufferAttribute(lengths, 1));

  // ── Material ──────────────────────────────────────────────────────────────
  const mat = new THREE.ShaderMaterial({
    uniforms: {
      uSize:      { value: 220.0 },
      uIntensity: { value: intensity },
      uTime:      { value: 0.0 },
    },
    vertexShader:   RAIN_VERT,
    fragmentShader: RAIN_FRAG,
    transparent:    true,
    depthWrite:     false,
    blending:       THREE.AdditiveBlending,
    fog:            false,
  });

  const points = new THREE.Points(geo, mat);
  points.name          = 'rain';
  points.frustumCulled = false;
  points.visible       = false; // start hidden
  scene.add(points);

  // ── State ──────────────────────────────────────────────────────────────────
  let _intensity = intensity;
  let _overcast  = 0;
  let _elapsed   = 0;
  const _camPos  = new THREE.Vector3();

  function setIntensity(v) {
    _intensity = THREE.MathUtils.clamp(v, 0, 1);
    mat.uniforms.uIntensity.value = _intensity;
    points.visible = _intensity > 0.01;
  }

  function setOvercast(v) {
    _overcast = THREE.MathUtils.clamp(v, 0, 1);
  }

  /**
   * Call once per frame from the main loop.
   * @param {number} dt          Delta time in seconds
   * @param {THREE.Camera} camera Current camera (rain volume follows it)
   */
  function update(dt, camera) {
    if (_intensity < 0.01) return;

    _elapsed += dt;
    mat.uniforms.uTime.value = _elapsed;

    camera.getWorldPosition(_camPos);

    const pos     = geo.attributes.position.array;
    const fallDt  = FALL_SPEED * dt * (0.8 + _intensity * 0.4);
    const windDt  = WIND_X * dt;

    for (let i = 0; i < POOL_SIZE; i++) {
      const idx = i * 3;
      pos[idx]     += windDt;
      pos[idx + 1] -= fallDt;

      // Recycle droplets that have fallen out of the view volume
      const relX = pos[idx]     - _camPos.x;
      const relY = pos[idx + 1] - _camPos.y;
      const relZ = pos[idx + 2] - _camPos.z;

      if (relY < RECYCLE_Y ||
          Math.abs(relX) > SPAWN_RADIUS ||
          Math.abs(relZ) > SPAWN_RADIUS) {
        pos[idx]     = _camPos.x + (Math.random() - 0.5) * SPAWN_RADIUS * 2;
        pos[idx + 1] = _camPos.y + SPAWN_HEIGHT - Math.random() * 8;
        pos[idx + 2] = _camPos.z + (Math.random() - 0.5) * SPAWN_RADIUS * 2;
      }
    }

    geo.attributes.position.needsUpdate = true;
  }

  // expose read-only state for main.js
  Object.defineProperties({ setIntensity, setOvercast, update }, {
    intensity: { get: () => _intensity },
    overcast:  { get: () => _overcast },
  });

  return {
    points,
    update,
    setIntensity,
    setOvercast,
    get intensity() { return _intensity; },
    get overcast()  { return _overcast;  },
  };
}
