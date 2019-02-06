#include "vulkan.h"

void vulkan::data::Semaphore::Create(Device* in_Device)
{
	VkSemaphoreCreateInfo imageAcquiredSemaphoreCreateInfo;
	imageAcquiredSemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	imageAcquiredSemaphoreCreateInfo.pNext = NULL;
	imageAcquiredSemaphoreCreateInfo.flags = 0;

	vulkan::Error::Window(vkCreateSemaphore(in_Device->device, &imageAcquiredSemaphoreCreateInfo, NULL, &imageAcquiredSemaphore), "CreateSemaphoreƒGƒ‰[");
}
