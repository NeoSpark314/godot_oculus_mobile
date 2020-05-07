#include "config_common.h"
#include "ovr_mixed_reality_capture.h"

#include "OVR_Mrc_Shim.h"
#include "../Source/OVR_Mrc_Shim.cpp"

static const char *kClassName = "OvrMRC";

// No need to put these functions into the header; they are only exposed via the .gdns api
GDCALLINGCONV void *ovr_mrc_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovr_mrc_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);

GDCALLINGCONV godot_variant initialize(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant set_mrc_activation_mode(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_mrc_activation_mode(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant is_mrc_enabled(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant is_mrc_activated(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant set_mrc_input_video_buffer_type(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant set_mrc_audio_sample_rate(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant update(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_external_camera_count(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant get_external_camera_intrinsics(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant get_external_camera_extrinsics(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);

GDCALLINGCONV godot_variant sync_mrc_frame(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant encode_mrc_frame(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
GDCALLINGCONV godot_variant encode_mrc_frame_with_dual_texture(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);



void register_gdnative_mrc(void *p_handle) {
    { // register the constructor and destructor of the OvrUtilitites class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_mrc_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_mrc_destructor;

		nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // register all the functions that we want to expose via the Ovrmrc class in GDScript
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

   		method.method = &initialize;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "initialize", attributes, method);

   		method.method = &set_mrc_activation_mode;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_mrc_activation_mode", attributes, method);
   		method.method = &get_mrc_activation_mode;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_mrc_activation_mode", attributes, method);

   		method.method = &is_mrc_enabled;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "is_mrc_enabled", attributes, method);
   		method.method = &is_mrc_activated;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "is_mrc_activated", attributes, method);

   		method.method = &set_mrc_input_video_buffer_type;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_mrc_input_video_buffer_type", attributes, method);
   		method.method = &set_mrc_audio_sample_rate;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "set_mrc_audio_sample_rate", attributes, method);

   		method.method = &update;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "update", attributes, method);
   		method.method = &get_external_camera_count;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_external_camera_count", attributes, method);

   		method.method = &get_external_camera_intrinsics;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_external_camera_intrinsics", attributes, method);
   		method.method = &get_external_camera_extrinsics;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_external_camera_extrinsics", attributes, method);

   		method.method = &sync_mrc_frame;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "sync_mrc_frame", attributes, method);
   		method.method = &encode_mrc_frame;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "encode_mrc_frame", attributes, method);
   		method.method = &encode_mrc_frame_with_dual_texture;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "encode_mrc_frame_with_dual_texture", attributes, method);
	}
}


GDCALLINGCONV void *ovr_mrc_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}


GDCALLINGCONV void ovr_mrc_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
    //ovrm_UnloadSharedLibrary();
    if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
        ovrm_GetAPIs()->Shutdown();
	}
}


GDCALLINGCONV godot_variant initialize(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        bool result_load_shared_library = ovrm_LoadSharedLibrary(nullptr);
        if (!result_load_shared_library) {
            ALOGE("Godot OvrMrc: initialize(): failed to load shared library");
    		api->godot_variant_new_bool(&ret, false);
            return ret;
        }

        if (!ovrm_GetAPIs()) {
            ALOGE("Godot OvrMrc: initialize(): ovrm_GetAPIs() failed to return API.");
    		api->godot_variant_new_bool(&ret, false);
            return ret;
        }

        int majorVersion = 0;
        int minorVersion = 0;
        int patchVersion = 0;
        ovrm_GetAPIs()->GetVersions(&majorVersion, &minorVersion, &patchVersion);
        ALOGV("Godot OvrMrc: initializing ovrm version %d.%d.%d", majorVersion, minorVersion, patchVersion);

        ovrmResult result_ovrm_initialize = ovrm_GetAPIs()->Initialize(ovr, ovr_java->Vm, ovr_java->ActivityObject);

        if (result_ovrm_initialize != ovrmSuccess) {
            ALOGE("Godot OvrMrc: initialize(): ovrm_Initialize(...) failed with code %d", result_ovrm_initialize);
            api->godot_variant_new_bool(&ret, false);
            return ret;
        } 
          
        ovrmResult result_ovrm_configure_gles = ovrm_GetAPIs()->ConfigureGLES(eglGetCurrentContext(), false, false);
        if (result_ovrm_configure_gles != ovrmSuccess) {
            ALOGE("Godot OvrMrc: initialize(): ovrm_ConfigureGLES(...) failed with code %d", result_ovrm_configure_gles);
            api->godot_variant_new_bool(&ret, false);
            return ret;
        }
        ALOGV("Godot OvrMrc: current egl context = %d", eglGetCurrentContext());

        api->godot_variant_new_bool(&ret, true);
    );
}

