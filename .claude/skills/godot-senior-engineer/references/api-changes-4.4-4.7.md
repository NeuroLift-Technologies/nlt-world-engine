# API changes 4.4 → 4.7 (from the engine's own validation records)

Generated from `misc/extension_api_validation/` in the Godot source at tag `4.7.2-stable`. Every intentional API break or signature change gets a record there, along with a note on whether compatibility methods were registered.

**How to read this:**
- "Compatibility methods registered" means old *binary* (GDExtension) calls keep working.
- GDScript and C# source code still sees the *new* signature. Usually that's harmless: an optional argument was added.
- Look for "removed", "renamed", "moved" and "type changed". Those break scripts.
- Grep this file for a class name when an upgrade breaks something, then read the GitHub PR (`GH-xxxxx` → `https://github.com/godotengine/godot/pull/xxxxx`).

## 4.4 → 4.5

- **GH-104087** [type changed] `OpenXRAPIExtension.register_composition_layer_provider, OpenXRAPIExtension.register_projection_views_extension, OpenXRAPIExtension.unregister_composition_layer_provider, OpenXRAPIExtension.unregister_projection_views_extension`: Switched from `OpenXRExtensionWrapperExtension` to parent `OpenXRExtensionWrapper`. Compatibility methods registered.
- **GH-104269** [removed] `RenderingServer.instance_reset_physics_interpolation, RenderingServer.instance_set_interpolated`: Functionality moved out of server.
- **GH-104872** [args changed] `CanvasItem.draw_char, CanvasItem.draw_char_outline, CanvasItem.draw_multiline_string, CanvasItem.draw_multiline_string_outline, CanvasItem.draw_string, CanvasItem.draw_string_outline (+22 more)`: Optional "oversmpling" argument added. Compatibility methods registered.
- **GH-104890** [removed] `JSONRPC.set_scope`: Replaced `set_scope` with `set_method`. Compatibility method registered for binary compatibility. Manual upgrade required by users to retain functionality.
- **GH-105570** [args changed] `RenderingDevice.texture_create_from_extension`: Argument added; p_mipmaps. Compatibility method registered.
- **GH-106121** [args changed] `EditorUndoRedoManager.create_action`: New argument added. Compatibility method registered.
- **GH-106220** [type changed] `GLTFAccessor.get_accessor_type, GLTFAccessor.get_buffer_view, GLTFAccessor.get_byte_offset, GLTFAccessor.get_component_type, GLTFAccessor.get_count, GLTFAccessor.get_max (+22 more)`: GLTFBufferView and GLTFAccessor now use int64 for offsets and lengths. Compatibility methods registered.
- **GH-106300**: Optional "color" argument added. Compatibility methods registered.
- **GH-106848** [removed] `Node.get_rpc_config`: Change Node `get_rpc_config` to `get_node_rpc_config`. Compatibility method registered.
- **GH-107347** [args changed] `RichTextLabel.add_image, RichTextLabel.update_image`: Optional argument added. Compatibility methods registered.
- **GH-108825** [type changed] `EditorExportPlatformExtension._get_option_icon`: Return type changed to allow returning both ImageTexture and DPITexture. Compatibility method registered.
- **GH-71542**: Optional argument added. Compatibility methods registered.
- **GH-76560** [type changed] `Node.set_name`: Change Node `set_name` to use StringName to improve performance. Compatibility method registered.
- **GH-76829** [args changed] `RichTextLabel.add_image, RichTextLabel.push_table, TreeItem.add_button`: Added optional arguments. Compatibility methods registered.
- **GH-98194** [args changed] `DisplayServer.file_dialog_show, DisplayServer.file_dialog_with_options_show`: Optional argument added. Compatibility methods registered.
- **GH-98750** `Color.ALICE_BLUE, Color.ANTIQUE_WHITE, Color.AQUAMARINE, Color.AZURE, Color.BEIGE, Color.BISQUE (+127 more)`: Precision of string-serialized Variant constants increased.

## 4.5 → 4.6

