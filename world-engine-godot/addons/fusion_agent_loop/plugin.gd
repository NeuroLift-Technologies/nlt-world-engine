@tool
extends EditorPlugin
## Session-only opt-in for the Fusion local agent loop.
##
## `Main.cs` reads `NLT_AGENT_LOOP_ENABLED` and `NLT_AGENT_LOOP_ENDPOINT` once in
## `_Ready()`. Those variables have to exist in the *editor's* environment before
## the game process is spawned, because the play button inherits the editor's
## environment and not the shell's. Setting them here means the loop can be
## exercised by pressing Play, with no PowerShell step.
##
## Why this is a plugin rather than the `EnableFusionAgentLoop` export already on
## `Main`: the export is saved into `Main.tscn`, which is source-controlled, so
## ticking it in the Inspector makes the opt-in the committed default for every
## other developer. This toggle only calls `OS.set_environment()`, which affects
## the current editor session and its child processes. It never touches the scene.
##
## Default runs stay observer-only: with the toggle off, nothing is set and
## `Main` behaves exactly as it does in a plain checkout.

const ENABLED_KEY := "NLT_AGENT_LOOP_ENABLED"
const ENDPOINT_KEY := "NLT_AGENT_LOOP_ENDPOINT"
const DEFAULT_ENDPOINT := "http://127.0.0.1:8001/agent-loop/perception"

var _dock: Control
var _toggle: CheckButton
var _endpoint: LineEdit
var _status: Label


func _enter_tree() -> void:
	_dock = VBoxContainer.new()
	_dock.name = "FusionLoop"
	_dock.custom_minimum_size = Vector2(260, 0)

	var title := Label.new()
	title.text = "Fusion Agent Loop"
	title.add_theme_font_size_override("font_size", 14)
	_dock.add_child(title)

	var blurb := Label.new()
	blurb.text = "Session-only. Sets the environment for the game process when you press Play. Does not modify Main.tscn."
	blurb.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	blurb.modulate = Color(0.7, 0.7, 0.7)
	_dock.add_child(blurb)

	_toggle = CheckButton.new()
	_toggle.text = "Enable local agent loop"
	_toggle.toggled.connect(_on_toggled)
	_dock.add_child(_toggle)

	_endpoint = LineEdit.new()
	_endpoint.placeholder_text = DEFAULT_ENDPOINT
	_endpoint.text = DEFAULT_ENDPOINT
	_endpoint.custom_minimum_size = Vector2(0, 0)
	_endpoint.text_changed.connect(_on_endpoint_changed)
	_dock.add_child(_endpoint)

	_status = Label.new()
	_status.modulate = Color(0.7, 0.7, 0.7)
	_dock.add_child(_status)

	add_control_to_dock(EditorPlugin.DOCK_SLOT_LEFT_UL, _dock)

	# Adopt whatever is already set so toggling stays consistent across reloads.
	var existing := OS.get_environment(ENABLED_KEY)
	if existing == "1":
		_toggle.button_pressed = true
		var current := OS.get_environment(ENDPOINT_KEY)
		if not current.is_empty():
			_endpoint.text = current
	_refresh_status()


func _exit_tree() -> void:
	# Leave no opt-in behind for the next session.
	OS.set_environment(ENABLED_KEY, "")
	OS.set_environment(ENDPOINT_KEY, "")
	if _dock:
		remove_control_from_docks(_dock)
		_dock.queue_free()


func _on_toggled(pressed: bool) -> void:
	if pressed:
		OS.set_environment(ENABLED_KEY, "1")
		var endpoint := _endpoint.text.strip_edges()
		if endpoint.is_empty():
			endpoint = DEFAULT_ENDPOINT
			_endpoint.text = endpoint
		OS.set_environment(ENDPOINT_KEY, endpoint)
	else:
		OS.set_environment(ENABLED_KEY, "")
		OS.set_environment(ENDPOINT_KEY, "")
	_refresh_status()


func _on_endpoint_changed(text: String) -> void:
	if _toggle.button_pressed:
		OS.set_environment(ENDPOINT_KEY, text.strip_edges())
		_refresh_status()


func _refresh_status() -> void:
	if _toggle.button_pressed:
		_status.text = "Set for this editor session. Press Play.\nFusion must already be serving on this endpoint."
	else:
		_status.text = "Off. Default observer-only run."