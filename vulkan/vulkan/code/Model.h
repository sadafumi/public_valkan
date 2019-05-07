#pragma once

#include <string>
#include "vulkan_api.h"
#include "mfv.h"

class Model
{
public:
	void Init(std::string texFile, vulkan::data::Device* in_dev, vulkan::data::Command_Buffer* in_comm, vulkan::data::Render_Pass* pass, vulkan::data::Pipeline_cache* pipelinecache);
	void Uninit();
	void Updata();
	void Draw();
	void Set_Matrixs(glm::mat4 in_mtx);
	void Set_Layout(vulkan::data::Graphic_Queue* in_Q, vulkan::data::Command_Buffer* in_cmd);
private:
	
	glm::mat4 in_model;
	int Mesh_size = 0;
	mfv::model in_data;

	vulkan::data::Uniform_Buffer uniform_buff;

	vulkan::Resources::Shader Shaders;

	std::vector<vulkan::data::Descriptor_Pool> desc_pools;
	std::vector<vulkan::data::Pipeline> pipelines;

	std::vector<vulkan::Resources::Buffer> vertexs;
	
	std::vector<vulkan::Resources::Texture> texs;
	
	vulkan::data::Device* Device;
	vulkan::data::Command_Buffer* cmd_buff;
};

