#include "vulkan_api.h"

void vulkan::data::Command_Buffer::Init(Device * in_Device, Command_Pool* cmd_pool,int buff_size)
{
	VkCommandBufferAllocateInfo cmd = {};
	cmd.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmd.pNext = NULL;
	cmd.commandPool = cmd_pool->cmd_pool;
	cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cmd.commandBufferCount = buff_size;

	vulkan::Error::Window(vkAllocateCommandBuffers(in_Device->device, &cmd, &this->cmd_buff),"コマンドバッファの作成に失敗");

	this->scissor.Init(in_Device->window_size);
	this->viewport.Init(in_Device->window_size);
}

void vulkan::data::Command_Buffer::Uninit(Device * in_Device, Command_Pool* cmd_pool)
{
	VkCommandBuffer cmd_bufs[1] = { this->cmd_buff};
	vkFreeCommandBuffers(in_Device->device, cmd_pool->cmd_pool, 1, cmd_bufs);
}

void vulkan::data::Command_Buffer::submitCommand(Graphic_Queue * in_Q, Fence* in_fence, Semaphore* semap)
{
	semap = semap;
	VkPipelineStageFlags pipe_stage_flags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	VkSubmitInfo submit_info[1] = {};
	submit_info[0].pNext = NULL;
	submit_info[0].sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	//submit_info[0].waitSemaphoreCount = 1;
	//submit_info[0].pWaitSemaphores = &semap->imageAcquiredSemaphore;
	submit_info[0].pWaitDstStageMask = &pipe_stage_flags;
	submit_info[0].commandBufferCount = 1;
	submit_info[0].pCommandBuffers = &cmd_buff;
	submit_info[0].signalSemaphoreCount = 0;
	submit_info[0].pSignalSemaphores = NULL;

	if (in_fence == NULL)
	{
		vulkan::Error::Window(vkQueueSubmit(in_Q->graphics_queue, 1, submit_info, VK_NULL_HANDLE), "QueueSubmitエラー");
	}
	else
	{
		vulkan::Error::Window(vkQueueSubmit(in_Q->graphics_queue, 1, submit_info, in_fence->Fence), "QueueSubmitエラー"); {}
	}	


}

void vulkan::data::Command_Buffer::Wait(Graphic_Queue* in_Q)
{
	vulkan::Error::Window(vkQueueWaitIdle(in_Q->graphics_queue), "WAIT");
}

void vulkan::data::Command_Buffer::Begin(Frame_Buffer* in_fb,int index)
{
	VkCommandBufferInheritanceInfo inhInfo{};
	VkCommandBufferBeginInfo beginInfo{};

	inhInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	inhInfo.framebuffer = in_fb->Frame_Buffer[index];
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.pInheritanceInfo = &inhInfo;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(cmd_buff, &beginInfo);
}

void vulkan::data::Command_Buffer::Begin_Render_pass(Utility::Int_Vec2 win, Frame_Buffer* in_fb,int index,  Render_Pass* in_r_pass)
{
	VkClearValue clear_values[2];
	clear_values[0].color.float32[0] = 0.2f;
	clear_values[0].color.float32[1] = 0.2f;
	clear_values[0].color.float32[2] = 0.2f;
	clear_values[0].color.float32[3] = 0.2f;
	clear_values[1].depthStencil.depth = 1.0f;
	clear_values[1].depthStencil.stencil = 0;

	VkRenderPassBeginInfo rp_begin;
	rp_begin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	rp_begin.pNext = NULL;
	rp_begin.renderPass = in_r_pass->RenderPass;
	rp_begin.framebuffer = in_fb->Frame_Buffer[index];
	rp_begin.renderArea.offset.x = 0;
	rp_begin.renderArea.offset.y = 0;
	rp_begin.renderArea.extent.width = win.x;
	rp_begin.renderArea.extent.height = win.y;
	rp_begin.clearValueCount = 2;
	rp_begin.pClearValues = clear_values;

	vkCmdBeginRenderPass(cmd_buff, &rp_begin, VK_SUBPASS_CONTENTS_INLINE);
}

void vulkan::data::Command_Buffer::End()
{
	vkEndCommandBuffer(cmd_buff);
}

void vulkan::data::Command_Buffer::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
{
	vkCmdSetViewport(cmd_buff, 0, 1, &this->viewport.viewport);
	vkCmdSetScissor(cmd_buff, 0, 1, &this->scissor.scissor);

	vkCmdDraw(cmd_buff, vertexCount, instanceCount, firstVertex, firstInstance);
}

