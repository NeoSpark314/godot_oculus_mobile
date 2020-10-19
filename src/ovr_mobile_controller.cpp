/**
* Created by Fredia Huya-Kouadio. 
*/

#include "ovr_mobile_controller.h"

namespace ovrmobile {

namespace {
const int kXAxis = 0;
const int kYAxis = 1;
const int kAnalogIndexTriggerAxis = 2;
const int kAnalogGripTriggerAxis = 3;

const float kIndexTriggerPressedThreshold = 0.6f;
const float kGripTriggerPressedThreshold = 0.6f;

const int kInvalidGodotControllerId = 0;

const char *kUnsupportedController = "Unsupported Controller";
const char *kOculusTouchLeftController = "Oculus Touch Left Controller";
const char *kOculusTouchRightController = "Oculus Touch Right Controller";
const char *kOculusTrackedLeftHand = "Oculus Tracked Left Hand";
const char *kOculusTrackedRightHand = "Oculus Tracked Right Hand";

} // namespace

OvrMobileController::OvrMobileController() = default;

OvrMobileController::~OvrMobileController() = default;

void OvrMobileController::process(ovrMobile *ovr, ovrJava *java, double predicted_display_time) {
	update_controllers_connection_state(ovr, java);
	for (auto &controller : controllers) {
		update_controller_tracking_state(ovr, controller, predicted_display_time);
		update_controller_input_state(ovr, controller);
		update_controller_vibration(ovr, controller);
	}
}

void OvrMobileController::update_controller_vibration(ovrMobile *ovr, ControllerState& controller_state) {
	if (!controller_state.connected || controller_state.godot_controller_id == kInvalidGodotControllerId) {
		return;
	}

	if (controller_state.capability_header.Type == ovrControllerType_TrackedRemote) {
		if (!supports_haptic_vibration(controller_state.remote_capabilities)) {
			return;
		}

		// Get the vibration intensity.
		const float vibration = arvr_api->godot_arvr_get_controller_rumble(controller_state.godot_controller_id);
		vrapi_SetHapticVibrationSimple(ovr, controller_state.remote_capabilities.Header.DeviceID, vibration);
	} else {
		// unsupprted controller
	}
}

void OvrMobileController::update_controller_input_state(ovrMobile *ovr,ControllerState& controller_state) {
	if (!controller_state.connected || controller_state.godot_controller_id == kInvalidGodotControllerId) {
		return;
	}

	if (controller_state.capability_header.Type == ovrControllerType_TrackedRemote) {
		update_controller_input_state_tracked_remote(ovr, controller_state);
	} else if (controller_state.capability_header.Type == ovrControllerType_Hand) {
		update_controller_input_state_hand(ovr, controller_state);
	} else {
		// unsupported controller
	}
}

void OvrMobileController::update_controller_input_state_tracked_remote(ovrMobile *ovr, ControllerState& controller_state) {
	// Get the device input state.
	controller_state.input_header.ControllerType = ovrControllerType_TrackedRemote;
	if (vrapi_GetCurrentInputState(ovr, controller_state.remote_capabilities.Header.DeviceID, &controller_state.input_header) < 0) {
		return;
	}

	ovrInputStateTrackedRemote& input_state = controller_state.input_tracked_remote;

	// Update the controller axis.
	if (has_joystick(controller_state.remote_capabilities)) {
		// X axis
		arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kXAxis, input_state.Joystick.x, true /* can_be_negative */);
		// Y axis
		arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kYAxis, input_state.Joystick.y, true /* can_be_negative */);
	}

	if (has_trackpad(controller_state.remote_capabilities)) {
		// X axis
		float positionX = input_state.TrackpadStatus ? input_state.TrackpadPosition.x / controller_state.remote_capabilities.TrackpadMaxX : 0.0f;
		arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kXAxis, positionX, false /* can_be_negative */);
		// Y axis
		float positionY = input_state.TrackpadStatus ? input_state.TrackpadPosition.y /	controller_state.remote_capabilities.TrackpadMaxY : 0.0f;
		arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kYAxis, positionY, false /* can_be_negative */);
	}

	if (has_analog_index_trigger(controller_state.remote_capabilities)) {
		arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kAnalogIndexTriggerAxis, input_state.IndexTrigger, false /* can_be_negative */);
	}

	if (has_analog_grip_trigger(controller_state.remote_capabilities)) {
		arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kAnalogGripTriggerAxis, input_state.GripTrigger, false /* can_be_negative */);
	}

	// Update the controller button state. The button mappings for Godot will differ based on the Oculus mobile device.
	if (is_oculus_touch_controller(controller_state.remote_capabilities)) {
		// For now, keep the button assignments the same as for the Oculus Rift.
		// 9 -> thumb rest. The Oculus Quest touch controllers no longer have the thumb rest.
		arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 2, input_state.GripTrigger > kGripTriggerPressedThreshold);
		arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 10, check_bit(input_state.Touches, ovrTouch_ThumbUp));
		arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 11, check_bit(input_state.Touches, ovrTouch_IndexTrigger));
		arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 12, check_bit(input_state.Touches, ovrTouch_IndexPointing));
		arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 15, input_state.IndexTrigger > kIndexTriggerPressedThreshold);

		if (is_left_hand_controller(controller_state.remote_capabilities)) {
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 3, check_bit(input_state.Buttons, ovrButton_Enter)); // menu button
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 14, check_bit(input_state.Buttons, ovrButton_LThumb));
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 7, check_bit(input_state.Buttons, ovrButton_X));
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 5, check_bit(input_state.Touches, ovrTouch_X));
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 1, check_bit(input_state.Buttons, ovrButton_Y));
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 6, check_bit(input_state.Touches, ovrTouch_Y));
		}

		if (is_right_hand_controller(controller_state.remote_capabilities)) {
			// 3 -> home button. The home button is not available for applications.
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 7, check_bit(input_state.Buttons, ovrButton_A));
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 5, check_bit(input_state.Touches, ovrTouch_A));
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 1, check_bit(input_state.Buttons, ovrButton_B));
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 6, check_bit(input_state.Touches, ovrTouch_B));
			arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 14, check_bit(input_state.Buttons, ovrButton_RThumb));
		}
	}
}

