#pragma once

#include <string>
#include "vulkan_api.h"

class Object
{
public:
	Object();
	~Object();
	void Init(std::string texFile, vulkan::data::Device* in_dev, vulkan::data::Command_Buffer* in_comm, vulkan::data::Render_Pass* pass, vulkan::data::Pipeline_cache* pipelinecache );
	void Uninit();
	void Updata();
	void Draw();
	void Set_Matrixs(glm::mat4 in_mtx);
	vulkan::Resources::Texture tex;
private:
	glm::mat4 in_model;
	std::vector<vulkan::Resources::Vertex> verticesData;

	vulkan::data::Uniform_Buffer uniform_buff;
	vulkan::data::Descriptor_Pool desc_pool;
	vulkan::data::Pipeline pipeline;

	vulkan::Resources::Buffer vertex;
	
	vulkan::Resources::Shader Shaders;

	vulkan::data::Device* Device;
	vulkan::data::Command_Buffer* cmd_buff;
};


