# Animation

## Tool choice
- **`AnimationPlayer`**: keyframe almost anything: properties, method calls, audio, Bezier curves, and other animations. Animations live in `AnimationLibrary` resources; a name like `"library/anim"` refers to one in a non-default library.
- **`AnimationTree`**: blending and state logic on top of an AnimationPlayer's animations.
  - Root node types: `AnimationNodeStateMachine`, `AnimationNodeBlendTree`, `AnimationNodeBlendSpace1D/2D`.
  - Drive it by setting `parameters/...` paths, e.g. `tree.set("parameters/locomotion/blend_position", v)`.
  - Use `travel()` on the state machine playback for state changes. Use the conditions or expressions on transitions instead of polling.
  - When an AnimationTree is active, it owns the AnimationPlayer. Calling `play()` on the player does nothing useful.
- **`Tween`**: procedural, fire-and-forget motion in code (UI, juice, simple moves). Don't keyframe what a tween does better, and the reverse.
- **`AnimatedSprite2D`**: simple frame flipbooks.

## 3D characters
- Import from glTF. Set the import options for loop modes, root motion, and retargeting with a `BoneMap` + `SkeletonProfileHumanoid`, so you can share animations between rigs.
- Root motion: set `root_motion_track` on the AnimationTree. Each physics frame, read `get_root_motion_position()`/`rotation`, apply them to the `CharacterBody3D` velocity, then call `move_and_slide()`. The physics body drives the character; the animation only supplies the motion data.
- `AnimationMixer` callback mode should usually be Physics when animations drive physics bodies or hitboxes.
- `BoneAttachment3D` attaches props such as weapons and held items to bones.

## IK and procedural (4.6+)
- The **new IK framework** is built on `SkeletonModifier3D`. `IKModifier3D` comes with solvers `TwoBoneIK3D` (arms and legs), `SplineIK3D` (tails, spines), `FABRIK3D`, `CCDIK3D` and `JacobianIK3D`, plus twist and angular constraints.
- These replace `SkeletonIK3D`, which is marked deprecated in the 4.7.2 class reference. Other `SkeletonModifier3D` types: `LookAtModifier3D`, `SpringBoneSimulator3D` (hair and cloth jiggle), `RetargetModifier3D`.
- Modifiers run in tree order after the animation is applied. Order matters.
- Foot IK on uneven ground: raycast down from each foot, set the TwoBoneIK target, and offset the hips.
- On low-end CPUs, every IK chain and spring bone costs CPU every frame. Budget them and disable them for distant characters.

## Common bugs
- An animation "doesn't play": an AnimationTree is active, the animation is in a named library, autoplay is fighting your code, or the track paths broke after renaming nodes. Since 4.6, unique node IDs reduce rename breakage once scenes are re-saved.
- Jitter on animated physics bodies: the mixer runs in Idle mode while the body moves in Physics, or physics interpolation is off.
- A reset pose bleeding through: the `RESET` animation (used for "Reset on Save") is wrong or missing.
