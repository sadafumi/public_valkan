//========================================================================
//	maked by sadafumi 
//	2019/2/7
//========================================================================
#pragma once
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <vulkan/vulkan.h>
#include "Utility.h"

namespace vulkan
{
	class Error
	{
	public:
		static void Window(VkResult, const char *);
		static void Window(bool, const char *);
	};
	namespace data
	{
		class Global_Layer_Properties
		{
		public:
			typedef struct
			{
				VkLayerProperties properties;
				std::vector<VkExtensionProperties> instance_extensions;
				std::vector<VkExtensionProperties> device_extensions;
			} layer_properties;
			VkResult Init();
			VkResult init_global_extension_properties(layer_properties &layer_props);
			void Uninit();
			std::vector<layer_properties> instance_layer_properties;
		};
		class Instance
		{
		public:
			void Init();
			void Uninit();
			VkInstance instance;
		};
		class Debug_Log
		{
		public:
			void Init(Instance* Instance);
			void Uninit(Instance* Instance);
			static VKAPI_ATTR VkBool32 VKAPI_CALL dbgFunc(VkDebugReportFlagsEXT msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
				size_t location, int32_t msgCode, const char *pLayerPrefix, const char *pMsg,
				void *pUserData);
			PFN_vkCreateDebugReportCallbackEXT dbgCreateDebugReportCallback;
			PFN_vkDestroyDebugReportCallbackEXT dbgDestroyDebugReportCallback;
			VkDebugReportCallbackEXT debug_report_callback;
		};
		class PhysicalDevice
		{
		public:
			void Init(Instance* Instance, Global_Layer_Properties*);
			void Uninit();
			VkPhysicalDevice Get_PhyDevice();
		private:
			VkResult init_device_extension_properties(Global_Layer_Properties::layer_properties &layer_props);
		public:
			VkPhysicalDeviceProperties gpu_props;
			VkPhysicalDeviceMemoryProperties memory_properties;
			std::vector<VkPhysicalDevice> phydev;
			uint32_t queue_family_count;
			std::vector<VkQueueFamilyProperties> queue_props;
		};
		class Device
		{
		public:
			void Init(PhysicalDevice*);
			void Uninit();
			VkDevice device;
			int queue_Family_index;
		};
		class Graphic_Queue
		{
		public:
			void Init(Device*);
			void Uninit(Device*);
			VkQueue graphics_queue;
			int graphics_queue_family_index;
			VkQueue present_queue;
			int present_queue_family_index;
		};
		class Checker
		{
		public:
			static bool memory_type_from_properties(PhysicalDevice* in_PhyDevice, uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex);
		};
		class Surface
		{
		public:
			void Init(HWND hWnd, HINSTANCE hInstance, Instance*);
			void Destroy(Instance *in_Instance);
			VkSurfaceKHR surface;
		};
		class Swap_Chain
		{
		public:
			void Init(Utility::Int_Vec2, PhysicalDevice*, Device*, Surface*, VkImageUsageFlags usageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
			void Uninit(Device*);
			VkSwapchainKHR swapChain;
		};
		class Depth_Buffer
		{
		public:
			void Init(Utility::Int_Vec2, PhysicalDevice*, Device*);
			void Uninit(Device*);
			VkFormat format;
			VkImage image;
			VkDeviceMemory mem;
			VkImageView view;
		};
		class Render_Pass
		{
		public:
			void Init(Device*, Swap_Chain*, Depth_Buffer*, bool depth_flag, bool clear = true, VkImageLayout finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
			void Uninit(Device*);
			VkRenderPass RenderPass;
		};
		class Fence
		{
		public:
			void Init(Device*);
			void Uninit(Device*);
			VkFence Fence;
		};
		class Semaphore
		{
		public:
			void Create(Device*);
			VkSemaphore imageAcquiredSemaphore;
		};

		class Command_Pool
		{
		public:
			void Init(Device*);
			void Uninit(Device*);
			VkCommandPool cmd_pool;
		};
		class Frame_Buffer;
		class Command_Buffer
		{
		public:
			void Init(Device*, Command_Pool*, int);
			void Uninit(Device*, Command_Pool*);
			void submitCommand(Graphic_Queue*, Fence*, Semaphore*);
			void Wait(Graphic_Queue *);
			void Begin(Frame_Buffer*, int);
			void Begin_Render_pass(Utility::Int_Vec2, Frame_Buffer*, int, Render_Pass*);
			void End();
			VkCommandBuffer cmd_buff;
		};
		class Image
		{
		public:
			void Init(Device* in_Device, Swap_Chain* in_swapchain);
			void Destroy();
			void Image_Layoutting(Command_Buffer*);
			void barrierResource(Command_Buffer*, int,
				VkPipelineStageFlags srcStageFlags, VkPipelineStageFlags dstStageFlags,
				VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask,
				VkImageLayout srcImageLayout, VkImageLayout dstImageLayout);
			std::vector< VkImage> Images;
		};
		class ImageView
		{
		public:
			void Init(Device* in_Device, Image* in_Image);
			void Destroy(Device* in_Device);
			std::vector< VkImageView> ImageViews;
		};
		class Frame_Buffer
		{
		public:
			void Init(Utility::Int_Vec2, Device*, ImageView*, Render_Pass*, Depth_Buffer*, bool depth_flag);
			void Uninit(Device*);
			std::vector<VkFramebuffer> Frame_Buffer;

		};
	}
	namespace Resources
	{
		class Vertex
		{
		public:
			Vertex() {};
			Vertex(Utility::Vec4, Utility::Vec4);
			//Vertex(Utility::Vec4, Utility::Vec2);
			Utility::Vec4 Pos;
			//Utility::Vec2 UV;
			Utility::Vec4 color;
		};
		//namespace Vertex 
		//{
		//	class vec4vec4
		//	{
		//	public:
		//		vec4vec4() {};
		//		vec4vec4(Utility::Vec4, Utility::Vec4);
		//		Utility::Vec4 Pos;
		//		Utility::Vec4 color;
		//	};
		//	class vec3vec4
		//	{
		//	public:
		//		vec3vec4() {};
		//		vec3vec4(Utility::Vec3, Utility::Vec4);
		//		Utility::Vec3 Pos;
		//		Utility::Vec4 color;
		//	};
		//	class vec2vec4
		//	{
		//	public:
		//		vec2vec4() {};
		//		vec2vec4(Utility::Vec2, Utility::Vec4);
		//		Utility::Vec2 Pos;
		//		Utility::Vec4 color;
		//	};
		//	class vec4vec2
		//	{
		//	public:
		//		vec4vec2() {};
		//		vec4vec2(Utility::Vec4, Utility::Vec2);
		//		Utility::Vec4 Pos;
		//		Utility::Vec2 UV;
		//	};
		//}
		class Buffer
		{
		public:

