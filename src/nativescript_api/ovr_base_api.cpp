#include "api_common.h"
#include "ovr_base_api.h"
#include <vector>

static const char *kClassName = "OvrBaseAPI";


GDCALLINGCONV void *ovr_base_api_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovr_base_api_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);

// implements VrApi.h: ovrResult vrapi_GetBoundaryGeometry( ovrMobile * ovr, const uint32_t pointsCountInput, uint32_t * pointsCountOutput, ovrVector3f * points );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_GetBoundaryOrientedBoundingBox( ovrMobile * ovr, ovrPosef * pose, ovrVector3f * scale );
GDCALLINGCONV godot_variant get_boundary_oriented_bounding_box(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h: ovrResult vrapi_TestPointIsInBoundary( ovrMobile * ovr, const ovrVector3f point, bool * pointInsideBoundary, ovrBoundaryTriggerResult * result );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_GetBoundaryTriggerState( ovrMobile * ovr, const ovrTrackedDeviceTypeId deviceId, ovrBoundaryTriggerResult * result );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_RequestBoundaryVisible( ovrMobile * ovr, const bool visible );
GDCALLINGCONV godot_variant request_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

//ovrResult vrapi_GetBoundaryVisible( ovrMobile * ovr, bool * visible );
GDCALLINGCONV godot_variant get_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);



// implements VrApi.h: ovrResult vrapi_SetDisplayRefreshRate(ovrMobile * ovr, const float refreshRate);
GDCALLINGCONV godot_variant set_display_refresh_rate(godot_object *instance, void *method_data, void *user_data, int num_args, godot_variant **args);

// Utility method to access the display refresh rates supported by the device.
GDCALLINGCONV godot_variant get_supported_display_refresh_rates(godot_object *instance, void *method_data, void *user_data, int num_args, godot_variant **args);



// get_hand_pose(controller_id : int, pose : Array[24]);
// fills the tracked pose in the given array as quaternions for the given controller id; returns a confidence value in [0.0, 1.0] based
// on the hand tracking confidence returned by VrApi. If the controller is not connected or VR not initialized it returns nil.
GDCALLINGCONV godot_variant get_hand_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// get_hand_scale(controller_id : int);
// returns 0.0 if the system is unable to get the hand scale; else returns the scale given by VrApi
GDCALLINGCONV godot_variant get_hand_scale(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// check if the current pointer pose is valid; only then get_pointer_pose will return a useful value
GDCALLINGCONV godot_variant is_pointer_pose_valid(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// return the VrApi hand pointer pose
GDCALLINGCONV godot_variant get_pointer_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);



// implements VrApi.h: ovrResult vrapi_SetClockLevels( ovrMobile * ovr, const int32_t cpuLevel, const int32_t gpuLevel );
GDCALLINGCONV godot_variant set_clock_levels(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h ovrResult vrapi_SetExtraLatencyMode( ovrMobile * ovr, const ovrExtraLatencyMode mode );
// Valid int values for the latency mode are defined by ovrExtraLatencyMode enum in VrApi_Types.h
GDCALLINGCONV godot_variant set_extra_latency_mode(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// Set the fixed foveated rendering level if it's available.
// Returns true if it's available and the given level is valid, false otherwise.
// For additional information, check the following docs:
// - Oculus Quest: https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
// - Oculus Go: https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-ffr/
GDCALLINGCONV godot_variant set_foveation_level(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// Enables or disables dynamic foveation
// Returns true if it's available 
GDCALLINGCONV godot_variant set_enable_dynamic_foveation(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


// Sets the swap interval to control the application frame timing.
// See https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-vrapi#frame-timing for additional background.
GDCALLINGCONV godot_variant set_swap_interval(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);


// implements VrApi.h: ovrTrackingSpace vrapi_GetTrackingSpace( ovrMobile * ovr );
GDCALLINGCONV godot_variant get_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h: ovrResult vrapi_SetTrackingSpace( ovrMobile * ovr, ovrTrackingSpace whichSpace );
GDCALLINGCONV godot_variant set_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

// implements VrApi.h: ovrPosef vrapi_LocateTrackingSpace( ovrMobile * ovr, ovrTrackingSpace target );
GDCALLINGCONV godot_variant locate_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);



void register_gdnative_base_api(void *p_handle) {
    { // register the constructor and destructor of the OvrBaseAPI class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_base_api_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_base_api_destructor;

		nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // now we register all the functions that we want to expose via OvrBaseAPI class in GDScript; we use as method names the same names as in VrApi.h but without prefix
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &request_boundary_visible;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "request_boundary_visible", attributes, method);

		method.method = &get_boundary_visible;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_boundary_visible", attributes, method);

		method.method = &get_boundary_oriented_bounding_box;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_boundary_oriented_bounding_box", attributes, method);

		method.method = &get_supported_display_refresh_rates;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_supported_display_refresh_rates", attributes, method);

		method.method = &set_display_refresh_rate;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_display_refresh_rate", attributes, method);


		method.method = &get_hand_pose;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_hand_pose", attributes, method);

		method.method = &get_hand_scale;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_hand_scale", attributes, method);
		
		method.method = &is_pointer_pose_valid;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "is_pointer_pose_valid", attributes, method);
		method.method = &get_pointer_pose;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_pointer_pose", attributes, method);

		// Performance
		method.method = &set_clock_levels;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_clock_levels", attributes, method);

		method.method = &set_extra_latency_mode;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_extra_latency_mode", attributes, method);

		method.method = &set_foveation_level;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_foveation_level", attributes, method);

		method.method = &set_enable_dynamic_foveation;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_enable_dynamic_foveation", attributes, method);

		method.method = &set_swap_interval;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_swap_interval", attributes, method);


		method.method = &get_tracking_space;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_tracking_space", attributes, method);

		method.method = &set_tracking_space;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_tracking_space", attributes, method);

		method.method = &locate_tracking_space;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "locate_tracking_space", attributes, method);
		

	}
}


GDCALLINGCONV void *ovr_base_api_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}


