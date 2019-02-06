#include "vulkan.h"


void vulkan::data::Device::Init(PhysicalDevice * PhyDevice)
{
	VkDeviceQueueCreateInfo Queue_info = {};
	uint32_t qfamily_count;
	VkQueueFamilyProperties *queue_props;
	vkGetPhysicalDeviceQueueFamilyProperties(PhyDevice->Get_PhyDevice(), &qfamily_count, NULL);
	queue_props = new VkQueueFamilyProperties[qfamily_count];
	vkGetPhysicalDeviceQueueFamilyProperties(PhyDevice->Get_PhyDevice(), &qfamily_count, queue_props);

	for (unsigned int j = 0; j < qfamily_count; j++)
	{
		if (queue_props[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			Queue_info.queueFamilyIndex = j;
			break;
		}
	}

	queue_Family_index = Queue_info.queueFamilyIndex;
	float queue_priorities[1] = { 0.0 };
	Queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	Queue_info.pNext = NULL;
	Queue_info.queueCount = 1;
	Queue_info.pQueuePriorities = queue_priorities;
	//Queue_info.queueFamilyIndex = PhyDevice->queue_family_count;

	std::vector<const char *> device_extension_names;
	std::vector<const char *> device_layers_names;

	device_layers_names.push_back("VK_LAYER_LUNARG_standard_validation");
	device_extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

	VkDeviceCreateInfo Create_info = {};
	Create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	Create_info.pNext = NULL;
	//Create_info.flags = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
	Create_info.flags = 0;
	Create_info.queueCreateInfoCount = 1;
	Create_info.pQueueCreateInfos = &Queue_info;
	Create_info.enabledLayerCount = (uint32_t)device_layers_names.size();
	Create_info.ppEnabledLayerNames = device_layers_names.size() ? device_layers_names.data() : NULL;
	Create_info.enabledExtensionCount = (uint32_t)device_extension_names.size();
	Create_info.ppEnabledExtensionNames = device_extension_names.size() ? device_extension_names.data() : NULL;
	Create_info.pEnabledFeatures = NULL;
	
	Create_info.enabledLayerCount = 0;
	Create_info.ppEnabledLayerNames = NULL;

	vulkan::Error::Window(vkCreateDevice(PhyDevice->Get_PhyDevice(), &Create_info, NULL, &this->device),"デバイスの生成に失敗");

	delete[] queue_props;
}

void vulkan::data::Device::Uninit()
{
	vkDeviceWaitIdle(this->device);
	vkDestroyDevice(this->device, NULL);
}
