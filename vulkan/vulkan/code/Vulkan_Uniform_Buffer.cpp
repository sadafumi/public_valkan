#include "vulkan_api.h"

void vulkan::data::Uniform_Buffer::Init(Device* in_Device)
{
	float fov = glm::radians(60.0f);
	if (in_Device->window_size.x > in_Device->window_size.y)
	{
		fov *= static_cast<float>(in_Device->window_size.y) / static_cast<float>(in_Device->window_size.x);
	}
	Projection = glm::perspective(fov, static_cast<float>(in_Device->window_size.x) / static_cast<float>(in_Device->window_size.y), 0.1f, 100.0f);

	View = glm::lookAt(glm::vec3(0, 0, 10),	glm::vec3(0, 0, 0),	glm::vec3(0, 1, 0));   
	
	Model = glm::mat4(1.0f);
	Clip = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f);

	//Projection = Utility::mtx4x4::Perspective(fov, static_cast<float>(in_Device->window_size.x) / static_cast<float>(in_Device->window_size.y), 0.1f, 100.0f);
	//View = Utility::mtx4x4::LookAt(Utility::Vec3(0, 0, 10), Utility::Vec3(0, 0, 0), Utility::Vec3(0, 1, 0));
	//Model = Utility::mtx4x4(1.0f);
	//Clip = Utility::mtx4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f);

	VkBufferCreateInfo buf_info = {};
	buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buf_info.pNext = NULL;
	buf_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	buf_info.size = sizeof(Model);
	buf_info.queueFamilyIndexCount = 0;
	buf_info.pQueueFamilyIndices = NULL;
	buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	buf_info.flags = 0;
	vulkan::Error::Window(vkCreateBuffer(in_Device->device, &buf_info, NULL, &uniform_data.buf),"Bufferの作成に失敗");

	VkMemoryRequirements mem_reqs;
	vkGetBufferMemoryRequirements(in_Device->device, uniform_data.buf, &mem_reqs);

	VkMemoryAllocateInfo alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.pNext = NULL;
	alloc_info.memoryTypeIndex = 0;

	alloc_info.allocationSize = mem_reqs.size;
	
	vulkan::Error::Window(vulkan::data::Checker::memory_type_from_properties( mem_reqs.memoryTypeBits,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&alloc_info.memoryTypeIndex), "No mappable, coherent memory");

	vulkan::Error::Window(vkAllocateMemory(in_Device->device, &alloc_info, NULL, &uniform_data.mem),"アロケートメモリー");

	uint8_t *pData;
	vulkan::Error::Window(vkMapMemory(in_Device->device, uniform_data.mem, 0, mem_reqs.size, 0, (void **)&pData),"マップメモリーの作成に失敗");
	size = mem_reqs.size;
	memcpy(pData, &Model, sizeof(Model));

	vkUnmapMemory(in_Device->device, uniform_data.mem);

	vulkan::Error::Window(vkBindBufferMemory(in_Device->device, uniform_data.buf, uniform_data.mem, 0),"バインドバッファメモリーの作成に失敗");

	uniform_data.buffer_info.buffer = uniform_data.buf;
	uniform_data.buffer_info.offset = 0;
	uniform_data.buffer_info.range = sizeof(Model);
}
void vulkan::data::Uniform_Buffer::Updata(Device* in_Device)
{	
	MVP = Clip * Projection * View * Model;
	
	uint8_t *pData;
	vulkan::Error::Window(vkMapMemory(in_Device->device, uniform_data.mem, 0, this->size, 0, (void **)&pData), "マップメモリーの作成に失敗");

	memcpy(pData, &MVP, sizeof(MVP));

	vkUnmapMemory(in_Device->device, uniform_data.mem);

	uniform_data.buffer_info.buffer = uniform_data.buf;
	uniform_data.buffer_info.offset = 0;
	uniform_data.buffer_info.range = sizeof(MVP);
}

void vulkan::data::Uniform_Buffer::Uninit(Device* in_Device)
{
	vkDestroyBuffer(in_Device->device, uniform_data.buf, NULL);
	vkFreeMemory(in_Device->device, uniform_data.mem, NULL);
}
