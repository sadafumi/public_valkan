#include "vulkan_api.h"


void vulkan::data::Render_Pass::Init(Device* in_Device, Swap_Chain* in_swapchain, Depth_Buffer* in_Depth_Buffer, bool deps_flag,bool clear, VkImageLayout finalLayout)
{
	in_swapchain = in_swapchain;
	finalLayout = finalLayout;
	VkAttachmentDescription attachmentDesc[2];
	attachmentDesc[0].format = VK_FORMAT_B8G8R8A8_UNORM;
	attachmentDesc[0].samples = VK_SAMPLE_COUNT_1_BIT;
	attachmentDesc[0].loadOp = clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD;
	attachmentDesc[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachmentDesc[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachmentDesc[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	//attachmentDesc[0].finalLayout = finalLayout;
	attachmentDesc[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachmentDesc[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachmentDesc[0].flags = 0;

	if(deps_flag)
	{
		attachmentDesc[1].format = in_Depth_Buffer->format;
		attachmentDesc[1].samples = VK_SAMPLE_COUNT_1_BIT;
		attachmentDesc[1].loadOp = clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD;
		attachmentDesc[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentDesc[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		attachmentDesc[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachmentDesc[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachmentDesc[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		attachmentDesc[1].flags = 0;
	}

	VkAttachmentReference attachmentRef = {};
	attachmentRef.attachment = 0;
	attachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depth_reference = {};
	depth_reference.attachment = 1;
	depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.flags = 0;
	subpass.inputAttachmentCount = 0;
	subpass.pInputAttachments = NULL;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &attachmentRef;
	subpass.pResolveAttachments = NULL;
	subpass.pDepthStencilAttachment = deps_flag ? &depth_reference : NULL;
	subpass.preserveAttachmentCount = 0;
	subpass.pPreserveAttachments = NULL;

	VkRenderPassCreateInfo renderPassInfo{};

	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.pNext = NULL;
	renderPassInfo.attachmentCount = deps_flag ? 2 : 1;
	renderPassInfo.pAttachments = attachmentDesc;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 0;
	renderPassInfo.pDependencies = NULL;

	vulkan::Error::Window(vkCreateRenderPass(in_Device->device, &renderPassInfo, NULL, &RenderPass),"レンダーパスの作成に失敗");
}

void vulkan::data::Render_Pass::Uninit(Device* in_Device)
{
	vkDestroyRenderPass(in_Device->device, RenderPass, NULL);
}
