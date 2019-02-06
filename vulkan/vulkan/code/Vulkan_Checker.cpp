#include "vulkan.h"

bool vulkan::data::Checker::memory_type_from_properties(PhysicalDevice * in_PhyDevice, uint32_t typeBits, VkFlags requirements_mask, uint32_t * typeIndex)
{
	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < in_PhyDevice->memory_properties.memoryTypeCount; i++) 
	{
		if ((typeBits & 1) == 1) 
		{
			// Type is available, does it match user properties?
			if ((in_PhyDevice->memory_properties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask) 
			{
				*typeIndex = i;
				return false;
			}
		}
		typeBits >>= 1;
	}
	// No memory types matched, return failure
	return true;
}
