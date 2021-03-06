#include "vulkan_api.h"

void vulkan::data::Depth_Buffer::Init(Device* in_Device,PhysicalDevice* in_phyDevice)
{
	VkImageCreateInfo image_info = {};
	if (this->format == VK_FORMAT_UNDEFINED) this->format = VK_FORMAT_D16_UNORM;

	const VkFormat depth_format = this->format;
	VkFormatProperties props;
	vkGetPhysicalDeviceFormatProperties(in_phyDevice->Get_PhyDevice(), depth_format, &props);
	if (props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) 
	{
		image_info.tiling = VK_IMAGE_TILING_LINEAR;
	}
	else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) 
	{
		image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
	}
	else
	{
		/* Try other depth formats? */
		//std::cout << "depth_format " << depth_format << " Unsupported.\n";
		exit(-1);
	}

	image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image_info.pNext = NULL;
	image_info.imageType = VK_IMAGE_TYPE_2D;
	image_info.format = depth_format;
	image_info.extent.width = in_Device->window_size.x;
	image_info.extent.height = in_Device->window_size.y;
	image_info.extent.depth = 1;
	image_info.mipLevels = 1;
	image_info.arrayLayers = 1;
	image_info.samples = VK_SAMPLE_COUNT_1_BIT;
	//image_info.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	image_info.queueFamilyIndexCount = 0;
	image_info.pQueueFamilyIndices = NULL;
	image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	image_info.flags = 0;

	VkMemoryAllocateInfo mem_alloc = {};
	mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	mem_alloc.pNext = NULL;
	mem_alloc.allocationSize = 0;
	mem_alloc.memoryTypeIndex = 0;

	VkImageViewCreateInfo view_info = {};
	view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	view_info.pNext = NULL;
	view_info.image = VK_NULL_HANDLE;
	view_info.format = depth_format;
	view_info.components.r = VK_COMPONENT_SWIZZLE_R;
	view_info.components.g = VK_COMPONENT_SWIZZLE_G;
	view_info.components.b = VK_COMPONENT_SWIZZLE_B;
	view_info.components.a = VK_COMPONENT_SWIZZLE_A;
	view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	view_info.subresourceRange.baseMipLevel = 0;
	view_info.subresourceRange.levelCount = 1;
	view_info.subresourceRange.baseArrayLayer = 0;
	view_info.subresourceRange.layerCount = 1;
	view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	view_info.flags = 0;

	if (depth_format == VK_FORMAT_D16_UNORM_S8_UINT || 
		depth_format == VK_FORMAT_D24_UNORM_S8_UINT ||
		depth_format == VK_FORMAT_D32_SFLOAT_S8_UINT) 
	{
		view_info.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	VkMemoryRequirements mem_reqs;

	/* Create image */
	vulkan::Error::Window(vkCreateImage(in_Device->device, &image_info, NULL, &this->image),"イメージの作成に失敗");
	vkGetImageMemoryRequirements(in_Device->device, this->image, &mem_reqs);

	mem_alloc.allocationSize = mem_reqs.size;
	
	vulkan::data::Checker::memory_type_from_properties(mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &mem_alloc.memoryTypeIndex);
	/* Use the memory properties to determine the type of memory required */

	/* Allocate memory */
	vulkan::Error::Window(vkAllocateMemory(in_Device->device, &mem_alloc, NULL, &mem),"深度メモリの確保に失敗");

	/* Bind memory */
	vulkan::Error::Window(vkBindImageMemory(in_Device->device, this->image, mem, 0),"深度バインドメモリの作成に失敗");

	/* Create image view */
	view_info.image = this->image;
	vulkan::Error::Window(vkCreateImageView(in_Device->device, &view_info, NULL, &this->view),"深度イメージビューの作成に失敗");
}

void vulkan::data::Depth_Buffer::Uninit(Device* in_Device)
{
	vkDestroyImageView(in_Device->device, this->view, NULL);
	vkDestroyImage(in_Device->device, this->image, NULL);
	vkFreeMemory(in_Device->device, this->mem, NULL);
}
