#include "vulkan_api.h"
#include "mtf.h"
//#include "mtfv.h"
#include "mtfv.hpp"

//
//bool read_ppm(char const* const filename, int& width, int& height, uint64_t rowPitch, unsigned char* dataPtr) {
//	// PPM format expected from http://netpbm.sourceforge.net/doc/ppm.html
//	//  1. magic number
//	//  2. whitespace
//	//  3. width
//	//  4. whitespace
//	//  5. height
//	//  6. whitespace
//	//  7. max color value
//	//  8. whitespace
//	//  7. data
//
//	// Comments are not supported, but are detected and we kick out
//	// Only 8 bits per channel is supported
//	// If dataPtr is nullptr, only width and height are returned
//
//	// Read in values from the PPM file as characters to check for comments
//	char magicStr[3] = {}, heightStr[6] = {}, widthStr[6] = {}, formatStr[6] = {};
//
//#ifndef __ANDROID__
//	FILE* fPtr = fopen(filename, "rb");
//#else
//	FILE* fPtr = AndroidFopen(filename, "rb");
//#endif
//	if (!fPtr) {
//		printf("Bad filename in read_ppm: %s\n", filename);
//		return false;
//	}
//
//	// Read the four values from file, accounting with any and all whitepace
//	fscanf(fPtr, "%s %s %s %s ", magicStr, widthStr, heightStr, formatStr);
//
//	// Kick out if comments present
//	if (magicStr[0] == '#' || widthStr[0] == '#' || heightStr[0] == '#' || formatStr[0] == '#') {
//		printf("Unhandled comment in PPM file\n");
//		return false;
//	}
//
//	// Only one magic value is valid
//	if (strncmp(magicStr, "P6", sizeof(magicStr))) {
//		printf("Unhandled PPM magic number: %s\n", magicStr);
//		return false;
//	}
//
//	width = atoi(widthStr);
//	height = atoi(heightStr);
//
//	// Ensure we got something sane for width/height
//	static const int saneDimension = 32768;  //??
//	if (width <= 0 || width > saneDimension) {
//		printf("Width seems wrong.  Update read_ppm if not: %u\n", width);
//		return false;
//	}
//	if (height <= 0 || height > saneDimension) {
//		printf("Height seems wrong.  Update read_ppm if not: %u\n", height);
//		return false;
//	}
//
//	if (dataPtr == nullptr) {
//		// If no destination pointer, caller only wanted dimensions
//		return true;
//	}
//
//	// Now read the data
//	for (int y = 0; y < height; y++) {
//		unsigned char* rowPtr = dataPtr;
//		for (int x = 0; x < width; x++) {
//			fread(rowPtr, 3, 1, fPtr);
//			rowPtr[3] = 255; /* Alpha of 1 */
//			rowPtr += 4;
//		}
//		dataPtr += rowPitch;
//	}
//	fclose(fPtr);
//
//	return true;
//}


void vulkan::Resources::Texture::set_image_layout(data::Graphic_Queue* in_Q, data::Command_Buffer* in_cmd, VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkPipelineStageFlags src_stages, VkPipelineStageFlags dest_stages)
{
	vulkan::Error::Window(!(in_cmd->cmd_buff != VK_NULL_HANDLE),"CommandBufferがありません");
	vulkan::Error::Window(!(in_Q->graphics_queue != VK_NULL_HANDLE),"グラフィックQがありません");

	VkImageMemoryBarrier image_memory_barrier = {};
	image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	image_memory_barrier.pNext = NULL;
	image_memory_barrier.srcAccessMask = 0;
	image_memory_barrier.dstAccessMask = 0;
	image_memory_barrier.oldLayout = old_image_layout;
	image_memory_barrier.newLayout = new_image_layout;
	image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	image_memory_barrier.image = image;
	image_memory_barrier.subresourceRange.aspectMask = aspectMask;
	image_memory_barrier.subresourceRange.baseMipLevel = 0;
	image_memory_barrier.subresourceRange.levelCount = 1;
	image_memory_barrier.subresourceRange.baseArrayLayer = 0;
	image_memory_barrier.subresourceRange.layerCount = 1;

	switch (old_image_layout) 
	{
	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		image_memory_barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		image_memory_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_PREINITIALIZED:
		image_memory_barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		break;

	default:
		break;
	}
	switch (new_image_layout) 
	{
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		break;

	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		image_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		break;

	case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		image_memory_barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		break;

	case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		image_memory_barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		break;

	default:
		break;
	}
	vkCmdPipelineBarrier(in_cmd->cmd_buff, src_stages, dest_stages, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);
	//(in_cmd->cmd_buff, src_stages, dest_stages, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);
}