GDCALLINGCONV void ovr_base_api_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
	}
}


GDCALLINGCONV godot_variant request_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
	    bool visible = api->godot_variant_as_bool(p_args[0]);
		ovrResult result = vrapi_RequestBoundaryVisible(ovr, visible);
		if (result == ovrSuccess) api->godot_variant_new_bool(&ret, true); // set the return value to true if vrapi was called successfully
	)
}

GDCALLINGCONV godot_variant get_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
        bool visible = false;
		vrapi_GetBoundaryVisible(ovr, &visible);
		api->godot_variant_new_bool(&ret, visible);
	)	
}


GDCALLINGCONV godot_variant get_boundary_oriented_bounding_box(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrPosef pose;
		ovrVector3f scale;
		if (vrapi_GetBoundaryOrientedBoundingBox(ovr, &pose, &scale) == ovrSuccess) {
			godot_real world_scale = arvr_api->godot_arvr_get_worldscale();
			godot_transform gd_transform;
			godot_vector3 gd_scale;
			ovrmobile::godot_transform_from_ovr_pose(&gd_transform, pose, world_scale);
			api->godot_vector3_new(&gd_scale, scale.x * world_scale, scale.y * world_scale, scale.z * world_scale);

			godot_variant vTransform;
			godot_variant vScale;
			api->godot_variant_new_transform(&vTransform, &gd_transform);
			api->godot_variant_new_vector3(&vScale, &gd_scale);
			
			godot_array gd_returnArray; // for now we return the transform and scale in a godot array; maybe and Area with a BoxShape would be nice?
			api->godot_array_new(&gd_returnArray);

			api->godot_array_push_back(&gd_returnArray, &vTransform);
			api->godot_array_push_back(&gd_returnArray, &vScale);
			api->godot_variant_destroy(&vTransform);
			api->godot_variant_destroy(&vScale);

			api->godot_variant_new_array(&ret, &gd_returnArray); // set the return value to be the constructed array
			api->godot_array_destroy(&gd_returnArray);
		}
	)
}


