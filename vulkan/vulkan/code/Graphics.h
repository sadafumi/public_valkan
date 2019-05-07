//========================================================================
//	maked by sadafumi 
//	2019/2/7
//========================================================================
#pragma once
#include <Windows.h>
#include "Window_Data.h"
#include "vulkan_api.h"
#include "Object.h"
#include "Model.h"
#include <stdio.h>

class Graphics
{
public:
	Graphics();
	~Graphics();
	void Init(Window_Data data);
	void Uninit();
	void Updata();
	void Draw();
private:
	Object obj_1;
	Object obj_2;
	Model model_1;

	uint32_t current_buffer;
	vulkan::data::Global_Layer_Properties global_layer_properties;
	vulkan::data::Instance Instance;
	vulkan::data::Debug_Log Debug;
	vulkan::data::PhysicalDevice PhyDevice;
	vulkan::data::Device Device;
	vulkan::data::Command_Pool cmd_pool;
	vulkan::data::Command_Buffer cmd_buff;
	vulkan::data::Depth_Buffer deps_buff;
	vulkan::data::Surface surface;
	vulkan::data::Swap_Chain swapchain;
	vulkan::data::Image	image;
	vulkan::data::ImageView imageview;
	vulkan::data::Graphic_Queue graphic_queue;
	vulkan::data::Render_Pass renderpass;
	vulkan::data::Frame_Buffer framebuffer;

	vulkan::data::Pipeline_cache pipelinecache;

	vulkan::data::Fence fence;
	vulkan::data::Semaphore semaphore;
};


