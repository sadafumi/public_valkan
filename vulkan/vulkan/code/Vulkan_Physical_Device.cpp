#include "vulkan_api.h"


void vulkan::data::PhysicalDevice::Init(Instance * Instance, Global_Layer_Properties* layer)
{
	uint32_t gpu_count;
	vulkan::Error::Window(vkEnumeratePhysicalDevices(Instance->instance, &gpu_count, NULL),"物理デバイスの個数を取得");
	this->phydev.resize(gpu_count);
	vulkan::Error::Window(vkEnumeratePhysicalDevices(Instance->instance, &gpu_count, this->phydev.data()),"物理デバイスの取得に失敗");

	vkGetPhysicalDeviceQueueFamilyProperties(this->phydev[0], &queue_family_count, NULL);
	queue_props.resize(queue_family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(this->phydev[0], &queue_family_count, queue_props.data());

	vkGetPhysicalDeviceProperties(this->phydev[0], &this->gpu_props);
	vkGetPhysicalDeviceMemoryProperties(this->phydev[0], &this->memory_properties);

	for (auto& layer_props : layer->instance_layer_properties)
	{
		init_device_extension_properties(layer_props);
	}

	//VkPhysicalDeviceProperties dev_props;
	//vkGetPhysicalDeviceProperties(phydev, &dev_props);
}

void vulkan::data::PhysicalDevice::Uninit()
{

}

VkResult vulkan::data::PhysicalDevice::init_device_extension_properties( Global_Layer_Properties::layer_properties & layer_props)
{
	VkExtensionProperties *device_extensions;
	uint32_t device_extension_count;
	VkResult res;
	char *layer_name = NULL;

	layer_name = layer_props.properties.layerName;

	do 
	{
		res = vkEnumerateDeviceExtensionProperties(Get_PhyDevice(), layer_name, &device_extension_count, NULL);
		if (res) return res;
		if (device_extension_count == 0) 
		{
			return VK_SUCCESS;
		}
		layer_props.device_extensions.resize(device_extension_count);
		device_extensions = layer_props.device_extensions.data();
		res = vkEnumerateDeviceExtensionProperties(Get_PhyDevice(), layer_name, &device_extension_count, device_extensions);
	} while (res == VK_INCOMPLETE);

	return res;
}

VkPhysicalDevice vulkan::data::PhysicalDevice::Get_PhyDevice()
{
	return this->phydev[0];
}
