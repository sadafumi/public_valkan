#include "vulkan_api.h"

void vulkan::data::Image::Init(Device * in_Device, Swap_Chain * in_swapchain)
{
	uint32_t swapchain_count;
	vulkan::Error::Window(vkGetSwapchainImagesKHR(in_Device->device, in_swapchain->swapChain, &swapchain_count, NULL), "swapチェインの個数の取得に失敗");
	this->Images.resize(swapchain_count);
	vulkan::Error::Window(vkGetSwapchainImagesKHR(in_Device->device, in_swapchain->swapChain, &swapchain_count, this->Images.data()), "スワップチェインの取得に失敗");
}

void vulkan::data::Image::Destroy()
{
}

void vulkan::data::Image::Image_Layoutting(Command_Buffer * in_cmd)
{
	std::vector<VkImageMemoryBarrier> barriers;
	barriers.resize(this->Images.size());
	for (uint32_t i = 0; i < barriers.size(); i++)
	{
		VkImageMemoryBarrier barrier{};

		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		barrier.image = this->Images[i];
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.layerCount = 1;
		barrier.subresourceRange.levelCount = 1;
		barriers[i] = barrier;
	}

	vkCmdPipelineBarrier(in_cmd->cmd_buff, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		0, 0, NULL, 0, NULL, barriers.size(), barriers.data());
}

void vulkan::data::Image::barrierResource(Command_Buffer *in_cmd, int index, VkPipelineStageFlags srcStageFlags, VkPipelineStageFlags dstStageFlags, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, VkImageLayout srcImageLayout, VkImageLayout dstImageLayout)
{
	VkImageMemoryBarrier barrier{};

	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.image = this->Images[index];
	barrier.srcAccessMask = srcAccessMask;
	barrier.dstAccessMask = dstAccessMask;
	barrier.oldLayout = srcImageLayout;
	barrier.newLayout = dstImageLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
	vkCmdPipelineBarrier(in_cmd->cmd_buff, srcStageFlags, dstStageFlags, 0, 0, NULL, 0, NULL, 1, &barrier);
}
