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
const MODEL_KEY := "FUSION_GGUF_MODEL"
const PORT_KEY := "FUSION_AGENT_LOOP_PORT"

## PYTHONPATH is how the child is told where src/ lives. Godot's OS.execute_with_pipe cannot set a
## working directory, and the editor's CWD is the Godot project — which does not contain the Fusion
## package at all. Pointing PYTHONPATH at the Fusion checkout is the one mechanism that survives
## CreateProcess, and it is restored afterwards so the editor is not left mutated.
const PYTHONPATH_KEY := "PYTHONPATH"
const REPO_KEY := "FUSION_REPO"

const DEFAULT_ENDPOINT := "http://127.0.0.1:8001/agent-loop/perception"

## EditorSettings keys. These persist across sessions without touching the environment,
## which is the whole point: no PowerShell step, no $env: to paste, no clipboard involved.
const SETTING_PYTHON := "fusion_agent_loop/python"
const SETTING_MODEL := "fusion_agent_loop/model"
const SETTING_REPO := "fusion_agent_loop/repo"

## The Fusion module to launch. Resolved against the Fusion checkout via PYTHONPATH, so the
## editor's CWD no longer decides whether this import succeeds.
const FUSION_MODULE := "src.fusion.agent_loop_http"

## Fallback interpreter for this workstation. Only used when nothing is configured and
## FUSION_PYTHON is unset — a committed default for one developer is not portable, so the
## dock exposes it as an editable field instead of baking a path into behaviour.
const FALLBACK_PYTHON := "C:/Users/joshd/Local_models/fusion-gguf-env/Scripts/python.exe"

## Fallback Fusion checkout. Same portability caveat as FALLBACK_PYTHON: the plugin cannot
## derive this, because the Fusion repo is a sibling of this one rather than a path relative to
## the addon. Exposed as an editable field for every other developer.
const FALLBACK_REPO := "C:/Users/joshd/nlt-repos/neurolift-ai-fusion"

var _dock: Control
var _toggle: CheckButton
var _endpoint: LineEdit
var _status: Label
var _python_edit: LineEdit
var _model_edit: LineEdit
var _repo_edit: LineEdit
var _start_button: Button
var _stop_button: Button
var _log_view: TextEdit

var _server_pid := -1
var _stdout: FileAccess = null
var _stderr: FileAccess = null
var _log_partial := ""


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

	# --- Fusion server lifecycle -------------------------------------------------
	# Launching the endpoint from the editor removes the PowerShell step entirely: no env
	# vars to paste, no interpreter to remember, and the server is already listening by the
	# time the user presses Play. Output is captured to a file rather than read from a pipe,
	# because OS.execute() blocks the editor UI until the child exits.

	var sep := HSeparator.new()
	_dock.add_child(sep)

	var title2 := Label.new()
	title2.text = "Fusion Server"
	title2.add_theme_font_size_override("font_size", 14)
	_dock.add_child(title2)

	var blurb2 := Label.new()
	blurb2.text = "Runs src.fusion.agent_loop_http from the Fusion repo below. Start it before pressing Play."
	blurb2.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	blurb2.modulate = Color(0.7, 0.7, 0.7)
	_dock.add_child(blurb2)

	_python_edit = _add_path_row("Python (venv)", _resolve_python(), _on_python_changed)
	_model_edit = _add_path_row("GGUF model", _resolve_model(), _on_model_changed)
	_repo_edit = _add_path_row("Fusion repo (src/)", _resolve_repo(), _on_repo_changed)

	var row := HBoxContainer.new()
	_start_button = Button.new()
	_start_button.text = "Start"
	_start_button.pressed.connect(_on_start_pressed)
	row.add_child(_start_button)
	_stop_button = Button.new()
	_stop_button.text = "Stop"
	_stop_button.pressed.connect(_on_stop_pressed)
	row.add_child(_stop_button)
	_dock.add_child(row)

	_log_view = TextEdit.new()
	_log_view.custom_minimum_size = Vector2(0, 120)
	_log_view.editable = false
	_log_view.wrap_mode = TextEdit.LINE_WRAPPING_BOUNDARY
	_dock.add_child(_log_view)

	add_control_to_dock(EditorPlugin.DOCK_SLOT_LEFT_UL, _dock)

	# Adopt whatever is already set so toggling stays consistent across reloads.
	var existing := OS.get_environment(ENABLED_KEY)
	if existing == "1":
		_toggle.button_pressed = true
		var current := OS.get_environment(ENDPOINT_KEY)
		if not current.is_empty():
			_endpoint.text = current
	_refresh_status()