void OvrMobileController::update_controller_input_state_hand(ovrMobile *ovr, ControllerState& controller_state) {
	controller_state.input_header.ControllerType = ovrControllerType_Hand;

	if (vrapi_GetCurrentInputState(ovr, controller_state.remote_capabilities.Header.DeviceID, &controller_state.input_header) < 0) {
		return;
	}

	ovrInputStateHand& input_state = controller_state.input_hand;

	// we map pinch index and middle to button presses with same id as X/Y and A/B
	arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 7, check_bit(input_state.InputStateStatus, ovrInputStateHandStatus_IndexPinching));
	arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 1, check_bit(input_state.InputStateStatus, ovrInputStateHandStatus_MiddlePinching));

	// pinch ring and pinky are mapped to grip (2) and index (15) triggers for now
	arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 2, check_bit(input_state.InputStateStatus, ovrInputStateHandStatus_RingPinching));
	arvr_api->godot_arvr_set_controller_button(controller_state.godot_controller_id, 15, check_bit(input_state.InputStateStatus, ovrInputStateHandStatus_PinkyPinching));

	// to allow accessing the pinch state as provided by the API we map them here to the joystick axis of the controller
	// this will give the ability to access the basic hand tracking gestures without the need to query specific APIs
	arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kXAxis, input_state.PinchStrength[ovrHandPinchStrength_Index], false);
	arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kYAxis, input_state.PinchStrength[ovrHandPinchStrength_Middle], false);
	arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kAnalogIndexTriggerAxis, input_state.PinchStrength[ovrHandPinchStrength_Ring], false);
	arvr_api->godot_arvr_set_controller_axis(controller_state.godot_controller_id, kAnalogGripTriggerAxis, input_state.PinchStrength[ovrHandPinchStrength_Pinky], false);
}


