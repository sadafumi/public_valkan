#include "Object.h"

Object::Object()
{
}


Object::~Object()
{
}

void Object::Init(std::string texFile, vulkan::data::Device* in_dev, vulkan::data::Command_Buffer* in_comm, vulkan::data::Render_Pass* pass, vulkan::data::Pipeline_cache* pipelinecache)
{
	this->Device = in_dev;
	this->cmd_buff = in_comm;
	
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f,  0.5f, 1.0f), Utility::Vec2(0.0f, 0.0f)));   // lft-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,  0.5f,  0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));  // lft-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,  0.5f, -0.5f, 1.0f), Utility::Vec2(1.0f, 1.0f)));   // lft-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,  0.5f,  0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));  // lft-btm-back
	// front face													0.5f  0.5f	0.5f					 	 0	   0
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,  0.5f, -0.5f, 1.0f), Utility::Vec2(1.0f, 1.0f)));    // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));   // rgt-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,  0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));   // lft-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,  0.5f, -0.5f, 1.0f), Utility::Vec2(1.0f, 1.0f)));   // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 0.0f)));  // lft-top-front
	// top face														0.5f 0.5f	0.5f					 	 0	   0
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(1.0f, 1.0f)));   // rgt-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, -0.5f,  0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));  // rgt-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, -0.5f,  0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));    // rgt-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f,  0.5f, 1.0f), Utility::Vec2(0.0f, 0.0f)));   // lft-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));  // lft-top-front
	// bottom face													0.5f 0.5f	0.5f					 	 0	   0
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f,  0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));   // lft-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f,  0.5f, 1.0f), Utility::Vec2(1.0f, 1.0f)));  // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 0.0f)));  // lft-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f,  0.5f, 1.0f), Utility::Vec2(1.0f, 1.0f)));    // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f, -0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));   // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 0.0f)));  // lft-btm-fron
	// right face														 0.5f	0.5f					 	 0	   0
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(0.5f,  0.5f,  0.5f, 1.0f), Utility::Vec2(1.0f, 1.0f)));   // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(0.5f, -0.5f,  0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));   // rgt-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(0.5f,  0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));   // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(0.5f, -0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 0.0f)));  // rgt-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(0.5f,  0.5f, -0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));   // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(0.5f, -0.5f,  0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));   // rgt-top-back
	// back face														 0.5f	0.5f					 	 0	   0
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));  // lft-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,  0.5f, 0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));    // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,  0.5f, 0.5f, 1.0f), Utility::Vec2(1.0f, 1.0f)));   // lft-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, -0.5f, 0.5f, 1.0f), Utility::Vec2(0.0f, 0.0f)));  // rgt-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,  0.5f, 0.5f, 1.0f), Utility::Vec2(0.0f, 1.0f)));    // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Utility::Vec2(1.0f, 0.0f)));  // lft-top-back
	

	bool tex_flag = true;

	const char* vert_2D_ShaderPath = "shader/3D_Texture.vert.spv";
	const char* frag_2D_ShaderPath = "shader/3D_Texture.frag.spv";

	this->uniform_buff.Init(this->Device);

	this->Shaders.Create(&Shaders, vert_2D_ShaderPath, frag_2D_ShaderPath, Device);

	this->tex.Create(&tex, Device, texFile.data());

	this->desc_pool.Init(this->Device, tex_flag);

	this->desc_pool.Create_Layout(this->Device, tex_flag);
	this->desc_pool.Set(this->Device, &uniform_buff, tex_flag, &tex);

	this->vertex.Create(&vertex, verticesData, sizeof(vulkan::Resources::Vertex), tex_flag, Device);

	pipeline.Create_Layout(this->Device, &desc_pool);
	
	this->pipeline.Init(this->Device, &cmd_buff->viewport, &cmd_buff->scissor, &this->vertex, &Shaders, pass, pipelinecache, tex_flag);

	in_model = glm::mat4(1.0f);
}

void Object::Uninit()
{
	this->vertex.Destroy(Device);

	pipeline.Uninit(Device);

	tex.Destroy(Device);

	desc_pool.Uninit(Device);

	this->Shaders.Destroy(Device);

	uniform_buff.Uninit(Device);
}

void Object::Updata()
{
	this->uniform_buff.Model = in_model;
	this->uniform_buff.Updata(this->Device);
	this->desc_pool.Updata(this->Device, &uniform_buff, false, NULL);
}

void Object::Draw()
{
	const VkDeviceSize offsets[1] = { 0 };

	vkCmdBindPipeline(this->cmd_buff->cmd_buff, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
	vkCmdBindDescriptorSets(this->cmd_buff->cmd_buff, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline_layout, 0, 1, desc_pool.desc_set.data(), 0, NULL);
	vkCmdBindVertexBuffers(this->cmd_buff->cmd_buff, 0, 1, &vertex.buffer, offsets);

	cmd_buff->Draw(verticesData.size(), 1, 0, 0);
}

void Object::Set_Matrixs(glm::mat4 in_mtx)
{
	this->in_model = in_mtx;
}
