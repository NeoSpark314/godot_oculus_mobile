////////////////////////////////////////////////////////////////////////////////////////////////
// This GDNative module is to be considered temporary and experimental. It exposes part
// of the VrApi.h directly to gdscript and is for low level access of VrApi features.
// It might get replaced by dedicated functions in the future.

#ifndef OVR_VR_API_PROXY_H
#define OVR_VR_API_PROXY_H

#ifdef __cplusplus
extern "C" {
#endif

// registers the OvrVrApiProxy class and functions to GDNative and should be called from godot_ovrmobile_nativescript_init
void register_gdnative_vr_api_proxy(void *p_handle);

#ifdef __cplusplus
}
#endif

#endif /* !OVR_VRAPIPROXY */