void OvrMobileController::update_controller_tracking_state(ovrMobile *ovr, ControllerState& controller_state, double predicted_display_time) {
	if (!controller_state.connected || controller_state.godot_controller_id == kInvalidGodotControllerId) {
		return;
	}

	if (controller_state.capability_header.Type == ovrControllerType_TrackedRemote) {
		update_controller_tracking_state_tracked_remote(ovr, controller_state, predicted_display_time);
	} else if (controller_state.capability_header.Type == ovrControllerType_Hand) {
		update_controller_tracking_state_hand(ovr, controller_state, predicted_display_time);
	} else {
		// unsupported controller type
	}
}

void OvrMobileController::update_controller_tracking_state_tracked_remote(ovrMobile *ovr, ControllerState& controller_state, double predicted_display_time) {
	// Tracked remote is connected. Get the device tracking state.
	if (vrapi_GetInputTrackingState(ovr, controller_state.remote_capabilities.Header.DeviceID, predicted_display_time, &controller_state.tracking_state) < 0) {
		return;
	}

	// Update the controller transform.
	godot_transform transform;
	godot_transform_from_ovr_pose(&transform, controller_state.tracking_state.HeadPose.Pose, arvr_api->godot_arvr_get_worldscale());
	arvr_api->godot_arvr_set_controller_transform(controller_state.godot_controller_id, &transform,
			has_orientation_tracking(controller_state.remote_capabilities),
			has_position_tracking(controller_state.remote_capabilities));
}

void OvrMobileController::update_controller_tracking_state_hand(ovrMobile *ovr, ControllerState& controller_state, double predicted_display_time) {
	if (vrapi_GetInputTrackingState(ovr, controller_state.capability_header.DeviceID, predicted_display_time, &controller_state.tracking_state) < 0) {
		return;
	}

	controller_state.hand_pose.Header.Version = ovrHandVersion_1; //!!TODO: set in initialization
	vrapi_GetHandPose(ovr, controller_state.capability_header.DeviceID, predicted_display_time, &controller_state.hand_pose.Header);

	// Update the controller transform.
	godot_transform transform;
	//godot_transform_from_ovr_pose(&transform, controller_state.tracking_state.HeadPose.Pose, arvr_api->godot_arvr_get_worldscale());
	godot_transform_from_ovr_pose(&transform, controller_state.hand_pose.RootPose, arvr_api->godot_arvr_get_worldscale());
	arvr_api->godot_arvr_set_controller_transform(controller_state.godot_controller_id, &transform, true, true);
}


