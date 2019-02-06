#include "vulkan.h"


VkResult vulkan::data::Global_Layer_Properties::Init()
{
	uint32_t instance_layer_count;
	VkLayerProperties *vk_props = NULL;
	VkResult err;
	do {
		err = vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
		if (err) return err;

		if (instance_layer_count == 0) {
			return VK_SUCCESS;
		}

		vk_props = new VkLayerProperties[instance_layer_count];

		err = vkEnumerateInstanceLayerProperties(&instance_layer_count, vk_props);
	} while (err == VK_INCOMPLETE);

	/*
	 * Now gather the extension list for each instance layer.
	 */
	for (uint32_t i = 0; i < instance_layer_count; i++) {
		layer_properties layer_props;
		layer_props.properties = vk_props[i];
		err = init_global_extension_properties(layer_props);
		if (err) return err;
		instance_layer_properties.push_back(layer_props);
	}
	delete[] vk_props;

	return err;
}

VkResult vulkan::data::Global_Layer_Properties::init_global_extension_properties(vulkan::data::Global_Layer_Properties::layer_properties &layer_props)
{
	VkExtensionProperties *instance_extensions;
	uint32_t instance_extension_count;
	VkResult res;
	char *layer_name = NULL;

	layer_name = layer_props.properties.layerName;

	do {
		res = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, NULL);
		if (res) return res;

		if (instance_extension_count == 0) {
			return VK_SUCCESS;
		}

		layer_props.instance_extensions.resize(instance_extension_count);
		instance_extensions = layer_props.instance_extensions.data();
		res = vkEnumerateInstanceExtensionProperties(layer_name, &instance_extension_count, instance_extensions);
	} while (res == VK_INCOMPLETE);

	return res;
}

void vulkan::data::Global_Layer_Properties::Uninit()
{
}
