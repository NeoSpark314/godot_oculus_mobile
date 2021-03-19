////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module to access and setup the init parameters for the plugin.
// The methods defined in this class must be invoked prior to initializing the Oculus mobile plugin.

#ifndef OVR_INIT_API_H
#define OVR_INIT_API_H

#include "../godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// Registers the OvrInitAPI class and functions to GDNative.
// This methhod should be called from godot_ovrmobile_nativescript_init.
void register_gdnative_init_api(void *handle);

#ifdef __cplusplus
}
#endif

#endif // OVR_init_api_H
