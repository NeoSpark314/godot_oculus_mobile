#include "ovr_init_api.h"
#include "api_common.h"

static const char *kClassName = "OvrInitAPI";

void register_gdnative_init_api(void *handle) {
    // register the constructor and destructor of the OvrInitAPI class for use in GDScript
    godot_instance_create_func create = { nullptr, nullptr, nullptr};
    create.create_func = &ovr_init_api_constructor;

    godot_instance_destroy_func destroy = {nullptr, nullptr, nullptr};
    destroy.destroy_func = &ovr_init_api_destructor;

    nativescript_api->godot_nativescript_register_class(handle, kClassName, "Reference", create, destroy);

    // register all the functions that we want to expose via the OvrInitAPI class in GDScript
    godot_instance_method method = {nullptr, nullptr, nullptr};
    godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

    method.method = &set_render_target_size_multiplier;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_render_target_size_multiplier", attributes, method);
}

GDCALLINGCONV void *ovr_init_api_constructor(godot_object *instance, void *method_data) {
    return init_ovr_config_data_struct();
}

GDCALLINGCONV void ovr_init_api_destructor(godot_object *instance, void *method_data, void *user_data) {
    if (user_data) {
        reset_ovr_config_data_struct(static_cast<ovr_config_data_struct *>(user_data));
    }
}

typedef bool (*init_api_logic)(ovrmobile::OvrMobileSession&, int, godot_variant**);

// Utility method to avoid code duplication
godot_variant run_init_api(void *user_data, int num_args, godot_variant **args, init_api_logic logic) {
    bool result = false;
    ovrmobile::OvrMobileSession *session = nullptr;
    if (user_data) {
        auto *ovr_config_data = static_cast<ovr_config_data_struct *>(user_data);
        session = ovr_config_data->ovr_mobile_session;
        // Validate session is not null, and is not initialized.
        if (session && !session->is_initialized()) {
            result = logic(*session, num_args, args);
        }
    }

    godot_variant ret;
    api->godot_variant_new_bool(&ret, result);
    return ret;
}

GDCALLINGCONV godot_variant set_render_target_size_multiplier(godot_object*, void*, void *user_data, int num_args, godot_variant **args) {
    return run_init_api(user_data, num_args, args, [](ovrmobile::OvrMobileSession &session, int num_args, godot_variant **args){
        double multiplier = api->godot_variant_as_real(args[0]);

        // Update the render target size.
        session.set_render_target_size_multiplier(multiplier);
        return true;
    });
}