GDCALLINGCONV void ovr_display_refresh_rate_destructor(godot_object *instance, void *method_data, void *user_data) {
	if (user_data) {
		reset_ovr_config_data_struct(static_cast<ovr_config_data_struct *>(user_data));
	}
}

GDCALLINGCONV godot_variant get_supported_display_refresh_rates(godot_object *instance, void *method_data, void *p_user_data, int num_args, godot_variant **args) {
	CHECK_OVR(
			const int refresh_rates_count = vrapi_GetSystemPropertyInt(ovr_java, VRAPI_SYS_PROP_NUM_SUPPORTED_DISPLAY_REFRESH_RATES);
			std::vector<float> supported_refresh_rates(refresh_rates_count, 0.0F);
			vrapi_GetSystemPropertyFloatArray(ovr_java, VRAPI_SYS_PROP_SUPPORTED_DISPLAY_REFRESH_RATES, supported_refresh_rates.data(), refresh_rates_count);

			godot_array gd_return_array;
			api->godot_array_new(&gd_return_array);

			for (int i = 0; i < refresh_rates_count; i++) {
				godot_variant refresh_rate;
				api->godot_variant_new_real(&refresh_rate, supported_refresh_rates[i]);
				api->godot_array_push_back(&gd_return_array, &refresh_rate);
				api->godot_variant_destroy(&refresh_rate);
			}

			api->godot_variant_new_array(&ret, &gd_return_array);
			api->godot_array_destroy(&gd_return_array);

	)
}

GDCALLINGCONV godot_variant set_display_refresh_rate(godot_object *instance, void *method_data, void *p_user_data, int num_args, godot_variant **args) {
	CHECK_OVR(
			const double refresh_rate = api->godot_variant_as_real(args[0]);
			ovrResult result = vrapi_SetDisplayRefreshRate(ovr, refresh_rate);
			if (result == ovrSuccess) {
				api->godot_variant_new_bool(&ret, true);
			}

	)
}



GDCALLINGCONV godot_variant get_hand_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
        api->godot_variant_new_real(&ret, 0.0); // in case sth. fails below we return 0.0 to always have a float return value

		if (p_num_args != 2) {
			ALOGW("ovrHandTracking.gdns: get_hand_pose(controller_id, pose_quaternions[]) requires 2 parameters; got %d", p_num_args);
		} else {
			int controller_id = api->godot_variant_as_int(p_args[0]) - 1;
			const ovrmobile::OvrMobileController* pController = ovr_mobile_session->get_ovr_mobile_controller();
			if (pController != nullptr) {
				const ovrmobile::OvrMobileController::ControllerState* pState = pController->get_controller_state(controller_id);
				if (pState != nullptr && pState->connected) {
					godot_array rotations = api->godot_variant_as_array(p_args[1]);

					if (api->godot_array_size(&rotations) != ovrHandBone_Max) {
						ALOGE("get_hand_pose(...) expect p_args[1] to be an array of size %d; got %d.", ovrHandBone_Max, api->godot_array_size(&rotations));
					} else {

						for (int i = 0; i < ovrHandBone_Max; i++) {
							//godot_quat quat = godot_variant_as_quat(godot_array_get(rotations, i));
							godot_variant v_quat;
							godot_quat g_quat;
							//ovrQuatf ovr_quat = pose.BoneRotations[i];
							ovrQuatf ovr_quat = pState->hand_pose.BoneRotations[i];
							api->godot_quat_new(&g_quat, ovr_quat.x, ovr_quat.y, ovr_quat.z, ovr_quat.w);
							api->godot_variant_new_quat(&v_quat, &g_quat);
							api->godot_array_set(&rotations, i, &v_quat);
						}

						// we return a confidence value how well the hand is tracked. If the ovr sdk return untracked it is 0.0
						// low confidence is 0.5 and full confidence is 1.0
						float return_value = 0.0f;

						if (pState->hand_pose.Status == ovrHandTrackingStatus_Tracked) {
							if (pState->hand_pose.HandConfidence == ovrConfidence_HIGH) {
								return_value = 1.0f;
							} else { // in sdk 1.29 there are only HIGH and LOW as confidence values if the hand is tracked
								return_value = 0.5f;
							}
						}

						api->godot_variant_new_real(&ret, return_value);
					}
				}
			}
		} // num_args check
	)
}