GDCALLINGCONV godot_variant set_mrc_activation_mode(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        if (p_num_args != 1) {
            ALOGE("Godot OvrMrc: set_mrc_activation_mode(int) requires 1 parameter; got %d", p_num_args);
        } else {
            int activationMode = api->godot_variant_as_int(p_args[0]);

            ovrmResult result = ovrm_GetAPIs()->SetMrcActivationMode((ovrmMediaMrcActivationMode)activationMode);
            if (result != ovrmSuccess) {
                ALOGE("Godot OvrMrc: set_mrc_activation_mode(%d) failed with code %d", activationMode, result);
                api->godot_variant_new_bool(&ret, false);
                return ret;
            } else {
                ALOGV("Godot OvrMrc: set_mrc_activation_mode(%d) called.", activationMode);
            }

            api->godot_variant_new_bool(&ret, true);
        }
    );
}

GDCALLINGCONV godot_variant get_mrc_activation_mode(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        ovrmMediaMrcActivationMode value = ovrmMediaMrcActivationMode_EnumSize;
        ovrmResult result = ovrm_GetAPIs()->GetMrcActivationMode(&value);
        if (result != ovrmSuccess) {
            ALOGE("Godot OvrMrc: get_mrc_activation_mode() failed with code %d", result);
        }
        api->godot_variant_new_int(&ret, value);
    );
}

GDCALLINGCONV godot_variant is_mrc_enabled(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        ovrmBool value = false;
        ovrmResult result = ovrm_GetAPIs()->IsMrcEnabled(&value);
        if (result != ovrmSuccess) {
            ALOGE("Godot OvrMrc: is_mrc_enabled() failed with code %d", result);
            api->godot_variant_new_bool(&ret, false);
            return ret;
        }
        api->godot_variant_new_bool(&ret, value);
    );
}

GDCALLINGCONV godot_variant is_mrc_activated(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        ovrmBool value = false;
        ovrmResult result = ovrm_GetAPIs()->IsMrcActivated(&value);
        if (result != ovrmSuccess) {
            ALOGE("Godot OvrMrc: is_mrc_activated() failed with code %d", result);
            api->godot_variant_new_bool(&ret, false);
            return ret;
        }
        api->godot_variant_new_bool(&ret, value);
    );
}

GDCALLINGCONV godot_variant set_mrc_input_video_buffer_type(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        if (p_num_args != 1) {
            ALOGE("Godot OvrMrc: set_mrc_input_video_buffer_type(int) requires 1 parameter; got %d", p_num_args);
        } else {
            int mode = api->godot_variant_as_int(p_args[0]);

            ovrmResult result = ovrm_GetAPIs()->SetMrcInputVideoBufferType((ovrmMediaInputVideoBufferType)mode);
            if (result != ovrmSuccess) {
                ALOGE("Godot OvrMrc: set_mrc_input_video_buffer_type(%d) failed with code %d", mode, result);
                api->godot_variant_new_bool(&ret, false);
                return ret;
            }

            api->godot_variant_new_bool(&ret, true);
        }
    );
}

