#include "vulkan.h"

void vulkan::data::Fence::Init(Device* in_Device)
{
	VkFenceCreateInfo fenceInfo;
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.pNext = NULL;
	fenceInfo.flags = 0;
	vkCreateFence(in_Device->device, &fenceInfo, NULL, &this->Fence);
}

void vulkan::data::Fence::Uninit(Device* in_Device)
{
	vkDestroyFence(in_Device->device, this->Fence, NULL);
}
