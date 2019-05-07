#include "vulkan_api.h"
#include <assert.h>

void vulkan::Resources::Buffer::Create(Buffer* out_Buffer, std::vector<Vertex> vertexData,int stride, bool use_texture, data::Device *in_Device)
{
	out_Buffer->vertex_size = vertexData.size() * stride;

	VkBufferCreateInfo buf_info = {};
	buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buf_info.pNext = NULL;
	buf_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	buf_info.size = out_Buffer->vertex_size;
	buf_info.queueFamilyIndexCount = 0;
	buf_info.pQueueFamilyIndices = NULL;
	buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	buf_info.flags = 0;
	vulkan::Error::Window(vkCreateBuffer(in_Device->device, &buf_info, NULL, &out_Buffer->buffer),"Resourcesの生成に失敗");

	// Memory Allocation
	VkMemoryRequirements memreq;
	
	vkGetBufferMemoryRequirements(in_Device->device, out_Buffer->buffer, &memreq);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memreq.size;
	allocInfo.memoryTypeIndex = UINT32_MAX;
	
	vulkan::Error::Window(vulkan::data::Checker::memory_type_from_properties( memreq.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &allocInfo.memoryTypeIndex), "No mappable, coherent memory");
	vulkan::Error::Window(allocInfo.memoryTypeIndex == UINT32_MAX, "No found available heap.");

	
	vulkan::Error::Window(vkAllocateMemory(in_Device->device, &allocInfo, NULL, &out_Buffer->mem),"Allocatの生成に失敗");

	// Set data
	uint8_t* pData;
	vulkan::Error::Window(vkMapMemory(in_Device->device, out_Buffer->mem, 0, out_Buffer->vertex_size, 0, reinterpret_cast<void**>(&pData)), "バッファマップの作成に失敗");

	memcpy(pData, vertexData.data(), out_Buffer->vertex_size);
	vkUnmapMemory(in_Device->device, out_Buffer->mem);

	// Associate memory to buffer
	vulkan::Error::Window(vkBindBufferMemory(in_Device->device, out_Buffer->buffer, out_Buffer->mem, 0),"BindBufferの作成に失敗");

	out_Buffer->vi_binding.binding = 0;
	out_Buffer->vi_binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	out_Buffer->vi_binding.stride = stride;

	VkVertexInputAttributeDescription buff;

	buff.binding = 0;
	buff.location = 0;
	buff.format = VK_FORMAT_R32G32B32A32_SFLOAT;
	buff.offset = 0;
	
	out_Buffer->vi_attribs.push_back(buff);

	buff.binding = 0;
	buff.location = 1;
	buff.format = use_texture ? VK_FORMAT_R32G32_SFLOAT : VK_FORMAT_R32G32B32A32_SFLOAT;
	buff.offset = sizeof(float) * 4;

	out_Buffer->vi_attribs.push_back(buff);

}

//void vulkan::Resources::Buffer::Create_Model(Buffer *out_Buffer, std::vector<mfv::model::Vertex> in_vertex, int in_vertex_size, mfv::model * in_data,data::Device *in_Device)
void vulkan::Resources::Buffer::Create_Model(Buffer *out_Buffer, std::vector<float> in_vertex, int in_vertex_size, mfv::model * in_data, data::Device *in_Device)
{
	in_data = in_data;
	in_vertex = in_vertex;
	
	out_Buffer->vertex_size = in_vertex_size * in_data->stride_size;
	VkBufferCreateInfo buf_info = {};
	buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buf_info.pNext = NULL;
	buf_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	buf_info.size = out_Buffer->vertex_size;
	buf_info.queueFamilyIndexCount = 0;
	buf_info.pQueueFamilyIndices = NULL;
	buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	buf_info.flags = 0;
	vulkan::Error::Window(vkCreateBuffer(in_Device->device, &buf_info, NULL, &out_Buffer->buffer), "リソースのバッファの作成に失敗");

	// Memory Allocation
	VkMemoryRequirements memreq;

	vkGetBufferMemoryRequirements(in_Device->device, out_Buffer->buffer, &memreq);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memreq.size;
	allocInfo.memoryTypeIndex = UINT32_MAX;

	vulkan::Error::Window(vulkan::data::Checker::memory_type_from_properties(memreq.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &allocInfo.memoryTypeIndex), "No mappable, coherent memory");
	vulkan::Error::Window(allocInfo.memoryTypeIndex == UINT32_MAX, "No found available heap.");


	vulkan::Error::Window(vkAllocateMemory(in_Device->device, &allocInfo, NULL, &out_Buffer->mem), "Allocatの生成に失敗");

	// Set data
	uint8_t* pData;
	vulkan::Error::Window(vkMapMemory(in_Device->device, out_Buffer->mem, 0, out_Buffer->vertex_size, 0, reinterpret_cast<void**>(&pData)), "バッファマップの作成に失敗");

	memcpy(pData, in_vertex.data(), out_Buffer->vertex_size);
	vkUnmapMemory(in_Device->device, out_Buffer->mem);

	// Associate memory to buffer
	vulkan::Error::Window(vkBindBufferMemory(in_Device->device, out_Buffer->buffer, out_Buffer->mem, 0), "BindBufferの作成に失敗");

	out_Buffer->vi_binding.binding = 0;
	out_Buffer->vi_binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	out_Buffer->vi_binding.stride = in_data->stride_size;

	int offset = 0;
	int location = 0;
	for (unsigned int i = 0; i < in_data->strides.size(); i++)
	{
		Set_InputAttri(&out_Buffer->vi_attribs,in_data->strides[i],location, &offset);
		location++;
	}
}

void vulkan::Resources::Buffer::Set_InputAttri(std::vector<VkVertexInputAttributeDescription>* in_attri, mfv::model::Stride in_flag,int location, int* offset)
{
	VkVertexInputAttributeDescription buff;
	buff.binding = 0;
	buff.location = location;
	buff.offset = *offset;
	if(in_flag == mfv::model::Stride::Str_vertex)
	{
		buff.format = VK_FORMAT_R32G32B32A32_SFLOAT;
		*offset += sizeof(float) * 4;
	}
	if (in_flag == mfv::model::Stride::Str_normal)
	{
		buff.format = VK_FORMAT_R32G32B32_SFLOAT;
		*offset += sizeof(float) * 3;
	}
	if (in_flag == mfv::model::Stride::Str_uv)
	{
		buff.format = VK_FORMAT_R32G32_SFLOAT;
		*offset += sizeof(float) * 2;
	}
	in_attri->push_back(buff);
}

void vulkan::Resources::Buffer::Destroy(data::Device * in_device)
{
	vkDestroyBuffer(in_device->device, this->buffer, NULL);
	vkFreeMemory(in_device->device, this->mem, NULL);
}
