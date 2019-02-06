#include "vulkan.h"
#include <assert.h>

void vulkan::Resources::Buffer::Create(Buffer* out_Buffer, std::vector<Vertex> vertexData/*const void * vertexData*/,int stride, bool use_texture, data::Device *in_Device, data::PhysicalDevice* in_PhyDevice)
{
	int vertex_size = vertexData.size() * stride;
	VkBufferCreateInfo buf_info = {};
	buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buf_info.pNext = NULL;
	buf_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	buf_info.size = vertex_size;
	buf_info.queueFamilyIndexCount = 0;
	buf_info.pQueueFamilyIndices = NULL;
	buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	buf_info.flags = 0;
	vulkan::Error::Window(vkCreateBuffer(in_Device->device, &buf_info, NULL, &out_Buffer->buffer),"リソースのバッファの作成に失敗");

	// Memory Allocation
	VkMemoryRequirements memreq;
	
	vkGetBufferMemoryRequirements(in_Device->device, out_Buffer->buffer, &memreq);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memreq.size;
	allocInfo.memoryTypeIndex = UINT32_MAX;
	
	vulkan::Error::Window(vulkan::data::Checker::memory_type_from_properties(in_PhyDevice, memreq.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &allocInfo.memoryTypeIndex), "No mappable, coherent memory");
	vulkan::Error::Window(allocInfo.memoryTypeIndex == UINT32_MAX, "No found available heap.");

	VkDeviceMemory mem;
	vulkan::Error::Window(vkAllocateMemory(in_Device->device, &allocInfo, NULL, &mem),"Allocatの生成に失敗");

	// Set data
	uint8_t* pData;
	vulkan::Error::Window(vkMapMemory(in_Device->device, mem, 0, vertex_size, 0, reinterpret_cast<void**>(&pData)), "バッファマップの作成に失敗");

	memcpy(pData, vertexData.data(), vertex_size);
	vkUnmapMemory(in_Device->device, mem);

	// Associate memory to buffer
	vulkan::Error::Window(vkBindBufferMemory(in_Device->device, out_Buffer->buffer, mem, 0),"BindBufferの作成に失敗");

	out_Buffer->vi_binding.binding = 0;
	out_Buffer->vi_binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	out_Buffer->vi_binding.stride = stride;

	out_Buffer->vi_attribs[0].binding = 0;
	out_Buffer->vi_attribs[0].location = 0;
	out_Buffer->vi_attribs[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	out_Buffer->vi_attribs[0].offset = 0;

	out_Buffer->vi_attribs[1].binding = 0;
	out_Buffer->vi_attribs[1].location = 1;
	out_Buffer->vi_attribs[1].format = use_texture ? VK_FORMAT_R32G32_SFLOAT : VK_FORMAT_R32G32B32A32_SFLOAT;
	out_Buffer->vi_attribs[1].offset = sizeof(float) * 4;
}

void vulkan::Resources::Buffer::Destroy(data::Device * in_device)
{
	vkDestroyBuffer(in_device->device, this->buffer, NULL);
}