GDCALLINGCONV godot_variant get_hand_scale(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
        api->godot_variant_new_real(&ret, 0.0); // in case sth. fails below we return 0.0 to always have a float return value
		if (p_num_args != 1) {
			ALOGW("ovrHandTracking.gdns: get_hand_scale(controller_id) requires 1 parameters; got %d", p_num_args);
		} else {
			int controller_id = api->godot_variant_as_int(p_args[0]) - 1;
			const ovrmobile::OvrMobileController* pController = ovr_mobile_session->get_ovr_mobile_controller();
			if (pController != nullptr) {
				const ovrmobile::OvrMobileController::ControllerState* pState = pController->get_controller_state(controller_id);
				if (pState != nullptr && pState->connected) {
					api->godot_variant_new_real(&ret, pState->hand_pose.HandScale);
				}
			}
		}
    )
}

GDCALLINGCONV godot_variant is_pointer_pose_valid(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
        api->godot_variant_new_real(&ret, false); // in case sth. fails below we return false
		if (p_num_args != 1) {
			ALOGW("ovrHandTracking.gdns: is_pointer_pose_valid(controller_id) requires 1 parameters; got %d", p_num_args);
		} else {
			int controller_id = api->godot_variant_as_int(p_args[0]) - 1;
			const ovrmobile::OvrMobileController* pController = ovr_mobile_session->get_ovr_mobile_controller();
			if (pController != nullptr) {
				const ovrmobile::OvrMobileController::ControllerState* pState = pController->get_controller_state(controller_id);
				if (pState != nullptr && pState->connected) {
					if (ovrmobile::check_bit(pState->input_hand.InputStateStatus, ovrInputStateHandStatus_PointerValid)) {
						api->godot_variant_new_bool(&ret, true);
					} else {
						api->godot_variant_new_bool(&ret, false);
					}
				}
			}
		}
    )
}


GDCALLINGCONV godot_variant get_pointer_pose(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		if (p_num_args != 1) {
			ALOGW("ovrHandTracking.gdns: get_pointer_pose(controller_id) requires 1 parameters; got %d", p_num_args);
		} else {
			int controller_id = api->godot_variant_as_int(p_args[0]) - 1;
			const ovrmobile::OvrMobileController* pController = ovr_mobile_session->get_ovr_mobile_controller();
			if (pController != nullptr) {
				const ovrmobile::OvrMobileController::ControllerState* pState = pController->get_controller_state(controller_id);
				if (pState != nullptr && pState->connected) {
					godot_real world_scale = arvr_api->godot_arvr_get_worldscale();
					godot_transform gd_transform;

					ovrmobile::godot_transform_from_ovr_pose(&gd_transform, pState->input_hand.PointerPose, world_scale);
					api->godot_variant_new_transform(&ret, &gd_transform);
				}
			}
		}
    )
}



GDCALLINGCONV godot_variant set_clock_levels(godot_object*, void*, void *p_user_data, int, godot_variant **p_args) {
	CHECK_OVR(
	        int cpu_level = api->godot_variant_as_int(p_args[0]);
	        int gpu_level = api->godot_variant_as_int(p_args[1]);
	        ovrResult result = vrapi_SetClockLevels(ovr, cpu_level, gpu_level);
	        if (result == ovrSuccess) {
	            api->godot_variant_new_bool(&ret, true);
	        }

	)
}

GDCALLINGCONV godot_variant set_extra_latency_mode(godot_object*, void*, void *p_user_data, int, godot_variant **p_args) {
	CHECK_OVR(
	       int latency_mode = api->godot_variant_as_int(p_args[0]);
	       ovrResult result = vrapi_SetExtraLatencyMode(ovr,
	               static_cast<ovrExtraLatencyMode>(latency_mode));
	       if (result == ovrSuccess) {
	           api->godot_variant_new_bool(&ret, true);
	       }

	)
}