void vulkan::Resources::Texture::Image( texture_object* Tex_obj, data::Device * in_Device, const char * tex_path, VkImageUsageFlags extraUsages, VkFormatFeatureFlags extraFeatures)
{
	extraUsages = extraUsages;
	extraFeatures = extraFeatures;
	mtf::Texture in_Data;
	in_Data.LoadSize(tex_path);
	
	Tex_obj->tex_width = in_Data.Width;
	Tex_obj->tex_height = in_Data.Height;

	//read_ppm(tex_path, Tex_obj->tex_width, Tex_obj->tex_height, 0, NULL);
	
	Tex_obj->needs_staging = (!(in_Device->formatProps.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT));

	VkImageCreateInfo image_create_info = {};
	image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image_create_info.pNext = NULL;
	image_create_info.imageType = VK_IMAGE_TYPE_2D;
	image_create_info.format = VK_FORMAT_R8G8B8A8_UNORM;
	image_create_info.extent.width = Tex_obj->tex_width;
	image_create_info.extent.height = Tex_obj->tex_height;
	image_create_info.extent.depth = 1;
	image_create_info.mipLevels = 1;
	image_create_info.arrayLayers = 1;
	image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
	image_create_info.tiling = VK_IMAGE_TILING_LINEAR;
	image_create_info.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
	//image_create_info.initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	image_create_info.usage = Tex_obj->needs_staging ? (VK_IMAGE_USAGE_TRANSFER_SRC_BIT | extraUsages) : (VK_IMAGE_USAGE_SAMPLED_BIT | extraUsages);
	//image_create_info.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | extraUsages;
	image_create_info.queueFamilyIndexCount = 0;
	image_create_info.pQueueFamilyIndices = NULL;
	image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	image_create_info.flags = 0;

	VkMemoryAllocateInfo mem_alloc = {};
	mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	mem_alloc.pNext = NULL;
	mem_alloc.allocationSize = 0;
	mem_alloc.memoryTypeIndex = 0;

	VkMemoryRequirements mem_reqs;

	vulkan::Error::Window(vkCreateImage(in_Device->device, &image_create_info, NULL, &Tex_obj->image),"テクスチャのイメージの作成に失敗した");

	vkGetImageMemoryRequirements(in_Device->device, Tex_obj->image, &mem_reqs);

	mem_alloc.allocationSize = mem_reqs.size;

	vulkan::data::Checker::memory_type_from_properties(	 mem_reqs.memoryTypeBits,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,&mem_alloc.memoryTypeIndex);

	vulkan::Error::Window(vkAllocateMemory(in_Device->device, &mem_alloc, NULL, &(Tex_obj->image_memory)),"メモリの確保に失敗しました");

	vulkan::Error::Window(vkBindImageMemory(in_Device->device, Tex_obj->image, Tex_obj->image_memory, 0),"イメージメモリにコピー");

	VkImageSubresource subres = {};
	subres.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subres.mipLevel = 0;
	subres.arrayLayer = 0;

	VkSubresourceLayout layout = {};
	void *data;

	if(Tex_obj->needs_staging)
	{
		VkBufferCreateInfo buffer_create_info = {};
		buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_create_info.pNext = NULL;
		buffer_create_info.flags = 0;
		buffer_create_info.size = (Tex_obj->tex_width * Tex_obj->tex_height) * 4;
		buffer_create_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		buffer_create_info.queueFamilyIndexCount = 0;
		buffer_create_info.pQueueFamilyIndices = NULL;
		vulkan::Error::Window(vkCreateBuffer(in_Device->device, &buffer_create_info, NULL, &Tex_obj->buffer),"イメージBufferの作成に失敗");

		VkMemoryAllocateInfo buf_mem_alloc = {};
		buf_mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		buf_mem_alloc.pNext = NULL;
		buf_mem_alloc.allocationSize = 0;
		buf_mem_alloc.memoryTypeIndex = 0;

		vkGetBufferMemoryRequirements(in_Device->device, Tex_obj->buffer, &mem_reqs);
		buf_mem_alloc.allocationSize = mem_reqs.size;

		vulkan::data::Checker::memory_type_from_properties(mem_reqs.memoryTypeBits,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &buf_mem_alloc.memoryTypeIndex);

		vulkan::Error::Window(vkAllocateMemory(in_Device->device, &buf_mem_alloc, NULL, &(Tex_obj->buffer_memory)),"Bufferの確保に失敗");
		vulkan::Error::Window(vkBindBufferMemory(in_Device->device, Tex_obj->buffer, Tex_obj->buffer_memory, 0), "Bufferへのコピーに失敗");
	}
	else 
	{
		Tex_obj->buffer = VK_NULL_HANDLE;
		Tex_obj->buffer_memory = VK_NULL_HANDLE;

		/* Get the subresource layout so we know what the row pitch is */
		vkGetImageSubresourceLayout(in_Device->device, Tex_obj->image, &subres, &layout);
	}	

	VkDeviceMemory mapped_memory = Tex_obj->needs_staging ? Tex_obj->buffer_memory : Tex_obj->image_memory;
	vulkan::Error::Window(vkMapMemory(in_Device->device, Tex_obj->needs_staging ? Tex_obj->buffer_memory : Tex_obj->image_memory, 0, mem_reqs.size, 0, &data),"マップメモリーの作成に失敗");

	in_Data.LoadData(tex_path, (unsigned char *)data, Tex_obj->needs_staging ? ((unsigned int)Tex_obj->tex_width * 4) : (unsigned int)layout.rowPitch);
	//read_ppm(tex_path, Tex_obj->tex_width, Tex_obj->tex_height, Tex_obj->needs_staging ? (Tex_obj->tex_width * 4) : layout.rowPitch, (unsigned char*)data);

	vkUnmapMemory(in_Device->device, mapped_memory);

	VkImageViewCreateInfo view_info = {};
	view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	view_info.pNext = NULL;
	view_info.image = VK_NULL_HANDLE;
	view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	view_info.format = VK_FORMAT_R8G8B8A8_UNORM;
	view_info.components.r = VK_COMPONENT_SWIZZLE_R;
	view_info.components.g = VK_COMPONENT_SWIZZLE_G;
	view_info.components.b = VK_COMPONENT_SWIZZLE_B;
	view_info.components.a = VK_COMPONENT_SWIZZLE_A;
	view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	view_info.subresourceRange.baseMipLevel = 0;
	view_info.subresourceRange.levelCount = 1;
	view_info.subresourceRange.baseArrayLayer = 0;
	view_info.subresourceRange.layerCount = 1;

	/* create image view */
	view_info.image = Tex_obj->image;
	vulkan::Error::Window(vkCreateImageView(in_Device->device, &view_info, NULL, &Tex_obj->view),"イメージビューの作成");

}

