#include "vulkan.h"
#include "Utility.h"

void vulkan::data::Frame_Buffer::Init(Utility::Int_Vec2 in_win,Device* in_Device, ImageView* in_view, Render_Pass* in_Render_Pass, Depth_Buffer* in_depth, bool depth_flag)
{
	// Common Properties
	VkFramebufferCreateInfo fbinfo{};
	VkImageView attachmentViews[2];
	if (depth_flag) 
	{
		attachmentViews[1] = in_depth->view;
	}

	fbinfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	//fbinfo.attachmentCount = 2;//デバスBufferあるから2である普通は1
	fbinfo.attachmentCount = depth_flag ? 2 : 1;//
	fbinfo.renderPass = in_Render_Pass->RenderPass;
	fbinfo.pAttachments = attachmentViews;
	fbinfo.width = in_win.x;
	fbinfo.height = in_win.y;
	fbinfo.layers = 1;
	this->Frame_Buffer.resize(in_view->ImageViews.size());

	for (unsigned int i = 0; i < this->Frame_Buffer.size(); i++)
	{
		attachmentViews[0] = in_view->ImageViews[i];
		vulkan::Error::Window(vkCreateFramebuffer(in_Device->device, &fbinfo, nullptr, &this->Frame_Buffer[i]),"フレームバッファーの作成に失敗");
	}
}

void vulkan::data::Frame_Buffer::Uninit(Device* in_Device)
{
	for (unsigned int i = 0; i < this->Frame_Buffer.size(); i++)
	{
		vkDestroyFramebuffer(in_Device->device, this->Frame_Buffer[i], NULL);
	}
}