func _process(_delta: float) -> void:
	if _server_pid == -1:
		return

	# Drain both pipes non-blocking. execute_with_pipe is non-blocking here, so this cannot stall
	# the editor; an empty read just means no new output yet.
	_log_partial += _read_pipe(_stdout)
	_log_partial += _read_pipe(_stderr)
	if not _log_partial.is_empty() and _log_view:
		_log_view.text += _log_partial
		_log_partial = ""

	# The editor would otherwise keep showing "running" for a server that died on its own —
	# which is what a wrong interpreter or a port clash looks like from in here.
	if not OS.is_process_running(_server_pid):
		_server_pid = -1
		_close_pipes()
		if _log_view:
			_log_view.text += "\n[server exited before binding — check the repo path above and " \
				+ "whether port %s is already taken]" % _port()
		_refresh_status()


## Read whatever is available on a pipe, tolerating no-data and closed-pipe conditions.
func _read_pipe(pipe: FileAccess) -> String:
	if pipe == null:
		return ""
	var available := int(pipe.get_length())
	if available <= 0:
		return ""
	var buffer := pipe.get_buffer(available)
	if buffer.size() == 0:
		return ""
	return buffer.get_string_from_utf8()


func _close_pipes() -> void:
	for pipe in [_stdout, _stderr]:
		if pipe != null:
			pipe.close()
	_stdout = null
	_stderr = null


func _exit_tree() -> void:
	# Stop any server this plugin started. Leaving a child process holding port 8001 after the
	# editor closes is the exact failure that produced "address already in use" earlier.
	_stop_server()
	# Leave no opt-in behind for the next session.
	OS.set_environment(ENABLED_KEY, "")
	OS.set_environment(ENDPOINT_KEY, "")
	if _dock:
		remove_control_from_docks(_dock)
		_dock.queue_free()


## Add a label + LineEdit + browse row to the dock, returning the LineEdit for later reads.
func _add_path_row(label_text: String, value: String, on_changed: Callable) -> LineEdit:
	var row := VBoxContainer.new()
	var lbl := Label.new()
	lbl.text = label_text
	lbl.modulate = Color(0.7, 0.7, 0.7)
	row.add_child(lbl)

	var inner := HBoxContainer.new()
	var edit := LineEdit.new()
	edit.text = value
	edit.placeholder_text = value
	edit.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	edit.text_changed.connect(on_changed)
	inner.add_child(edit)

	var browse := Button.new()
	browse.text = "..."
	browse.custom_minimum_size = Vector2(28, 0)
	browse.pressed.connect(func() -> void: _browse(edit, label_text, on_changed))
	inner.add_child(browse)

	row.add_child(inner)
	_dock.add_child(row)
	return edit


