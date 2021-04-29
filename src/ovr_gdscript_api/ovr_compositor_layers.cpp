#include "../godot_calls.h"
#include "api_common.h"
#include "ovr_compositor_layers.h"

static const char *kClassName = "OvrCompositorLayers";


GDCALLINGCONV void *ovr_compositor_layers_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}


GDCALLINGCONV void ovr_compositor_layers_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
	}
}

static ovrMatrix4f CylinderModelMatrix(
    const int texWidth,
    const int texHeight,
    const ovrVector3f translation,
    const float rotateYaw,
    const float rotatePitch,
    const float radius,
    const float density) {
    const ovrMatrix4f scaleMatrix =
        ovrMatrix4f_CreateScale(radius, radius * (float)texHeight * VRAPI_PI / density, radius);
    const ovrMatrix4f transMatrix =
        ovrMatrix4f_CreateTranslation(translation.x, translation.y, translation.z);
    const ovrMatrix4f rotXMatrix = ovrMatrix4f_CreateRotation(rotatePitch, 0.0f, 0.0f);
    const ovrMatrix4f rotYMatrix = ovrMatrix4f_CreateRotation(0.0f, rotateYaw, 0.0f);

    const ovrMatrix4f m0 = ovrMatrix4f_Multiply(&transMatrix, &scaleMatrix);
    const ovrMatrix4f m1 = ovrMatrix4f_Multiply(&rotXMatrix, &m0);
    const ovrMatrix4f m2 = ovrMatrix4f_Multiply(&rotYMatrix, &m1);

    return m2;
}

static ovrLayerCylinder2 BuildCylinderLayer(
    ovrTextureSwapChain* cylinderSwapChain,
    const int textureWidth,
    const int textureHeight,
    const ovrTracking2* tracking) {
    ovrLayerCylinder2 layer = vrapi_DefaultLayerCylinder2();

    const float fadeLevel = 1.0f;
    layer.Header.ColorScale.x = layer.Header.ColorScale.y = layer.Header.ColorScale.z =
        layer.Header.ColorScale.w = fadeLevel;
    layer.Header.SrcBlend = VRAPI_FRAME_LAYER_BLEND_SRC_ALPHA;
    layer.Header.DstBlend = VRAPI_FRAME_LAYER_BLEND_ONE_MINUS_SRC_ALPHA;

    // layer.Header.Flags = VRAPI_FRAME_LAYER_FLAG_CLIP_TO_TEXTURE_RECT;

    layer.HeadPose = tracking->HeadPose;

    const float density = 4500.0f;
    const float rotateYaw = 0.0f;
    const float rotatePitch = 0.0f;
    const float radius = 3.0f;
    const ovrVector3f translation = {0.0f, 0.0f, 0.0f};

    ovrMatrix4f cylinderTransform = CylinderModelMatrix(
        textureWidth, textureHeight, translation, rotateYaw, rotatePitch, radius, density);

    const float circScale = density * 0.5f / textureWidth;
    const float circBias = -circScale * (0.5f * (1.0f - 1.0f / circScale));

    for (int eye = 0; eye < VRAPI_FRAME_LAYER_EYE_MAX; eye++) {
        ovrMatrix4f modelViewMatrix =
            ovrMatrix4f_Multiply(&tracking->Eye[eye].ViewMatrix, &cylinderTransform);
        layer.Textures[eye].TexCoordsFromTanAngles = ovrMatrix4f_Inverse(&modelViewMatrix);
        layer.Textures[eye].ColorSwapChain = cylinderSwapChain;
        layer.Textures[eye].SwapChainIndex = 0;

        // Texcoord scale and bias is just a representation of the aspect ratio. The positioning
        // of the cylinder is handled entirely by the TexCoordsFromTanAngles matrix.

        const float texScaleX = circScale;
        const float texBiasX = circBias;
        const float texScaleY = 0.5f;
        const float texBiasY = -texScaleY * (0.5f * (1.0f - (1.0f / texScaleY)));

        layer.Textures[eye].TextureMatrix.M[0][0] = texScaleX;
        layer.Textures[eye].TextureMatrix.M[0][2] = texBiasX;
        layer.Textures[eye].TextureMatrix.M[1][1] = texScaleY;
        layer.Textures[eye].TextureMatrix.M[1][2] = texBiasY;

        layer.Textures[eye].TextureRect.width = 1.0f;
        layer.Textures[eye].TextureRect.height = 1.0f;
    }

    return layer;
}


GDCALLINGCONV godot_variant create_test_layer(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(


		int CylinderWidth = 512;
        int CylinderHeight = 128;
        ovrTextureSwapChain* CylinderSwapChain = vrapi_CreateTextureSwapChain3(
            VRAPI_TEXTURE_TYPE_2D,
            GL_SRGB8_ALPHA8,
            CylinderWidth,
            CylinderHeight,
            1,
            1);

        uint32_t* texData =
            (uint32_t*)malloc(CylinderWidth * CylinderHeight * sizeof(uint32_t));

        for (int y = 0; y < CylinderHeight; y++) {
            for (int x = 0; x < CylinderWidth; x++) {
                texData[y * CylinderWidth + x] = (x ^ y) & 64 ? 0xFF6464F0 : 0xFFF06464;
            }
        }

        const int texId = vrapi_GetTextureSwapChainHandle(CylinderSwapChain, 0);
        glBindTexture(GL_TEXTURE_2D, texId);
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            CylinderWidth,
            CylinderHeight,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            texData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
       
	    //float borderColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
        //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glBindTexture(GL_TEXTURE_2D, 0);

        free(texData);





		api->godot_variant_new_bool(&ret, true);
	)	
}


void register_gdnative_compositor_layers(void *p_handle) {
    { // register the constructor and destructor of the OvrCompositorLayers class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_compositor_layers_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_compositor_layers_destructor;

		nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // register all the functions that we want to expose via the OvrCompositorLayers class in GDScript
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &create_test_layer;
		nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "create_test_layer", attributes, method);

	}
}