			VkBuffer buffer;
			VkVertexInputBindingDescription vi_binding;
			VkVertexInputAttributeDescription vi_attribs[2];
			static void Create(Buffer*, std::vector<Vertex>/*const void *vertexData*/, int, bool use_texture, data::Device*, data::PhysicalDevice*);
			void Destroy(data::Device*);
		};
		class Texture
		{
		private:
			struct texture_object
			{
				VkSampler sampler;

				VkImage image;
				VkImageLayout imageLayout;

				bool needs_staging;
				VkBuffer buffer;
				VkDeviceSize buffer_size;

				VkDeviceMemory image_memory;
				VkDeviceMemory buffer_memory;
				VkImageView view;
				int32_t tex_width, tex_height;

			};

			VkDeviceMemory stagingMemory;
			VkImage stagingImage;

			static void set_image_layout(data::Graphic_Queue*, data::Command_Buffer* in_cmd, VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkPipelineStageFlags src_stages, VkPipelineStageFlags dest_stages);
			static void Image(texture_object*, data::Device* in_Device, data::PhysicalDevice* PhyDevice, const char* tex_path, VkImageUsageFlags extraUsages, VkFormatFeatureFlags extraFeatures);
			static void Sampler(VkSampler* out, data::Device* in_Device);
		public:
			struct
			{
				VkDescriptorImageInfo image_info;
			} texture_data;
			std::vector<texture_object> texlist;
			static void Create(Texture*, data::Device*, data::PhysicalDevice*, const char* tex_path, VkImageUsageFlags extraUsages = 0, VkFormatFeatureFlags extraFeatures = 0);
			void Set_Image_Layout(data::Graphic_Queue* in_Q, data::Command_Buffer * in_cmd);
			void Destroy(data::Device* in_Device);
		};
		class Shader
		{
		public:
			VkPipelineShaderStageCreateInfo shaderStages[2];
			//static void Create(Shader*, const std::string*vertShaderText, const std::string*fragShaderText, data::Device*);
			static std::vector<char> Load(const std::string& filename);
			static void Create(Shader*, const char * vertShaderText, const char * fragShaderText, data::Device*);
			void Destroy(data::Device*);
		};
	}
	namespace data
	{
		class Uniform_Buffer
		{
		public:
			struct uniform
			{
				VkBuffer buf;
				VkDeviceMemory mem;
				VkDescriptorBufferInfo buffer_info;
			};
			void Init(Device*, PhysicalDevice*, Utility::Int_Vec2);
			void Updata(Device* in_Device);
			void Uninit(Device*);
			VkDeviceSize size;
			uniform uniform_data;
			Utility::mtx4x4 Projection;
			Utility::mtx4x4 View;
			Utility::mtx4x4 Model;
			Utility::mtx4x4 Clip;
			Utility::mtx4x4 MVP;
		};
		class Descriptor_Pool
		{
		public:
			void Init(Device*, bool tex_flag);
			void Create_Layout(Device*, bool tex_flag, VkDescriptorSetLayoutCreateFlags descSetLayoutCreateFlags = 0);
			void Set(Device*, Uniform_Buffer*, bool tex_flag, Resources::Texture*);
			void Updata(Device*, Uniform_Buffer*, bool tex_flag, Resources::Texture*);
			void Uninit(Device*);
			VkDescriptorPool desc_pool;
			std::vector<VkDescriptorSet> desc_set;
			std::vector<VkDescriptorSetLayout> desc_layout;
			const int NUM_DESCRIPTOR_SETS = 1;
		};
		class Pipeline_cache
		{
		public:
			void Init(Device*);
			void Uninit(Device*);
			VkPipelineCache pipelineCache;
		};
		class ViewPort
		{
		public:
			void Init(Utility::Int_Vec2);
			void Set(Command_Buffer*);
			VkViewport viewport;
		};
		class Scissor
		{
		public:
			void Init(Utility::Int_Vec2);
			void Set(Command_Buffer*);
			VkRect2D scissor;
		};
		class Pipeline
		{
		public:
			void Init(Device* in_Device, ViewPort*, Scissor*, Resources::Buffer* in_buff, Resources::Shader* in_Shader, Render_Pass* in_render_pass, Pipeline_cache* in_pipline_cache, bool Depth_flag, VkBool32 include_vi = true);
			void Create_Layout(Device* in_Device, Descriptor_Pool*);
			void Uninit(Device*);
			VkPipeline pipeline;
			VkPipelineLayout pipeline_layout;
			const int NUM_DESCRIPTOR_SETS = 1;
		};
	}
}