func _browse(edit: LineEdit, title_text: String, on_changed: Callable) -> void:
	# OS.SystemDir has no EXECUTABLES member in Godot 4.4/4.7, so start from the
	# filesystem root and let the user navigate to the interpreter or model.
	var chosen := OS.get_system_dir(OS.SYSTEM_DIR_DOWNLOADS)
	var is_repo := title_text.begins_with("Fusion repo")
	var filters := PackedStringArray()
	if title_text.begins_with("GGUF"):
		filters.append("*.gguf ; GGUF Models")
	var dialog := EditorFileDialog.new()
	# The repo row names a directory, not a file, so it must not filter by extension.
	dialog.file_mode = EditorFileDialog.FILE_MODE_OPEN_DIR if is_repo else EditorFileDialog.FILE_MODE_OPEN_FILE
	dialog.access = FileDialog.ACCESS_FILESYSTEM
	dialog.title = "Select %s" % title_text
	if not filters.is_empty():
		dialog.filters = filters
	dialog.current_path = edit.text if not edit.text.is_empty() else chosen
	dialog.file_selected.connect(func(path: String) -> void:
		edit.text = path
		on_changed.call_func(path))
	dialog.canceled.connect(dialog.queue_free)
	dialog.confirmed.connect(dialog.queue_free)
	dialog.close_requested.connect(dialog.queue_free)
	add_child(dialog)
	dialog.popup_centered_ratio(0.7)


func _resolve_python() -> String:
	var from_env := OS.get_environment("FUSION_PYTHON")
	if not from_env.is_empty():
		return from_env
	var saved: Variant = EditorInterface.get_editor_settings().get_setting(SETTING_PYTHON)
	if saved != null:
		return String(saved)
	return FALLBACK_PYTHON


func _resolve_model() -> String:
	var from_env := OS.get_environment(MODEL_KEY)
	if not from_env.is_empty():
		return from_env
	var saved: Variant = EditorInterface.get_editor_settings().get_setting(SETTING_MODEL)
	if saved != null:
		return String(saved)
	return ""


func _on_python_changed(text: String) -> void:
	EditorInterface.get_editor_settings().set_setting(SETTING_PYTHON, text)


func _on_model_changed(text: String) -> void:
	EditorInterface.get_editor_settings().set_setting(SETTING_MODEL, text)


func _resolve_repo() -> String:
	var from_env := OS.get_environment(REPO_KEY)
	if not from_env.is_empty():
		return from_env
	var saved: Variant = EditorInterface.get_editor_settings().get_setting(SETTING_REPO)
	if saved != null:
		return String(saved)
	return FALLBACK_REPO


func _on_repo_changed(text: String) -> void:
	EditorInterface.get_editor_settings().set_setting(SETTING_REPO, text)


func _port() -> String:
	# Derive the port from the endpoint the game will actually call, so a custom port typed in
	# the endpoint field cannot silently disagree with the port Fusion binds.
	var url := _endpoint.text.strip_edges()
	var without_scheme := url.replace("https://", "").replace("http://", "")
	for part in without_scheme.split("/"):
		if part.contains(":"):
			var seg := part.get_slice(":", 1)
			if seg.is_valid_int():
				return seg
	return "8001"


