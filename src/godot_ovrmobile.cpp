////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "godot_ovrmobile.h"

#include "arvr_interface.h"

#include "ovr_gdscript_api/ovr_base_api.h"
#include "ovr_gdscript_api/ovr_init_api.h"
#include "ovr_gdscript_api/ovr_utilities.h"
#include "ovr_gdscript_api/ovr_compositor_layers.h"
#include "ovr_gdscript_api/ovr_mixed_reality_capture.h"
#include "ovr_gdscript_api/ovr_vr_api_proxy.h"

void GDN_EXPORT godot_ovrmobile_gdnative_singleton() {
	if (arvr_api != NULL) {
		arvr_api->godot_arvr_register_interface(&interface_struct);
	}
}

void GDN_EXPORT godot_ovrmobile_nativescript_init(void *p_handle) {
	if (nativescript_api == NULL) {
		return;
	}

	register_gdnative_base_api(p_handle);
	register_gdnative_init_api(p_handle);
	register_gdnative_utilities(p_handle);
	register_gdnative_compositor_layers(p_handle);
	register_gdnative_vr_api_proxy(p_handle);
	register_gdnative_mrc(p_handle);
}
