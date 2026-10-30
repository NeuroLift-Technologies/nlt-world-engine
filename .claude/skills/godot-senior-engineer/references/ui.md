# UI (Control nodes)

## Layout
- **Use containers, not hand-positioned anchors, for anything that has to adapt.** The layout containers are `VBoxContainer`/`HBoxContainer`, `GridContainer`, `MarginContainer`, `PanelContainer`, `CenterContainer`, `ScrollContainer`, `AspectRatioContainer`, `FlowContainer` and `SplitContainer`. Children of a container control their own sizing with `size_flags` (fill, expand, stretch ratio) and `custom_minimum_size`.
- Anchors and offsets are for the top-level placement of a root Control or a free-floating element. Use the anchor presets ("Full Rect", "Center", etc.).
- Multi-resolution setup: set the base resolution in `display/window/size/viewport_*`, `stretch/mode = canvas_items` for most UI-heavy games, and `stretch/aspect = expand`, then lay out with anchors and containers. Test at several aspect ratios.
- Common "my UI is the wrong size" causes:
  - A Control under a plain `Node` or `Node2D` doesn't get container layout.
  - A Control under a `CanvasLayer` has no parent rect, so it needs anchors set to Full Rect.

## Theming
- `Theme` resources hold colors, constants, fonts, font sizes, icons and StyleBoxes per control type. Set one at the root Control or in Project Settings → GUI → Theme so it cascades.
- Create **type variations** (for example `HeaderLabel` based on `Label`) instead of per-node overrides. Per-node theme overrides don't scale.
- Use `StyleBoxFlat` for rounded or bordered panels and `StyleBoxTexture` for 9-patch art.

## Input and focus
- Event order: `_input` → GUI (`_gui_input` on the Control under the mouse) → `_shortcut_input` → `_unhandled_key_input` → `_unhandled_input`. Gameplay input belongs in `_unhandled_input` so the UI can consume clicks first.
- `mouse_filter`: `STOP` (consume), `PASS` (receive and pass up to the parent), `IGNORE`. Invisible full-screen Controls left on `STOP` are the classic "clicks don't reach my game" bug.
- Gamepad and keyboard navigation: call `grab_focus()` on the first button when a menu opens, and set `focus_neighbor_*` where the automatic neighbor choice is wrong. Since 4.6 a mouse click no longer shows the focus outline.
- Accessibility: 4.5+ has screen reader support through AccessKit (experimental). Give controls meaningful names and tooltips.

## Text and widgets
- `Label` for plain text. `RichTextLabel` for BBCode or markup, effects and inline images; it's heavier, so don't use it for every label.
- Fonts: dynamic fonts with fallbacks for CJK. Use MSDF for text that scales a lot.
- Localization:
  - Use `tr()`/`tr_n()` for text in code.
  - Text set in the inspector auto-translates if `auto_translate_mode` is set.
  - Translations come from CSV or gettext `.po` files. Since 4.6 CSV supports context and plural columns.
  - Preview translations in the editor (4.5+).
- A virtual joystick is built in for mobile: the `VirtualJoystick` Control node (4.7+). Its `action_left/right/up/down` properties map it to existing Input Map actions, so `Input.get_vector` keeps working unchanged. It also has `joystick_mode` (fixed/dynamic/following), deadzone and clampzone ratios, `visibility_mode`, and tap/flick signals. Don't recommend a plugin for it anymore.

## Patterns
- Keep UI scenes separate from game logic. They listen to signals or an event bus, or bind to a data `Resource`, and never reach into the game tree by path.
- Use `Tween` for UI motion: `create_tween().set_trans(...).set_ease(...)`. Tweens are bound to the node that created them and die with it. Since 4.7 they can wait for a signal with `tween_await()`.
- Heavy lists: `ItemList`/`Tree` handle many items better than hundreds of instanced row scenes. Virtualize rows yourself if you need custom ones.
