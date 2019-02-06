#include "vulkan.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>


void vulkan::data::Swap_Chain::Init(Utility::Int_Vec2 in_win,PhysicalDevice* in_phyDevice,Device* in_Device, Surface* in_Surface, VkImageUsageFlags usageFlags)
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
	vkGetPhysicalDeviceSurfaceFormatsKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &surfaceFormatCount, nullptr);
	surfaceFormats.resize(surfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &surfaceFormatCount, surfaceFormats.data());
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(in_phyDevice->Get_PhyDevice(), in_Surface->surface, &presentModeCount, nullptr);
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
		OutputDebugString("Supported Format Check...");
	}

	VkSwapchainCreateInfoKHR swapchain_ci = {};
	swapchain_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchain_ci.pNext = NULL;
	swapchain_ci.surface = in_Surface->surface;
	swapchain_ci.minImageCount = surfCapabilities.minImageCount;
	swapchain_ci.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
	swapchain_ci.imageExtent.width = in_win.x;
	swapchain_ci.imageExtent.height = in_win.y;
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

//void test()
//{
//
//	VkSurfaceCapabilitiesKHR surfCapabilities;
//
//	vulkan::Error::Window(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(in_phyDevice->Get_PhyDevice(), surface, &surfCapabilities), "物理デバイスのSurfaceCapabilitiesの取得に失敗");
//	uint32_t presentModeCount;
//	vulkan::Error::Window(vkGetPhysicalDeviceSurfacePresentModesKHR(in_phyDevice->Get_PhyDevice(), surface, &presentModeCount, NULL), "物理デバイスのプレゼントモードの取得に失敗");
//	VkPresentModeKHR *presentModes = new VkPresentModeKHR[presentModeCount];
//	vulkan::Error::Window(vkGetPhysicalDeviceSurfacePresentModesKHR(in_phyDevice->Get_PhyDevice(), surface, &presentModeCount, presentModes), "物理デバイスのプレゼントモードの取得に失敗");
//
//	VkExtent2D swapchainExtent;
//	// width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
//	if (surfCapabilities.currentExtent.width == 0xFFFFFFFF)
//	{
//		// If the surface size is undefined, the size is set to
//		// the size of the images requested.
//		swapchainExtent.width = in_win.x;
//		swapchainExtent.height = in_win.y;
//		if (swapchainExtent.width < surfCapabilities.minImageExtent.width)
//		{
//			swapchainExtent.width = surfCapabilities.minImageExtent.width;
//		}
//		else if (swapchainExtent.width > surfCapabilities.maxImageExtent.width)
//		{
//			swapchainExtent.width = surfCapabilities.maxImageExtent.width;
//		}
//
//		if (swapchainExtent.height < surfCapabilities.minImageExtent.height)
//		{
//			swapchainExtent.height = surfCapabilities.minImageExtent.height;
//		}
//		else if (swapchainExtent.height > surfCapabilities.maxImageExtent.height)
//		{
//			swapchainExtent.height = surfCapabilities.maxImageExtent.height;
//		}
//	}
//	else
//	{
//		swapchainExtent = surfCapabilities.currentExtent;
//	}
//	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;
//
//	uint32_t desiredNumberOfSwapChainImages = surfCapabilities.minImageCount;
//
//	VkSurfaceTransformFlagBitsKHR preTransform;
//	if (surfCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
//	{
//		preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
//	}
//	else
//	{
//		preTransform = surfCapabilities.currentTransform;
//	}
//
//	// Find a supported composite alpha mode - one of these is guaranteed to be set
//	VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
//	VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] =
//	{
//		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
//		VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
//		VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
//		VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
//	};
//	for (uint32_t i = 0; i < sizeof(compositeAlphaFlags); i++)
//	{
//		if (surfCapabilities.supportedCompositeAlpha & compositeAlphaFlags[i])
//		{
//			compositeAlpha = compositeAlphaFlags[i];
//			break;
//		}
//	}
//
//	VkSwapchainCreateInfoKHR swapchain_ci = {};
//	swapchain_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
//	swapchain_ci.pNext = NULL;
//	swapchain_ci.surface = surface;
//	swapchain_ci.minImageCount = desiredNumberOfSwapChainImages;
//	swapchain_ci.imageFormat = surfaceFormat;
//	swapchain_ci.imageExtent.width = swapchainExtent.width;
//	swapchain_ci.imageExtent.height = swapchainExtent.height;
//	swapchain_ci.preTransform = preTransform;
//	swapchain_ci.compositeAlpha = compositeAlpha;
//	swapchain_ci.imageArrayLayers = 1;
//	swapchain_ci.presentMode = swapchainPresentMode;
//	swapchain_ci.oldSwapchain = VK_NULL_HANDLE;
//	swapchain_ci.clipped = true;
//	swapchain_ci.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
//	swapchain_ci.imageUsage = usageFlags;
//	swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
//	swapchain_ci.queueFamilyIndexCount = 0;
//	swapchain_ci.pQueueFamilyIndices = NULL;
//	uint32_t queueFamilyIndices[2] = { (uint32_t)in_Device->graphics_queue_family_index, (uint32_t)present_queue_family_index };
//	if (in_Device->graphics_queue_family_index != present_queue_family_index)
//	{
//		// If the graphics and present queues are from different queue families,
//		// we either have to explicitly transfer ownership of images between the
//		// queues, or we have to create the swapchain with imageSharingMode
//		// as VK_SHARING_MODE_CONCURRENT
//		swapchain_ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
//		swapchain_ci.queueFamilyIndexCount = 2;
//		swapchain_ci.pQueueFamilyIndices = queueFamilyIndices;
//	}
//
//}