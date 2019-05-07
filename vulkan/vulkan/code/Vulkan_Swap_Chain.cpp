#include "vulkan_api.h"


void vulkan::data::Swap_Chain::Init(PhysicalDevice* in_phyDevice,Device* in_Device, Surface* in_Surface, VkImageUsageFlags usageFlags)
{
	VkSurfaceCapabilitiesKHR surfCapabilities;


	std::vector< VkPresentModeKHR > presentModes;
	std::vector< VkSurfaceFormatKHR > surfaceFormats;
	
	vulkan::Error::Window(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &surfCapabilities), "物理デバイスのSurfaceCapabilitiesの取得に失敗");

	VkBool32 surfaceSupported; 
	vulkan::Error::Window(vkGetPhysicalDeviceSurfaceSupportKHR(in_phyDevice->Get_PhyDevice(), in_Device->queue_Family_index, in_Surface->surface, &surfaceSupported),"物理DeviceからSurfaceサポートを取得");
	VkSurfaceCapabilitiesKHR surfaceCaps;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &surfaceCaps);
	uint32_t surfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &surfaceFormatCount, NULL);
	surfaceFormats.resize(surfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &surfaceFormatCount, surfaceFormats.data());
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &presentModeCount, NULL);
	presentModes.resize(presentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &presentModeCount, presentModes.data());

	VkSurfaceTransformFlagBitsKHR preTransform;
	if (surfCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	}
	else
	{
		preTransform = surfCapabilities.currentTransform;
	}
	for (uint32_t i = 0; i < surfaceFormatCount; i++)
	{
		auto c = surfaceFormats[i];
		std::cout << "Supported Format Check...\n" << std::endl;
	}

	VkSwapchainCreateInfoKHR swapchain_ci = {};
	swapchain_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchain_ci.pNext = NULL;
	swapchain_ci.surface = in_Surface->surface;
	swapchain_ci.minImageCount = surfCapabilities.minImageCount;
	swapchain_ci.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
	swapchain_ci.imageExtent.width = in_Device->window_size.x;
	swapchain_ci.imageExtent.height = in_Device->window_size.y;
	swapchain_ci.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
	swapchain_ci.imageUsage = usageFlags;
	swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchain_ci.preTransform = preTransform;
	swapchain_ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_ci.presentMode = VK_PRESENT_MODE_FIFO_KHR;
	swapchain_ci.imageArrayLayers = 1;
	swapchain_ci.oldSwapchain = VK_NULL_HANDLE;
	swapchain_ci.clipped = true;


	vulkan::Error::Window(vkCreateSwapchainKHR(in_Device->device, &swapchain_ci, NULL, &swapChain), "swapChainの作成に失敗");
}

void vulkan::data::Swap_Chain::Uninit(Device* in_Device)
{
	vkDestroySwapchainKHR(in_Device->device, swapChain, NULL);
}

