#pragma once
#include "vulkan.h"

class Test_Draw_2D_Texture
{
public:
	void Init(Utility::Int_Vec2, HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Updata();
	void Draw();
private:
	uint32_t current_buffer;
	vulkan::data::Global_Layer_Properties global_layer_properties;
	vulkan::data::Instance Instance;
	vulkan::data::Debug_Log Debug;
	vulkan::data::PhysicalDevice PhyDevice;
	vulkan::data::Device Device;
	vulkan::data::Command_Pool cmd_pool;
	vulkan::data::Command_Buffer cmd_buff;
	vulkan::data::Uniform_Buffer uniform_buff;
	vulkan::data::Surface surface;
	vulkan::data::Swap_Chain swapchain;
	vulkan::data::Image	image;
	vulkan::data::ImageView imageview;
	vulkan::data::Graphic_Queue graphic_queue;
	vulkan::data::Render_Pass renderpass;
	vulkan::data::Frame_Buffer framebuffer;
	vulkan::data::ViewPort viewport;
	vulkan::data::Scissor scissor;
	vulkan::data::Descriptor_Pool desc_pool;
	vulkan::data::Pipeline_cache pipelinecache;
	vulkan::data::Pipeline pipeline;
	vulkan::Resources::Texture tex;
	vulkan::Resources::Buffer vertex;
	vulkan::Resources::Shader Shaders;
	vulkan::data::Fence fence;
	vulkan::data::Semaphore semaphore;
	Utility::Int_Vec2 window_size;
};

