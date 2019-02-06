#include "vulkan.h"


void vulkan::data::Uniform_Buffer::Init(Device* in_Device, PhysicalDevice* PhyDevice, Utility::Int_Vec2 win)
{
	Projection = Utility::mtx4x4::Perspective(
		Utility::math::radians((120) / 2), 
		static_cast<float>(win.x) / static_cast<float>(win.y),
		0.1f, 
		100.0f);
	Projection = Utility::mtx4x4::Perspective_Direct(Utility::math::radians((120) / 2),
		static_cast<float>(win.x) / static_cast<float>(win.y),
		0.1f,
		100.0f);


	View = Utility::mtx4x4::LookAt(
		Utility::Vec3(0, 0, 1),   // Camera is at (-5,3,-10), in World Space
		Utility::Vec3(0, 0, 0),  // and looks at the origin
		Utility::Vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
	);
	
	Model.Identity();

	Utility::mtx4x4 Pos;
	Utility::mtx4x4 Sca;
	Utility::mtx4x4 Rota;
	Utility::mtx4x4 RotaX;
	Utility::mtx4x4 RotaY;
	Sca = Utility::mtx4x4::Scale(0.5f,0.5f, 0.5f);
	Pos = Utility::mtx4x4::Transform(0,0,0);
	RotaX = Utility::mtx4x4::RotationX(0.5f);
	RotaY = Utility::mtx4x4::RotationY(0.5f);
	Rota = RotaX * RotaY;
	Model =  Sca * Pos * RotaX;

	Model = Model * View * Projection;

	MVP = Model;

	VkBufferCreateInfo buf_info = {};
	buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buf_info.pNext = NULL;
	buf_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	buf_info.size = sizeof(MVP);
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
	
	vulkan::Error::Window(vulkan::data::Checker::memory_type_from_properties(PhyDevice, mem_reqs.memoryTypeBits,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&alloc_info.memoryTypeIndex), "No mappable, coherent memory");

	vulkan::Error::Window(vkAllocateMemory(in_Device->device, &alloc_info, NULL, &uniform_data.mem),"アロケートメモリー");

	uint8_t *pData;
	vulkan::Error::Window(vkMapMemory(in_Device->device, uniform_data.mem, 0, mem_reqs.size, 0, (void **)&pData),"マップメモリーの作成に失敗");
	size = mem_reqs.size;
	memcpy(pData, &MVP, sizeof(MVP));

	vkUnmapMemory(in_Device->device, uniform_data.mem);

	vulkan::Error::Window(vkBindBufferMemory(in_Device->device, uniform_data.buf, uniform_data.mem, 0),"バインドバッファメモリーの作成に失敗");

	uniform_data.buffer_info.buffer = uniform_data.buf;
	uniform_data.buffer_info.offset = 0;
	uniform_data.buffer_info.range = sizeof(MVP);
}
void vulkan::data::Uniform_Buffer::Updata(Device* in_Device)
{
	static float buff = 0;
	Model.Identity();
	buff += 0.01f;
	Utility::mtx4x4 Pos;
	Utility::mtx4x4 Sca;
	Utility::mtx4x4 Rota;
	Utility::mtx4x4 RotaX;
	Utility::mtx4x4 RotaY;
	Utility::mtx4x4 RotaZ;
	Sca = Utility::mtx4x4::Scale(0.5f, 0.5f, 0.5f);
	Pos = Utility::mtx4x4::Transform(0, 0, 0);
	RotaX = Utility::mtx4x4::RotationX(buff);
	RotaY = Utility::mtx4x4::RotationY(buff);
	RotaZ = Utility::mtx4x4::RotationY(buff);
	Rota = RotaX * RotaY * RotaZ;
	Model = Sca * Pos * Rota;

	Model = Model * View * Projection;

	MVP = Model;
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
}
