#include "vulkan.h"

void vulkan::data::Graphic_Queue::Init(Device* in_Device)
{
	vkGetDeviceQueue(in_Device->device, in_Device->queue_Family_index, 0, &graphics_queue);
	graphics_queue_family_index = in_Device->queue_Family_index;
	if (graphics_queue_family_index == present_queue_family_index)
	{
		present_queue = graphics_queue;
	}
	else 
	{
		vkGetDeviceQueue(in_Device->device, present_queue_family_index, 0, &present_queue);
	}
}

void vulkan::data::Graphic_Queue::Uninit(Device*)
{
}
