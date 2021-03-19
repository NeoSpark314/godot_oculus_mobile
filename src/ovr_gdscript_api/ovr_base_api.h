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

#ifdef __cplusplus
}
#endif

#endif /* !GDNATIVE_OVR_base_api_H */
