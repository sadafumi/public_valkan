#include "Graphics.h"
#include "Utility.h"

#define FENCE_TIMEOUT 100000000

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::Init(Window_Data data)
{
	
	bool depth_flag = true;

	vulkan::Error::Window(this->global_layer_properties.Init(), "グローバルレイヤープロパティー");
	this->Instance.Init();
	this->Debug.Init(&this->Instance);
	this->PhyDevice.Init(&Instance, &global_layer_properties);
	vulkan::data::Checker::Set_PhyDevicce(&PhyDevice);
	this->Device.Init(&PhyDevice);
	this->Device.Set_Window_Size(data.Get_Windows_Size());
	this->cmd_pool.Init(&Device);
	this->fence.Init(&Device);
	this->graphic_queue.Init(&Device);
	this->surface.Init(data, &Instance);
	this->swapchain.Init( &PhyDevice, &Device, &surface);

	this->image.Init(&Device, &swapchain);
	this->imageview.Init(&Device, &image);
	this->deps_buff.Init(&Device, &PhyDevice);

	this->renderpass.Init(&Device, &swapchain, &deps_buff, depth_flag);

	this->framebuffer.Init( &Device, &imageview, &renderpass, &deps_buff, depth_flag);
	this->cmd_buff.Init(&Device, &cmd_pool, this->framebuffer.Frame_Buffer.size());

	this->pipelinecache.Init(&Device);

	cmd_buff.Begin(&framebuffer, current_buffer);
	image.Image_Layoutting(&cmd_buff);
	cmd_buff.End();

	cmd_buff.submitCommand(&graphic_queue, NULL, &semaphore);
	cmd_buff.Wait(&graphic_queue);

	this->obj_1.Init("Resources/texture/test.mtf", &Device, &cmd_buff, &renderpass, &pipelinecache);
	this->obj_2.Init("Resources/texture/test.mtf", &Device, &cmd_buff, &renderpass, &pipelinecache);
	model_1.Init("Resources/model/Hibiki/Hibiki.mtv", &Device, &cmd_buff, &renderpass, &pipelinecache);

	cmd_buff.Begin(&framebuffer, current_buffer);
	//--------------------------------------------------------------------------------------------------
	this->obj_1.tex.Set_Image_Layout(&graphic_queue, &cmd_buff);
	this->obj_2.tex.Set_Image_Layout(&graphic_queue, &cmd_buff);
	model_1.Set_Layout(&graphic_queue, &cmd_buff);
	//--------------------------------------------------------------------------------------------------

	cmd_buff.End();

	semaphore.Create(&Device);

	cmd_buff.submitCommand(&graphic_queue, NULL, &semaphore);
	cmd_buff.Wait(&graphic_queue);

	vulkan::Error::Window(vkQueueWaitIdle(graphic_queue.graphics_queue), "Deviceを待ってます");

	vulkan::Error::Window(vkAcquireNextImageKHR(this->Device.device, swapchain.swapChain, UINT64_MAX, VK_NULL_HANDLE, fence.Fence, &current_buffer), "次のimageを取得できませんでした");
	vulkan::Error::Window(vkWaitForFences(this->Device.device, 1, &fence.Fence, VK_FALSE, UINT64_MAX), "fenceを待つことができませんでした");
	vulkan::Error::Window(vkResetFences(this->Device.device, 1, &fence.Fence), "fenceのResetに失敗");
}

void Graphics::Uninit()
{
	this->obj_1.Uninit();
	this->obj_2.Uninit();
	model_1.Uninit();

	semaphore.Destroy(&Device);
	this->fence.Uninit(&Device);

	pipelinecache.Uninit(&Device);

	framebuffer.Uninit(&Device);
	renderpass.Uninit(&Device);

	deps_buff.Uninit(&Device);
	imageview.Destroy(&Device);
	swapchain.Uninit(&Device);
	graphic_queue.Uninit(&Device);
	cmd_buff.Uninit(&Device, &cmd_pool);
	cmd_pool.Uninit(&Device);
	Device.Uninit();
	PhyDevice.Uninit();
	Debug.Uninit(&Instance);
	Instance.Uninit();
}

void Graphics::Updata()
{
	static float buff = 0;

	buff += 0.01f;
	glm::mat4 Rot(1.0f);
	glm::mat4 Pos(1.0f);
	glm::mat4 Sca(1.0f);

	glm::mat4 Rot1(1.0f);
	glm::mat4 Pos1(1.0f);
	glm::mat4 Sca1(1.0f);

	glm::mat4 Rot2(1.0f);
	glm::mat4 Pos2(1.0f);
	glm::mat4 Sca2(1.0f);


	Rot = glm::rotate(Rot, buff, glm::vec3(1, 1, 1));
	Pos = glm::translate(Pos, glm::vec3(2, 0, 0));
	Sca = glm::scale(Sca, glm::vec3(1.5f, 1.5f, 1.5f));

	this->obj_1.Set_Matrixs(Pos * Rot * Sca);
	this->obj_1.Updata();

	Rot1 = glm::rotate(Rot1, buff, glm::vec3(-1, -1, -1));
	Pos1 = glm::translate(Pos1, glm::vec3(-2, 0, 0));
	Sca1 = glm::scale(Sca1, glm::vec3(1.5f, 1.5f, 1.5f));

	this->obj_2.Set_Matrixs(Pos1 * Rot1 * Sca1);
	this->obj_2.Updata();

	Rot2 = glm::rotate(Rot2, buff, glm::vec3(0, 1, 0));
	Pos2 = glm::translate(Pos2, glm::vec3(0, -1.5, 0));
	Sca2 = glm::scale(Sca2, glm::vec3(0.15f, 0.15f, 0.15f));


	model_1.Set_Matrixs(Pos2 * Rot2 * Sca2);
	model_1.Updata();
}

void Graphics::Draw()
{

	cmd_buff.Begin(&framebuffer, current_buffer);
	//cmd_buff.Wait(&graphic_queue);
	image.barrierResource(&cmd_buff, current_buffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		VK_ACCESS_MEMORY_READ_BIT, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

	cmd_buff.Begin_Render_pass(Device.window_size, &framebuffer, current_buffer, &renderpass);

	model_1.Draw();
	this->obj_1.Draw();
	this->obj_2.Draw();

	vkCmdEndRenderPass(cmd_buff.cmd_buff);

	cmd_buff.End();

	cmd_buff.submitCommand(&graphic_queue, &fence, &semaphore);
	//ここでイメージバッファにエラー
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
	default: std::cout << "waitForFence returns unknown value.\n" << std::endl;
	}

	vulkan::Error::Window(vkResetFences(this->Device.device, 1, &fence.Fence), "fenceのResetに失敗");
	vulkan::Error::Window(vkAcquireNextImageKHR(this->Device.device,
		swapchain.swapChain,
		UINT64_MAX,
		VK_NULL_HANDLE,
		fence.Fence,
		&current_buffer), "次のimageを取得できませんでした");

	vulkan::Error::Window(vkWaitForFences(this->Device.device, 1, &fence.Fence, VK_FALSE, FENCE_TIMEOUT), "fenceを待つことができませんでした");
	vulkan::Error::Window(vkResetFences(this->Device.device, 1, &fence.Fence), "fenceのResetに失敗");

}
