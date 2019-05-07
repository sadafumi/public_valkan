#include "vulkan_api.h"

void vulkan::data::ImageView::Init(Device * in_Device, Image * in_Image)
{
	this->ImageViews.resize(in_Image->Images.size());
	for (unsigned int i = 0; i < this->ImageViews.size(); i++)
	{
		VkImageViewCreateInfo vinfo{};
		vinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		vinfo.image = in_Image->Images[i];
		vinfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		vinfo.format = VK_FORMAT_B8G8R8A8_UNORM;
		vinfo.components =
		{
			VK_COMPONENT_SWIZZLE_R,
			VK_COMPONENT_SWIZZLE_G,
			VK_COMPONENT_SWIZZLE_B,
			VK_COMPONENT_SWIZZLE_A
		};
		vinfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
		vulkan::Error::Window(vkCreateImageView(in_Device->device, &vinfo, NULL, &this->ImageViews[i]), "イメージビューの作成に失敗");
	}
}

void vulkan::data::ImageView::Destroy(Device * in_Device)
{
	for (unsigned int i = 0; i < this->ImageViews.size(); i++)
	{
		vkDestroyImageView(in_Device->device, this->ImageViews[i], NULL);
	}
}