- **GH-107167** [type changed] `EditorExportPreset.get_script_export_mode`: Change return type from `int` to `EditorExportPreset.ScriptExportMode` enum. Compatibility method registered.
- **GH-107954** [removed] `StreamPeerTCP.disconnect_from_host, StreamPeerTCP.get_status, StreamPeerTCP.poll, TCPServer.is_connection_available, TCPServer.is_listening, TCPServer.stop`: These were moved to the parent classes, and are still available.
- **GH-109302** [args changed, type changed] `OpenXRExtensionWrapper._set_instance_create_info_and_get_next_pointer`:
- **GH-110120** [removed, type changed] `SpringBoneSimulator3D.BoneDirection, SpringBoneSimulator3D.RotationAxis, SpringBoneSimulator3D.get_end_bone_direction, SpringBoneSimulator3D.get_joint_rotation_axis, SpringBoneSimulator3D.get_rotation_axis, SpringBoneSimulator3D.set_end_bone_direction (+2 more)`: Same enum is defined in SkeletonModifier3D which is a base class of SpringBoneSimulator3D. Compatibility methods registered.
- **GH-110250**: Optional argument added. Compatibility methods registered.
- **GH-110433** [args changed] `Performance.add_custom_monitor`: Optional argument added. Compatibility method registered.
- **GH-110767** [type changed] `AnimationPlayer.current_animation_changed, AnimationPlayer.get_assigned_animation, AnimationPlayer.get_autoplay, AnimationPlayer.get_current_animation, AnimationPlayer.get_queue, AnimationPlayer.set_assigned_animation (+2 more)`: Return types and parameters changed to StringName to improve performance. Compatibility methods registered; No compatibility system for signal arguments.
- **GH-110867**: Optional argument removed. Compatibility method registered.
- **GH-111117**: Optional argument added. Compatibility method registered.
- **GH-111212** [removed] `EditorFileDialog.access, EditorFileDialog.add_filter, EditorFileDialog.add_option, EditorFileDialog.add_side_menu, EditorFileDialog.clear_filename_filter, EditorFileDialog.clear_filters (+39 more)`: The errors are false-positives. The removed methods are now part of the new parent class.
- **GH-111439** [args changed] `FileDialog.add_filter`: Optional argument added. Compatibility method registered.
- **GH-112290** `PackedByteArray.duplicate, PackedColorArray.duplicate, PackedFloat32Array.duplicate, PackedFloat64Array.duplicate, PackedInt32Array.duplicate, PackedInt64Array.duplicate (+4 more)`: Duplicate method made const. Compatibility methods registered.
- **GH-112379** [type changed] `DisplayServer.tts_speak`: `utterance_id` argument changed from `int32` to `int64`. No compatibility method needed.
- **GH-112539** `PackedByteArray.bsearch, PackedColorArray.bsearch, PackedFloat32Array.bsearch, PackedFloat64Array.bsearch, PackedInt32Array.bsearch, PackedInt64Array.bsearch (+4 more)`: bsearch method made const. Compatibility methods registered.
- **GH-113172** `GLTFState.get_accessors, GLTFState.get_additional_data, GLTFState.get_animation_player, GLTFState.get_animation_players_count, GLTFState.get_animations, GLTFState.get_base_path (+26 more)`: GLTFState getters made const. Compatibility methods registered.
- **GH-113459** [args changed] `DisplayServer.accessibility_create_sub_text_edit_elements`: Optional argument added. Compatibility method registered.
- **GH-114053** [type changed] `FileAccess.create_temp`: The argument was supposed to use this enum instead of an untyped int. A compatibility method has been registered.
- **GH-90411**: Optional argument added for index. Compatibility method registered.

## 4.6 → 4.7.x

- **GH-104736** [args changed] `PhysicsServer2D.body_set_shape_as_one_way_collision, PhysicsServer2DExtension._body_set_shape_as_one_way_collision`: Argument added. Compatibility methods registered.
- **GH-109004** [removed] `ImageTexture.get_format, PortableCompressedTexture2D.get_format`: The above are now members of the base class Texture2D.
- **GH-109142** [args changed] `CPUParticles2D.request_particles_process, CPUParticles3D.request_particles_process, GPUParticles2D.request_particles_process, GPUParticles3D.request_particles_process, RenderingServer.particles_request_process_time`: Optional argument added. Compatibility methods registered.
- **GH-109892** `Object.ConnectFlags`: The enum above is now corrected to be a bitfield.
- **GH-110369** [args changed] `AnimationNodeBlendSpace1D.add_blend_point, AnimationNodeBlendSpace2D.add_blend_point`: Added "name" parameter, to functionally replace index reference for points. Compatibility methods registered.
- **GH-112617** [removed, type changed] `RichTextLabel.ImageUpdateMask, RichTextLabel.add_image, RichTextLabel.update_image`: Arguments changed from bools to enums for a few methods. Compatibility methods registered.
- **GH-114355** [removed] `AudioEffectSpectrumAnalyzer.get_tap_back_pos, AudioEffectSpectrumAnalyzer.set_tap_back_pos, AudioEffectSpectrumAnalyzer.tap_back_pos`: Removed this property because it caused buggy behavior for no discernible benefit. Compatibility methods registered.
- **GH-115799** [args changed] `RenderingServer.viewport_set_size, Viewport.is_using_xr`: Optional argument added. Compatibility method registered. Changed to const. Compatibility method registered.
- **GH-115946** [args changed] `ZIPPacker.start_file`: Optional argument added. Compatibility method registered.
- **GH-116394** [type changed] `Animation.get_length, Animation.set_length`: Return type and parameter changed from real_t to double to match internals. No compatibility methods registered because GDExtension FFI already uses double.
- **GH-116839** [type changed] `Control.get_accessibility_live, Control.set_accessibility_live`: Enum moved to AccessibilityServer. Compatibility methods registered.
- **GH-117149** [args changed] `Font.find_variation`: Optional "palette_index" and "custom_colors" arguments added. Compatibility method registered.
- **GH-117399**: Added OpenXRInteractionProfileMetadata parameter to function.
- **GH-117800** [args changed] `Image.save_exr, Image.save_exr_to_buffer`: Added color_image and max_linear_value parameters to Image.save_exr functions for saving HDR screenshots. Use default values for existing behavior.
- **GH-117968** [args changed] `EditorVCSInterface._commit`: Added "amend" parameter. Compatibility method registered.
- **GH-118128** [args changed] `OpenXRSpatialAnchorCapability.create_new_anchor, OpenXRSpatialComponentData._get_structure_data`: Added optional "next" structure when creating a new anchor.  The "next" structure is passed to the XR runtime. Made "OpenXRSpatialComponentData::_get_structure_data" (which is the virtual method that GDExtensions can override) non-const, which is consistent with the core virtual "OpenXRSpatialComponentData::get_structure_data" method. Compatibility methods registered.
- **GH-117399** [type changed] `Object.is_class`: Changed String parameter to StringName. Compatibility method registered.
- **GH-118787** [args changed] `EditorExportPlatform.export_project`: Added "notify" parameter. Compatibility method registered.
- **GH-119367** [args changed] `TreeItem.select`: Optional argument added. Compatibility method registered.
- **GH-119563** [type changed]: Return value changed from "void" to "bool". Compatibility method registered.
