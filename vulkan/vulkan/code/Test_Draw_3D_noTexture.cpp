#include "Test_Draw_3D_noTexture.h"


void Test_Draw_3D_noTexture::Init(Utility::Int_Vec2 in_win, HWND hWnd, HINSTANCE hInstance)
{
	window_size = in_win;

	//verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.9f,-0.9f, 0.0f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 0.0f)));
	//verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.9f,-0.9f, 0.0f, 1.0f), Utility::Vec4(0.0f, 0.0f, 1.0f, 0.0f)));
	//verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.9f, 0.9f, 0.0f, 1.0f), Utility::Vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	//verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.9f,-0.9f, 0.0f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 0.0f)));
	//verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.9f, 0.9f, 0.0f, 1.0f), Utility::Vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	//verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.9f, 0.9f, 0.0f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 1.0f)));
	//verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.9f,-0.9f, 0.0f, 1.0f), Utility::Vec4(1.0f, 1.0f, 1.0f, 1.0f)));

	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 0.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 0.0f, 0.0f)));  // lft-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 0.0f, 0.0f)));   // lft-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 0.0f, 0.0f)));  // lft-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 0.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 0.0f, 0.0f)));   // lft-btm-front
	// front face													0.5f  0.5f	0.5f							
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 0.0f)));   // rgt-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 0.0f)));    // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 0.0f)));   // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 0.0f, 0.0f)));   // lft-btm-front
	// top face														0.5f  0.5f	0.5f						0	
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 0.0f, 1.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(0.0f, 0.0f, 1.0f, 0.0f)));  // rgt-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 0.0f, 1.0f, 0.0f)));   // rgt-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 0.0f, 1.0f, 0.0f)));  // lft-top-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(0.0f, 0.0f, 1.0f, 0.0f)));   // lft-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(0.0f, 0.0f, 1.0f, 0.0f)));    // rgt-top-back
	// bottom face													0.5f  0.5f	0.5f						0	
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 1.0f, 0.0f)));  // lft-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 1.0f, 0.0f)));  // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 1.0f, 0.0f)));   // lft-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 1.0f, 0.0f)));  // lft-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 1.0f, 0.0f)));   // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 0.0f, 1.0f, 0.0f)));    // rgt-btm-back
	// right face														  0.5f	0.5f						0	
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 1.0f, 0.0f)));   // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 1.0f, 0.0f)));   // rgt-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 1.0f, 0.0f)));   // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 1.0f, 0.0f)));   // rgt-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 1.0f, 0.0f)));   // rgt-btm-front
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,-0.5f,-0.5f, 1.0f), Utility::Vec4(0.0f, 1.0f, 1.0f, 0.0f)));  // rgt-top-front
	// back face														  0.5f	0.5f						0
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 1.0f, 0.0f, 0.0f)));   // lft-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 1.0f, 0.0f, 0.0f)));    // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 1.0f, 0.0f, 0.0f)));  // lft-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4(-0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 1.0f, 0.0f, 0.0f)));  // lft-top-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f, 0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 1.0f, 0.0f, 0.0f)));    // rgt-btm-back
	verticesData.push_back(vulkan::Resources::Vertex(Utility::Vec4( 0.5f,-0.5f, 0.5f, 1.0f), Utility::Vec4(1.0f, 1.0f, 0.0f, 0.0f)));  // rgt-top-back

	bool tex_flag = false;
	bool depth_flag = false;

	const char *vert_2D_ShaderPath = "shader\\3D_no_Texture.vert.spv";
	const char *frag_2D_ShaderPath = "shader\\3D_no_Texture.frag.spv";

	int size = 0;
	size = sizeof(vulkan::Resources::Vertex);
	vulkan::Error::Window(this->global_layer_properties.Init(), "グローバルレイヤープロパティー");
	this->Instance.Init();
	this->Debug.Init(&this->Instance);
	this->PhyDevice.Init(&Instance, &global_layer_properties);
	this->Device.Init(&PhyDevice);
	this->cmd_pool.Init(&Device);
	this->fence.Init(&Device);
	this->graphic_queue.Init(&Device);
	this->surface.Init(hWnd, hInstance, &Instance);
	this->swapchain.Init(window_size, &PhyDevice, &Device, &surface);
	this->image.Init(&Device, &swapchain);
	this->imageview.Init(&Device, &image);
	this->uniform_buff.Init(&Device, &PhyDevice, window_size);
	this->renderpass.Init(&Device, &swapchain, NULL, depth_flag);
	if (!tex_flag && !depth_flag)
	{
		this->Shaders.Create(&Shaders, vert_2D_ShaderPath, frag_2D_ShaderPath, &Device);
	}
	this->framebuffer.Init(window_size, &Device, &imageview, &renderpass, NULL, depth_flag);
	this->cmd_buff.Init(&Device, &cmd_pool, this->framebuffer.Frame_Buffer.size());
	semaphore.Create(&Device);
	this->desc_pool.Init(&Device, tex_flag);
	//this->vertex.Create(&vertex, g_vb_texture_Data, sizeof(vulkan::Resources::Vertex), tex_flag, &Device, &PhyDevice);
	this->vertex.Create(&vertex, verticesData, sizeof(vulkan::Resources::Vertex), tex_flag, &Device, &PhyDevice);
	viewport.Init(window_size);
	scissor.Init(window_size);
	this->desc_pool.Create_Layout(&Device, tex_flag);
	this->desc_pool.Set(&Device, &uniform_buff, tex_flag, NULL);
	this->pipelinecache.Init(&Device);
	pipeline.Create_Layout(&Device, &desc_pool);
	this->pipeline.Init(&Device, &viewport, &scissor, &this->vertex, &Shaders, &renderpass, &pipelinecache, tex_flag);
	

	cmd_buff.Begin(&framebuffer, current_buffer);
	image.Image_Layoutting(&cmd_buff);
	cmd_buff.End();

	cmd_buff.submitCommand(&graphic_queue, NULL, &semaphore);
	cmd_buff.Wait(&graphic_queue);

	vulkan::Error::Window(vkQueueWaitIdle(graphic_queue.graphics_queue), "Deviceを待ってます");

	vulkan::Error::Window(vkAcquireNextImageKHR(this->Device.device, swapchain.swapChain, UINT64_MAX, VK_NULL_HANDLE, fence.Fence, &current_buffer), "次のimageを取得できませんでした");
	vulkan::Error::Window(vkWaitForFences(this->Device.device, 1, &fence.Fence, VK_FALSE, UINT64_MAX), "fenceを待つことができませんでした");
	vulkan::Error::Window(vkResetFences(this->Device.device, 1, &fence.Fence), "fenceのResetに失敗");
}