func _on_start_pressed() -> void:
	if _server_pid != -1 and OS.is_process_running(_server_pid):
		_refresh_status()
		return

	# Guard every field the launch reads. A null here used to crash on .text with no usable
	# message, which is worse than a dock log line naming the missing path.
	var python: String = _python_edit.text.strip_edges() if _python_edit else ""
	if python.is_empty():
		_set_log("Set the venv interpreter path first.")
		return
	if not FileAccess.file_exists(python):
		_set_log("Interpreter not found:\n%s" % python)
		return

	var repo: String = _repo_edit.text.strip_edges() if _repo_edit else ""
	if repo.is_empty():
		_set_log("Set the Fusion repo path (the checkout that contains src/).")
		return
	var package_marker := repo.replace("\\", "/").trim_suffix("/") + "/src/fusion/agent_loop_http.py"
	if not FileAccess.file_exists(package_marker):
		_set_log("Fusion package not found:\n%s\n\nThat folder must be the checkout containing src/fusion/." % package_marker)
		return

	var model: String = _model_edit.text.strip_edges() if _model_edit else ""

	# Godot 4.4/4.7 OS.create_process takes only (path, arguments, open_console): it cannot set a
	# working directory, pass environment, or redirect output. execute_with_pipe does support
	# piped stdio, and the child's environment is the editor's, so the Fusion variables are set
	# on the editor process first and inherited by the child. They are restored afterwards so the
	# editor itself is not left mutated.
	var previous_model := OS.get_environment(MODEL_KEY)
	var previous_port := OS.get_environment(PORT_KEY)
	var previous_pythonpath := OS.get_environment(PYTHONPATH_KEY)
	var had_model := OS.has_environment(MODEL_KEY)

	# Fusion treats an unset FUSION_GGUF_MODEL as "use the deterministic fallback"; an empty
	# string is also falsy after strip_edges() in agent_loop_http.py, but clearing it is clearer
	# than passing "" and avoids implying a configured-but-blank model path.
	if model.is_empty():
		OS.unset_environment(MODEL_KEY)
	else:
		OS.set_environment(MODEL_KEY, model)
	OS.set_environment(PORT_KEY, _port())
	# Without this the child inherits the editor's CWD (the Godot project) and `-m
	# src.fusion.agent_loop_http` dies with ModuleNotFoundError before uvicorn ever binds.
	OS.set_environment(PYTHONPATH_KEY, repo + (previous_pythonpath.is_empty() ? "" : ";" + previous_pythonpath))

	var args := PackedStringArray(["-m", FUSION_MODULE])
	var proc := OS.execute_with_pipe(python, args, false)
	_restore_server_env(had_model, previous_model, previous_port, previous_pythonpath)

	if proc.is_empty():
		_set_log("Failed to launch:\n%s\n\nCheck the interpreter path." % python)
		_server_pid = -1
		_refresh_status()
		return

	_server_pid = int(proc.get("pid", -1))
	_stdout = proc.get("stdio", null)
	_stderr = proc.get("stderr", null)
	_log_partial = ""

	# A pid is returned even when the module fails to import, so a wrong repo path shows up as a
	# fast exit rather than a launch failure. Naming the checkout makes that case self-evident in
	# the log instead of requiring a guess from a bare process id.
	_set_log("Started Fusion endpoint (pid %d) from:\n%s\n\nWaiting for uvicorn to bind..." % [_server_pid, repo])
	_refresh_status()


func _restore_server_env(had_model: bool, model: String, port: String, pythonpath: String) -> void:
	if had_model:
		OS.set_environment(MODEL_KEY, model)
	else:
		OS.unset_environment(MODEL_KEY)
	if port.is_empty():
		OS.unset_environment(PORT_KEY)
	else:
		OS.set_environment(PORT_KEY, port)
	# CreateProcess has already copied the environment block into the child by this point, so
	# restoring here does not reach the server — it only stops the editor being left mutated.
	if pythonpath.is_empty():
		OS.unset_environment(PYTHONPATH_KEY)
	else:
		OS.set_environment(PYTHONPATH_KEY, pythonpath)


func _on_stop_pressed() -> void:
	_stop_server()
	_set_log("Stopped.")
	_refresh_status()


func _stop_server() -> void:
	if _server_pid != -1 and OS.is_process_running(_server_pid):
		OS.kill(_server_pid)
	_server_pid = -1
	_close_pipes()


func _set_log(text: String) -> void:
	if _log_view:
		_log_view.text = text


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
		_status.text = "Set for this editor session. Press Play."
		if _server_pid != -1 and OS.is_process_running(_server_pid):
			_status.text = "Loop enabled, Fusion running (pid %d)." % _server_pid
		else:
			_status.text = "Loop enabled. Start Fusion, or it will stay on the model-free fallback."
	else:
		_status.text = "Off. Default observer-only run."

	if _start_button and _stop_button:
		var running := _server_pid != -1 and OS.is_process_running(_server_pid)
		_start_button.disabled = running
		_stop_button.disabled = not running