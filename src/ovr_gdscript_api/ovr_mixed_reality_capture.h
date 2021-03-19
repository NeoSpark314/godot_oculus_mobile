////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that wraps some utility functions that need the VrApi

#ifndef OVR_MRC_H
#define OVR_MRC_H

#include "../godot_calls.h"

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrUtilities class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_mrc(void *p_handle);

#ifdef __cplusplus
}
#endif

#endif /* !OVR_MRC */