void OvrMobileController::update_controllers_connection_state(ovrMobile *ovr, ovrJava *java) {
	// Reset the controllers connected state.
	for (auto &controller : controllers) {
		controller.connected = false;
	}

	// Check controller(s) connection state.
	ovrInputCapabilityHeader capability_header;
	for (uint32_t device_index = 0; vrapi_EnumerateInputDevices(ovr, device_index, &capability_header) >= 0; device_index++) {
		// Tracked remote (Oculus Quest controllers).
		if (capability_header.Type == ovrControllerType_TrackedRemote) {
			ovrInputTrackedRemoteCapabilities tracked_remote_capabilities;
			tracked_remote_capabilities.Header = capability_header;
			if (vrapi_GetInputDeviceCapabilities(ovr, &tracked_remote_capabilities.Header) < 0) {
				continue;
			}

			ControllerHand handedness;
			if (is_oculus_touch_controller(tracked_remote_capabilities)) {
				handedness = get_controller_handedness(tracked_remote_capabilities);
			} else {
				// We're handling a Gear VR or Oculus Go controller. Let's query the user dominant hand to find out where to
				// assign the controller.
				auto dominant_hand = static_cast<ovrHandedness>(vrapi_GetSystemPropertyInt(java, VRAPI_SYS_PROP_DOMINANT_HAND));
				handedness = get_controller_handedness(dominant_hand);
			}

			// this check forces a reconnect below because the type of the controller changed
			if (controllers[handedness].capability_header.Type != ovrControllerType_TrackedRemote && controllers[handedness].godot_controller_id != kInvalidGodotControllerId) {
				arvr_api->godot_arvr_remove_controller(controllers[handedness].godot_controller_id);
				ALOGV("Removed Controller Tracked Remote (Godot id %d)", controllers[handedness].godot_controller_id);
				controllers[handedness].godot_controller_id = kInvalidGodotControllerId;
			}

			controllers[handedness].connected = true;
			controllers[handedness].remote_capabilities = tracked_remote_capabilities;
		} else if (capability_header.Type == ovrControllerType_Hand) {
			ovrInputHandCapabilities tracked_hand_capabilities;
			tracked_hand_capabilities.Header = capability_header;
			if (vrapi_GetInputDeviceCapabilities(ovr, &tracked_hand_capabilities.Header) < 0) {
				continue;
			}

			ControllerHand handedness = get_controller_handedness(tracked_hand_capabilities);
			
			// this check forces a reconnect below because the type of the controller changed
			if (controllers[handedness].capability_header.Type != ovrControllerType_Hand && controllers[handedness].godot_controller_id != kInvalidGodotControllerId) {
				arvr_api->godot_arvr_remove_controller(controllers[handedness].godot_controller_id);
				ALOGV("Removed Tracked Hand (Godot id %d)", controllers[handedness].godot_controller_id);
				controllers[handedness].godot_controller_id = kInvalidGodotControllerId;
			}
			controllers[handedness].connected = true;
			controllers[handedness].hand_capabilities = tracked_hand_capabilities;
		} else {
			// unsupported at the moment
		}
	}

	// Notify Godot of the updated connection states.
	for (int hand = 0; hand < MAX_HANDS; hand++) {
		ControllerState *controller = &controllers[hand];

		if (controller->connected && controller->godot_controller_id == kInvalidGodotControllerId) {
			// Register the controller with Godot.
			if (controller->capability_header.Type == ovrControllerType_TrackedRemote) {
				controller->godot_controller_id = arvr_api->godot_arvr_add_controller(
						const_cast<char *>(get_controller_model_name(*controller)), get_godot_hand(static_cast<ControllerHand>(hand)),
						has_orientation_tracking(controller->remote_capabilities),
						has_position_tracking(controller->remote_capabilities));
			} else if (controller->capability_header.Type == ovrControllerType_Hand) {
				controller->godot_controller_id = arvr_api->godot_arvr_add_controller(
						const_cast<char *>(get_controller_model_name(*controller)), get_godot_hand(static_cast<ControllerHand>(hand)),
						true, true);
			}
			ALOGV("Updated Controller '%s' (Godot id %d; Oculus id %d)", get_controller_model_name(*controller), controller->godot_controller_id, hand);
		} else if (!controller->connected && controller->godot_controller_id != kInvalidGodotControllerId) {
			// Unregister the controller from Godot.
			ALOGV("Unregistered Controller '%s' (Godot id %d; Oculus id %d)", get_controller_model_name(*controller), controller->godot_controller_id, hand);
			arvr_api->godot_arvr_remove_controller(controller->godot_controller_id);
			controller->godot_controller_id = kInvalidGodotControllerId;
		}
	}
}

const char *OvrMobileController::get_controller_model_name(const ControllerState& controller_state) {
	if (controller_state.capability_header.Type == ovrControllerType_TrackedRemote) {
		if (is_oculus_touch_controller(controller_state.remote_capabilities)) {
			if (is_left_hand_controller(controller_state.remote_capabilities)) {
				return kOculusTouchLeftController;
			}

			if (is_right_hand_controller(controller_state.remote_capabilities)) {
				return kOculusTouchRightController;
			}
		}
	} else if (controller_state.capability_header.Type == ovrControllerType_Hand) {
		if (is_left_hand_controller(controller_state.hand_capabilities)) {
			return kOculusTrackedLeftHand;
		}
		if (is_right_hand_controller(controller_state.hand_capabilities)) {
			return kOculusTrackedRightHand;
		}
	}

	return kUnsupportedController;
}

} // namespace ovrmobile