GDCALLINGCONV godot_variant set_mrc_audio_sample_rate(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        if (p_num_args != 1) {
            ALOGE("Godot OvrMrc: set_mrc_audio_sample_rate(int sampleRate) requires 1 parameter; got %d", p_num_args);
        } else {
            int rate = api->godot_variant_as_int(p_args[0]);

            ovrmResult result = ovrm_GetAPIs()->SetMrcAudioSampleRate(rate);
            if (result != ovrmSuccess) {
                ALOGE("Godot OvrMrc: set_mrc_audio_sample_rate(%d) failed with code %d", rate, result);
                api->godot_variant_new_bool(&ret, false);
                return ret;
            }

            api->godot_variant_new_bool(&ret, true);
        }
    );
}


GDCALLINGCONV godot_variant update(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        ovrmResult result = ovrm_GetAPIs()->Update();
        if (result != ovrmSuccess) {
            ALOGE("Godot OvrMrc: update() failed with code %d", result);
            api->godot_variant_new_bool(&ret, false);
            return ret;
        }

        api->godot_variant_new_bool(&ret, true);
    );
}


GDCALLINGCONV godot_variant get_external_camera_count(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        int camera_count = 0;
        ovrmResult result = ovrm_GetAPIs()->GetExternalCameraCount(&camera_count);
        if (result != ovrmSuccess) {
            ALOGE("Godot OvrMrc: get_external_camera_count() failed with code %d", result);
            api->godot_variant_new_int(&ret, 0);
            return ret;
        }
        api->godot_variant_new_int(&ret, camera_count);
    );
}


GDCALLINGCONV godot_variant get_external_camera_intrinsics(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        if (p_num_args != 1) {
            ALOGE("Godot OvrMrc: get_external_camera_intrinsics(int cameraId) requires 1 parameter; got %d", p_num_args);
        } else {
            int cameraId = api->godot_variant_as_int(p_args[0]);
            ovrmCameraIntrinsics cameraIntrinsics;

            ovrmResult result = ovrm_GetAPIs()->GetExternalCameraIntrinsics(cameraId, &cameraIntrinsics);
            if (result != ovrmSuccess) {
                ALOGE("Godot OvrMrc: get_external_camera_intrinsics(%d) failed with code %d", cameraId, result);
                api->godot_variant_new_bool(&ret, false);
                return ret;
            }

            /* For reference the intrinsic struct returned by ovrm
            typedef struct {
                ovrmBool IsValid;
                double LastChangedTimeSeconds;
                ovrmFovf FOVPort;
                float VirtualNearPlaneDistanceMeters;
                float VirtualFarPlaneDistanceMeters;
                ovrmSizei ImageSensorPixelResolution;
                } ovrmCameraIntrinsics;
            */
            godot_variant vIsValid;
            godot_variant vLastChangedTimeSeconds;
            godot_variant vFOVPort_UpTan;
            godot_variant vFOVPort_DownTan;
            godot_variant vFOVPort_LeftTan;

            godot_variant vFOVPort_RightTan;
            godot_variant vVirtualNearPlaneDistanceMeters;
            godot_variant vVirtualFarPlaneDistanceMeters;
            godot_variant vImageSensorPixelResolution_w;
            godot_variant vImageSensorPixelResolution_h;

            api->godot_variant_new_bool(&vIsValid, cameraIntrinsics.IsValid);
            api->godot_variant_new_real(&vLastChangedTimeSeconds, cameraIntrinsics.LastChangedTimeSeconds); //NOTE this was original double
            api->godot_variant_new_real(&vFOVPort_UpTan, cameraIntrinsics.FOVPort.UpTan);
            api->godot_variant_new_real(&vFOVPort_DownTan, cameraIntrinsics.FOVPort.DownTan);
            api->godot_variant_new_real(&vFOVPort_LeftTan, cameraIntrinsics.FOVPort.LeftTan);
            api->godot_variant_new_real(&vFOVPort_RightTan, cameraIntrinsics.FOVPort.RightTan);
            
            api->godot_variant_new_real(&vVirtualNearPlaneDistanceMeters, cameraIntrinsics.VirtualNearPlaneDistanceMeters);
            api->godot_variant_new_real(&vVirtualFarPlaneDistanceMeters, cameraIntrinsics.VirtualFarPlaneDistanceMeters);

            api->godot_variant_new_int(&vImageSensorPixelResolution_w, cameraIntrinsics.ImageSensorPixelResolution.w);
            api->godot_variant_new_int(&vImageSensorPixelResolution_h, cameraIntrinsics.ImageSensorPixelResolution.h);

   			godot_array gd_returnArray; // for now we return the transform and scale in a godot array; maybe and Area with a BoxShape would be nice?
			api->godot_array_new(&gd_returnArray);

			api->godot_array_push_back(&gd_returnArray, &vIsValid);
			api->godot_array_push_back(&gd_returnArray, &vLastChangedTimeSeconds);
			api->godot_array_push_back(&gd_returnArray, &vFOVPort_UpTan);
			api->godot_array_push_back(&gd_returnArray, &vFOVPort_DownTan);
			api->godot_array_push_back(&gd_returnArray, &vFOVPort_LeftTan);
			api->godot_array_push_back(&gd_returnArray, &vFOVPort_RightTan);
			api->godot_array_push_back(&gd_returnArray, &vVirtualNearPlaneDistanceMeters);
			api->godot_array_push_back(&gd_returnArray, &vVirtualFarPlaneDistanceMeters);
			api->godot_array_push_back(&gd_returnArray, &vImageSensorPixelResolution_w);
			api->godot_array_push_back(&gd_returnArray, &vImageSensorPixelResolution_h);

			api->godot_variant_new_array(&ret, &gd_returnArray); // set the return value to be the constructed array
			api->godot_array_destroy(&gd_returnArray);
        }
    );
}

