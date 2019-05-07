#include "Model.h"
#include "Utility.h"

void Model::Init(std::string texFile, vulkan::data::Device* in_dev, vulkan::data::Command_Buffer* in_comm, vulkan::data::Render_Pass* pass, vulkan::data::Pipeline_cache* pipelinecache)
{
	texFile = texFile;
	in_dev = in_dev;
	in_comm = in_comm;
	pass = pass;
	this->Device = in_dev;
	this->cmd_buff = in_comm;
	pipelinecache = pipelinecache;
	bool tex_flag = true;
	tex_flag = tex_flag;

	in_data.Load_File(texFile);

	const char* vert_2D_ShaderPath = "shader/3D_Model.vert.spv";
	const char* frag_2D_ShaderPath = "shader/3D_Model.frag.spv";

	
	this->uniform_buff.Init(this->Device);

	this->Shaders.Create(&Shaders, vert_2D_ShaderPath, frag_2D_ShaderPath, Device);

	Mesh_size = in_data.meshs.size();
	this->texs.resize(Mesh_size);
	this->vertexs.resize(Mesh_size);
	this->desc_pools.resize(Mesh_size);
	this->pipelines.resize(Mesh_size);
	
	for (int i = 0; i < Mesh_size; i++)
	{
		vulkan::Resources::Buffer::Create_Model(&vertexs[i], in_data.meshs[i].vertexs, in_data.meshs[i].vertex_size, &in_data, Device);
		std::string buff;
		Utility::Path::EditPath(&buff, &texFile, &in_data.meshs[i].tex_file.name);

		this->texs[i].Create(&texs[i], Device, buff.data());

		this->desc_pools[i].Init(this->Device, tex_flag);

		this->desc_pools[i].Create_Layout(this->Device, tex_flag);
		this->desc_pools[i].Set(this->Device, &uniform_buff, tex_flag, &texs[i]);

		pipelines[i].Create_Layout(this->Device, &desc_pools[i]);

		this->pipelines[i].Init(this->Device, &cmd_buff->viewport, &cmd_buff->scissor, &this->vertexs[i], &Shaders, pass, pipelinecache, tex_flag);
	}

	in_model = glm::mat4(1.0f);
}

void Model::Uninit()
{
	for (int i = 0; i < Mesh_size; i++)
	{
		this->vertexs[i].Destroy(Device);
	}
	for (int i = 0; i < Mesh_size; i++)
	{
		pipelines[i].Uninit(Device);
	}
	for (int i = 0; i < Mesh_size; i++)
	{
		this->texs[i].Destroy(Device);
	}
	for (int i = 0; i < Mesh_size; i++)
	{
		desc_pools[i].Uninit(Device);
	}

	this->Shaders.Destroy(Device);

	uniform_buff.Uninit(Device);
}

void Model::Updata()
{
	this->uniform_buff.Model = in_model;
	this->uniform_buff.Updata(this->Device);
	for (int i = 0; i < Mesh_size; i++)
	{
		this->desc_pools[i].Updata(this->Device, &uniform_buff, false, NULL);
	}
}

void Model::Draw()
{
	const VkDeviceSize offsets[1] = { 0 };
	for (unsigned int i = 0; i < this->in_data.meshs.size(); i++)
	{
		vkCmdBindPipeline(this->cmd_buff->cmd_buff, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines[i].pipeline);
		vkCmdBindDescriptorSets(this->cmd_buff->cmd_buff, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines[i].pipeline_layout, 0, 1, desc_pools[i].desc_set.data(), 0, NULL);
		vkCmdBindVertexBuffers(this->cmd_buff->cmd_buff, 0, 1, &this->vertexs[i].buffer, offsets);

		cmd_buff->Draw(this->vertexs[i].vertex_size, 1, 0, 0);
	}
}

void Model::Set_Matrixs(glm::mat4 in_mtx)
{
	this->in_model = in_mtx;
}

void Model::Set_Layout(vulkan::data::Graphic_Queue* in_Q, vulkan::data::Command_Buffer* in_cmd)
{
	for (unsigned int i = 0; i < this->texs.size(); i++)
	{
		this->texs[i].Set_Image_Layout(in_Q, in_cmd);
	}
}
