////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that wraps some utility functions that need the VrApi

#ifndef OVR_UTILITIES_H
#define OVR_UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrUtilities class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_utilities(void *p_handle);

#ifdef __cplusplus
}
#endif

#endif /* !OVR_UTILITIES */