// Note this is a duplicate of ovrmobile::godot_transform_from_ovr_pose that takes the different ovrmPosef type
// as input. 
void godot_transform_from_ovrm_pose(godot_transform *dest, const ovrmPosef &pose, const float world_scale) {
	godot_quat q;
	godot_basis basis;
	godot_vector3 origin;

	api->godot_quat_new(&q, pose.Orientation.x, pose.Orientation.y, pose.Orientation.z, pose.Orientation.w);
	api->godot_basis_new_with_euler_quat(&basis, &q);

	api->godot_vector3_new(&origin, pose.Position.x * world_scale, pose.Position.y * world_scale, pose.Position.z * world_scale);
	api->godot_transform_new(dest, &basis, &origin);
}

GDCALLINGCONV godot_variant get_external_camera_extrinsics(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        if (p_num_args != 1) {
            ALOGE("Godot OvrMrc: get_external_camera_extrinsics(int cameraId) requires 1 parameter; got %d", p_num_args);
        } else {
            int cameraId = api->godot_variant_as_int(p_args[0]);
            ovrmCameraExtrinsics cameraExtrinsics;

            ovrmResult result = ovrm_GetAPIs()->GetExternalCameraExtrinsics(cameraId, &cameraExtrinsics);
            if (result != ovrmSuccess) {
                ALOGE("Godot OvrMrc: get_external_camera_extrinsics(%d) failed with code %d", cameraId, result);
                api->godot_variant_new_bool(&ret, false);
                return ret;
            }

            /* For reference the intrinsic struct returned by ovrm
            typedef struct {
                ovrmBool IsValid;
                double LastChangedTimeSeconds;
                ovrmCameraStatus CameraStatus;
                ovrmNode AttachedToNode;
                ovrmPosef RelativePose;
            } ovrmCameraExtrinsics;
            */
            godot_variant vIsValid;
            godot_variant vLastChangedTimeSeconds;
            godot_variant vCameraStatus;
            godot_variant vAttachedToNode;
            godot_variant vRelativePose;

            api->godot_variant_new_bool(&vIsValid, cameraExtrinsics.IsValid);
            api->godot_variant_new_real(&vLastChangedTimeSeconds, cameraExtrinsics.LastChangedTimeSeconds); //NOTE this was original double
            api->godot_variant_new_int(&vCameraStatus, cameraExtrinsics.CameraStatus);
            api->godot_variant_new_int(&vAttachedToNode, cameraExtrinsics.AttachedToNode);

			godot_transform gd_transform;
            godot_real world_scale = arvr_api->godot_arvr_get_worldscale();
   			godot_transform_from_ovrm_pose(&gd_transform, cameraExtrinsics.RelativePose, world_scale);
            api->godot_variant_new_transform(&vRelativePose, &gd_transform);

   			godot_array gd_returnArray; // for now we return the transform and scale in a godot array; maybe and Area with a BoxShape would be nice?
			api->godot_array_new(&gd_returnArray);

			api->godot_array_push_back(&gd_returnArray, &vIsValid);
			api->godot_array_push_back(&gd_returnArray, &vLastChangedTimeSeconds);
			api->godot_array_push_back(&gd_returnArray, &vCameraStatus);
			api->godot_array_push_back(&gd_returnArray, &vAttachedToNode);
			api->godot_array_push_back(&gd_returnArray, &vRelativePose);

			api->godot_variant_new_array(&ret, &gd_returnArray); // set the return value to be the constructed array
			api->godot_array_destroy(&gd_returnArray);
        }
    );
}


