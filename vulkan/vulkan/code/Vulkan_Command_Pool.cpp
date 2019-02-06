#include "vulkan.h"

void vulkan::data::Command_Pool::Init(Device* In_Device)
{
	VkCommandPoolCreateInfo cmd_pool_info = {};
	cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_info.queueFamilyIndex = In_Device->queue_Family_index;
	cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	vulkan::Error::Window(vkCreateCommandPool(In_Device->device, &cmd_pool_info, NULL, &cmd_pool),"コマンドプールの作成に失敗");
}

void vulkan::data::Command_Pool::Uninit(Device* In_Device)
{
	vkDestroyCommandPool(In_Device->device, this->cmd_pool, NULL);
}
