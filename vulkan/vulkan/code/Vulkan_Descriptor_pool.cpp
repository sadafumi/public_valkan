#include "vulkan_api.h"


void vulkan::data::Descriptor_Pool::Init(Device* in_Device,bool tex_flag)
{
	VkDescriptorPoolSize type_count[2];
	type_count[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	type_count[0].descriptorCount = 1;
	if (tex_flag) 
	{
		type_count[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		type_count[1].descriptorCount = 1;
	}

	VkDescriptorPoolCreateInfo descriptor_pool = {};
	descriptor_pool.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	descriptor_pool.pNext = NULL;
	descriptor_pool.maxSets = 1;
	descriptor_pool.poolSizeCount = tex_flag ? 2 : 1;
	descriptor_pool.pPoolSizes = type_count;

	vulkan::Error::Window(vkCreateDescriptorPool(in_Device->device, &descriptor_pool, NULL, &desc_pool),"ディスクリポータの作成に失敗");
}

void vulkan::data::Descriptor_Pool::Create_Layout(Device * in_Device, bool tex_flag, VkDescriptorSetLayoutCreateFlags descSetLayoutCreateFlags)
{
	VkDescriptorSetLayoutBinding layout_bindings[2];
	layout_bindings[0].binding = 0;
	layout_bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	layout_bindings[0].descriptorCount = 1;
	layout_bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	layout_bindings[0].pImmutableSamplers = NULL;

	if (tex_flag)
	{
		layout_bindings[1].binding = 1;
		layout_bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		layout_bindings[1].descriptorCount = 1;
		layout_bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		layout_bindings[1].pImmutableSamplers = NULL;
	}

	VkDescriptorSetLayoutCreateInfo descriptor_layout = {};
	descriptor_layout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptor_layout.pNext = NULL;
	descriptor_layout.flags = descSetLayoutCreateFlags;
	descriptor_layout.bindingCount = tex_flag ? 2 : 1;
	descriptor_layout.pBindings = layout_bindings;

	this->desc_layout.resize(NUM_DESCRIPTOR_SETS);
	vulkan::Error::Window(vkCreateDescriptorSetLayout(in_Device->device, &descriptor_layout, NULL, this->desc_layout.data()), "CreateDescriptorLayoutの設定に失敗");

}

void vulkan::data::Descriptor_Pool::Set(Device* in_Device, Uniform_Buffer* Uniform, bool tex_flag, Resources::Texture* in_tex)
{
	VkDescriptorSetAllocateInfo alloc_info[1];
	alloc_info[0].sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	alloc_info[0].pNext = NULL;
	alloc_info[0].descriptorPool = desc_pool; 
	alloc_info[0].descriptorSetCount = NUM_DESCRIPTOR_SETS;
	alloc_info[0].pSetLayouts = desc_layout.data();

	desc_set.resize(NUM_DESCRIPTOR_SETS);
	vulkan::Error::Window(vkAllocateDescriptorSets(in_Device->device, alloc_info, desc_set.data()),"ディスクリポータの設定に失敗");

	this->Updata(in_Device, Uniform, tex_flag, in_tex);
}

void vulkan::data::Descriptor_Pool::Updata(Device* in_Device, Uniform_Buffer* Uniform, bool tex_flag, Resources::Texture* in_tex)
{
	VkWriteDescriptorSet writes[2];

	writes[0] = {};
	writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writes[0].pNext = NULL;
	writes[0].dstSet = desc_set[0];
	writes[0].descriptorCount = 1;
	writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	writes[0].pBufferInfo = &Uniform->uniform_data.buffer_info;
	writes[0].dstArrayElement = 0;
	writes[0].dstBinding = 0;

	if (tex_flag)
	{
		writes[1] = {};
		writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writes[1].dstSet = desc_set[0];
		writes[1].dstBinding = 1;
		writes[1].descriptorCount = 1;
		writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		writes[1].pImageInfo = &in_tex->texture_data.image_info;
		writes[1].dstArrayElement = 0;
	}

	vkUpdateDescriptorSets(in_Device->device, tex_flag ? 2 : 1, writes, 0, NULL);

}

void vulkan::data::Descriptor_Pool::Uninit(Device* in_Device)
{
	for (int i = 0; i < NUM_DESCRIPTOR_SETS; i++)
	{
		vkDestroyDescriptorSetLayout(in_Device->device, this->desc_layout[i], NULL);
	}
	vkDestroyDescriptorPool(in_Device->device, desc_pool, NULL);
}