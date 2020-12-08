////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that exposes part of the oculus api.
// Each exported class implements one section of the VrApi.h.
// This implements the <Guardian System> section.

#ifndef OVR_base_api_H
#define OVR_base_api_H

#include "../godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrBaseAPI class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_base_api(void *p_handle);

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


#ifdef __cplusplus
}
#endif

#endif /* !GDNATIVE_OVR_base_api_H */