GDCALLINGCONV godot_variant sync_mrc_frame(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        if (p_num_args != 1) {
            ALOGE("Godot OvrMrc: sync_mrc_frame(int syncId) requires 1 parameter; got %d", p_num_args);
        } else {
            int syncId = api->godot_variant_as_int(p_args[0]);

            ovrmResult result = ovrm_GetAPIs()->SyncMrcFrame(syncId);
            if (result != ovrmSuccess) {
                ALOGE("Godot OvrMrc: sync_mrc_frame(%d) failed with code %d", syncId, result);
                api->godot_variant_new_bool(&ret, false);
                return ret;
            }
            api->godot_variant_new_bool(&ret, true);
        }
    );
}

GDCALLINGCONV godot_variant encode_mrc_frame(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        if (p_num_args != 2) {
            ALOGE("Godot OvrMrc: encode_mrc_frame(int textureHandle, double timestamp) requires 3 parameter; got %d", p_num_args);
        } else {
            ovrmTextureHandle textureHandle = (ovrmTextureHandle)api->godot_variant_as_int(p_args[0]);
            double timestamp = api->godot_variant_as_int(p_args[1]);

            int outSyncId = 0;
            ovrmResult result = ovrm_GetAPIs()->EncodeMrcFrame((void*)textureHandle, NULL, 0, 2/*audioChannels*/, timestamp, &outSyncId);
            if (result != ovrmSuccess) {
                ALOGE("Godot OvrMrc: encode_mrc_frame(%d, %f) failed with code %d", (int)textureHandle, timestamp, result);
                api->godot_variant_new_int(&ret, 0);
                return ret;
            }
            ALOGV("Godot OvrMrc: encode_mrc_frame(%d, %f) -> %d", (int)textureHandle, timestamp, outSyncId);
            api->godot_variant_new_int(&ret, outSyncId);
        }
    );
}


GDCALLINGCONV godot_variant encode_mrc_frame_with_dual_texture(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
        if (p_num_args != 3) {
            ALOGE("Godot OvrMrc: encode_mrc_frame_with_dual_texture(int backgroundTextureHandle, int foregroundTextureHandle, double timestamp) requires 3 parameter; got %d", p_num_args);
        } else {
            ovrmTextureHandle backgroundTextureHandle = (ovrmTextureHandle)api->godot_variant_as_int(p_args[0]);
            ovrmTextureHandle foregroundTextureHandle = (ovrmTextureHandle)api->godot_variant_as_int(p_args[1]);
            double timestamp = api->godot_variant_as_real(p_args[2]);

            int outSyncId = 0;
            ovrmResult result = ovrm_GetAPIs()->EncodeMrcFrameWithDualTextures((void*)backgroundTextureHandle, (void*)foregroundTextureHandle, NULL, 0, 2/*audioChannels*/, timestamp, &outSyncId);
            if (result != ovrmSuccess) {
                ALOGE("Godot OvrMrc: encode_mrc_frame_with_dual_texture(%d, %d, %f) failed with code %d", (int)backgroundTextureHandle, (int)foregroundTextureHandle, timestamp, result);
                api->godot_variant_new_bool(&ret, false);
                return ret;
            }
            api->godot_variant_new_int(&ret, outSyncId);
        }
    );
}