void Test_Draw_3D_noTexture::Uninit()
{
	this->vertex.Destroy(&Device);
	this->fence.Uninit(&Device);
	pipeline.Uninit(&Device);
	pipelinecache.Uninit(&Device);
	desc_pool.Uninit(&Device);
	framebuffer.Uninit(&Device);
	renderpass.Uninit(&Device);
	uniform_buff.Uninit(&Device);
	swapchain.Uninit(&Device);
	cmd_buff.Uninit(&Device, &cmd_pool);
	cmd_pool.Uninit(&Device);
	Device.Uninit();
	PhyDevice.Uninit();
	Debug.Uninit(&Instance);
	Instance.Uninit();
}

void Test_Draw_3D_noTexture::Updata()
{
	this->uniform_buff.Updata(&Device);
	this->desc_pool.Updata(&Device, &uniform_buff, false, NULL);
}

void Test_Draw_3D_noTexture::Draw()
{
	const VkDeviceSize offsets[1] = { 0 };

	cmd_buff.Begin(&framebuffer, current_buffer);
	cmd_buff.Wait(&graphic_queue);
	image.barrierResource(&cmd_buff, current_buffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		VK_ACCESS_MEMORY_READ_BIT, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

	cmd_buff.Begin_Render_pass(window_size, &framebuffer, current_buffer, &renderpass);

	vkCmdBindPipeline(cmd_buff.cmd_buff, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);

	viewport.Set(&cmd_buff);
	scissor.Set(&cmd_buff);
	
	vkCmdBindDescriptorSets(cmd_buff.cmd_buff, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline_layout, 0, 1, desc_pool.desc_set.data(), 0, NULL);
	vkCmdBindVertexBuffers(cmd_buff.cmd_buff, 0, 1, &vertex.buffer, offsets);

	vkCmdDraw(cmd_buff.cmd_buff, verticesData.size(), 1, 0, 0);
	vkCmdEndRenderPass(cmd_buff.cmd_buff);
	//image.barrierResource(&cmd_buff, current_buffer,
	//	VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
	//	VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, VK_ACCESS_MEMORY_READ_BIT,
	//	VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
	cmd_buff.End();

	cmd_buff.submitCommand(&graphic_queue, &fence, &semaphore);

	switch (vkWaitForFences(Device.device, 1, &fence.Fence, VK_TRUE, 100000000))
	{
	case VK_SUCCESS:
	{
		VkPresentInfoKHR present;
		present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present.pNext = NULL;
		present.swapchainCount = 1;
		present.pSwapchains = &swapchain.swapChain;
		present.pImageIndices = &current_buffer;
		present.pWaitSemaphores = NULL;
		present.waitSemaphoreCount = 0;
		present.pResults = NULL;

		vulkan::Error::Window(vkQueuePresentKHR(graphic_queue.present_queue, &present), "QueuePresentエラー");
		break;
	}
	case VK_TIMEOUT: printf("Command execution timed out."); break;
	default: OutputDebugString("waitForFence returns unknown value.\n");
	}

	vulkan::Error::Window(vkResetFences(this->Device.device, 1, &fence.Fence), "fenceのResetに失敗");
	vulkan::Error::Window(vkAcquireNextImageKHR(this->Device.device, swapchain.swapChain, UINT64_MAX, VK_NULL_HANDLE, fence.Fence, &current_buffer), "次のimageを取得できませんでした");
	vulkan::Error::Window(vkWaitForFences(this->Device.device, 1, &fence.Fence, VK_FALSE, UINT64_MAX), "fenceを待つことができませんでした");
	vulkan::Error::Window(vkResetFences(this->Device.device, 1, &fence.Fence), "fenceのResetに失敗");
}