void vulkan::Resources::Texture::Sampler(VkSampler * out, data::Device * in_Device)
{
	VkSamplerCreateInfo samplerCreateInfo = {};
	samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerCreateInfo.magFilter = VK_FILTER_NEAREST;
	samplerCreateInfo.minFilter = VK_FILTER_NEAREST;
	samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
	samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerCreateInfo.mipLodBias = 0.0;
	samplerCreateInfo.anisotropyEnable = VK_FALSE;
	samplerCreateInfo.maxAnisotropy = 1;
	samplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
	samplerCreateInfo.minLod = 0.0;
	samplerCreateInfo.maxLod = 0.0;
	samplerCreateInfo.compareEnable = VK_FALSE;
	samplerCreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	/* create sampler */
	vulkan::Error::Window( vkCreateSampler(in_Device->device, &samplerCreateInfo, NULL, out),"Samplerの作成に失敗しました");
}

void vulkan::Resources::Texture::Create(Texture* in_tex, data::Device* in_Device, const char * tex_path, VkImageUsageFlags extraUsages, VkFormatFeatureFlags extraFeatures)
{
	texture_object Tex_obj = {};

	Image(&Tex_obj, in_Device, tex_path, extraUsages, extraFeatures);
	
	Sampler(&Tex_obj.sampler,in_Device);
	
	in_tex->texlist.push_back(Tex_obj);

	in_tex->texture_data.image_info.imageView = in_tex->texlist.back().view;
	in_tex->texture_data.image_info.sampler = in_tex->texlist.back().sampler;
	in_tex->texture_data.image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

void vulkan::Resources::Texture::Set_Image_Layout(data::Graphic_Queue* in_Q, data::Command_Buffer * in_cmd)
{
	for (unsigned int i = 0; i < this->texlist.size(); i++)
	{
		if (!this->texlist[i].needs_staging)
		{
			this->texlist[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			set_image_layout(in_Q, in_cmd, this->texlist[i].image,
				VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED, this->texlist[i].imageLayout,
				VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
		}
		else
		{
			set_image_layout(in_Q, in_cmd, this->texlist[i].image,
				VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);


			VkBufferImageCopy copy_region;
			copy_region.bufferOffset = 0;
			copy_region.bufferRowLength = this->texlist[i].tex_width;
			copy_region.bufferImageHeight = this->texlist[i].tex_height;
			copy_region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			copy_region.imageSubresource.mipLevel = 0;
			copy_region.imageSubresource.baseArrayLayer = 0;
			copy_region.imageSubresource.layerCount = 1;
			copy_region.imageOffset.x = 0;
			copy_region.imageOffset.y = 0;
			copy_region.imageOffset.z = 0;
			copy_region.imageExtent.width = this->texlist[i].tex_width;
			copy_region.imageExtent.height = this->texlist[i].tex_height;
			copy_region.imageExtent.depth = 1;


			vkCmdCopyBufferToImage(in_cmd->cmd_buff, this->texlist[i].buffer, this->texlist[i].image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy_region);

			this->texlist[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			set_image_layout(in_Q, in_cmd, this->texlist[i].image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, this->texlist[i].imageLayout, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);

		}
	}
}

void vulkan::Resources::Texture::Destroy(data::Device* in_Device)
{
	for (unsigned int i = 0; i < this->texlist.size(); i++)
	{
		vkDestroySampler(in_Device->device, this->texlist[i].sampler, NULL);
		vkDestroyImageView(in_Device->device, this->texlist[i].view, NULL);
		vkDestroyImage(in_Device->device, this->texlist[i].image, NULL);
		vkFreeMemory(in_Device->device, this->texlist[i].image_memory, NULL);
		vkFreeMemory(in_Device->device, this->texlist[i].buffer_memory, NULL);
	}
	if (this->stagingImage) 
	{
		vkDestroyImage(in_Device->device, this->stagingImage, NULL);
	}
	if (this->stagingMemory) 
	{
		vkFreeMemory(in_Device->device, this->stagingMemory, NULL);
	}
}