GDCALLINGCONV godot_variant set_foveation_level(godot_object *, void *, void *p_user_data, int, godot_variant **p_args) {
	CHECK_OVR(
			// Check if foveation is available.
			int foveation_available = vrapi_GetSystemPropertyInt(ovr_java, VRAPI_SYS_PROP_FOVEATION_AVAILABLE);
			if (foveation_available == VRAPI_TRUE) {
				// Retrieve the foveation level
				int foveation_level = api->godot_variant_as_int(p_args[0]);

				// Validate the foveation level.
				bool foveation_valid = false;
				if (ovrmobile::is_oculus_quest_device(ovr_java)) {
				    // Foveation level for the Oculus Quest ranges from 0 to 4
				    // See // - Oculus Quest: https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
				    foveation_valid = foveation_level >= 0 && foveation_level <= 4;
				}

				if (foveation_valid) {
				    vrapi_SetPropertyInt(ovr_java, VRAPI_FOVEATION_LEVEL, foveation_level);
				}
                api->godot_variant_new_bool(&ret, foveation_valid);
			}

	)
}

GDCALLINGCONV godot_variant set_enable_dynamic_foveation(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		if (p_num_args != 1) {
			ALOGW("set_enable_dynamic_foveation(enabled) requires 1 parameter; got %d", p_num_args);
		} else {
			// Check if foveation is available.
			int foveation_available = vrapi_GetSystemPropertyInt(ovr_java, VRAPI_SYS_PROP_FOVEATION_AVAILABLE);
			if (foveation_available == VRAPI_TRUE) {
				// Retrieve if set enable or disable
				bool enable_dynamic_foveation = api->godot_variant_as_bool(p_args[0]);
				bool dynamic_foveation_valid = false;
				if (ovrmobile::is_oculus_quest_device(ovr_java)) {
					dynamic_foveation_valid = true;
				}

				if (dynamic_foveation_valid) {
					vrapi_SetPropertyInt(ovr_java, VRAPI_DYNAMIC_FOVEATION_ENABLED, enable_dynamic_foveation);
				}
				api->godot_variant_new_bool(&ret, dynamic_foveation_valid);
			}
		}
	)
}

GDCALLINGCONV godot_variant set_swap_interval(godot_object *, void *, void *p_user_data, int, godot_variant **p_args) {
	CHECK_OVR(
	        unsigned int swap_interval = api->godot_variant_as_uint(p_args[0]);
	        if (swap_interval == 1 || swap_interval == 2) {
                ovr_mobile_session->set_swap_interval(swap_interval);
                api->godot_variant_new_bool(&ret, true);
            }

	)
}



GDCALLINGCONV godot_variant get_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrTrackingSpace space = vrapi_GetTrackingSpace(ovr);
		api->godot_variant_new_int(&ret, space);
	)	
}

GDCALLINGCONV godot_variant set_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrTrackingSpace space = (ovrTrackingSpace)api->godot_variant_as_int(p_args[0]); // note that ovrTrackingSpace is an enum in VrApi.h
		ovrResult result = vrapi_SetTrackingSpace(ovr, space);
		if (result == ovrSuccess) api->godot_variant_new_bool(&ret, true); // set the return value to true if vrapi was called successfully
	)	
}

GDCALLINGCONV godot_variant locate_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrTrackingSpace space = (ovrTrackingSpace)api->godot_variant_as_int(p_args[0]); // note that ovrTrackingSpace is an enum in VrApi.h
		ovrPosef result_pose = vrapi_LocateTrackingSpace(ovr, space);
		
		godot_real world_scale = arvr_api->godot_arvr_get_worldscale();
		godot_transform gd_transform;
		ovrmobile::godot_transform_from_ovr_pose(&gd_transform, result_pose, world_scale);

		api->godot_variant_new_transform(&ret, &gd_transform);
	)	
}

