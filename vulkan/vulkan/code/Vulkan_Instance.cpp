#include "vulkan_api.h"
#include <vector>

void vulkan::data::Instance::Init()
{
	const VkApplicationInfo app_info =
	{
		VK_STRUCTURE_TYPE_APPLICATION_INFO, //sType
		NULL,//pNext
		"Test1",//アプリの名前
		0,//アプリのバージョン
		"Test1",//アプリを作るエンジン名*ないのでアプリ名
		0,//アプリ作成に使うエンジンのバージョン
		VK_API_VERSION_1_0 //アプリに使用するVulkanのバージョン
	};
	std::vector<const char *> instance_layer_names;
	std::vector<const char *> instance_extension_names;
	instance_layer_names.push_back("VK_LAYER_LUNARG_standard_validation");

	instance_extension_names.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#ifdef __ANDROID__
	instance_extension_names.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(_WIN32)
	instance_extension_names.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	instance_extension_names.push_back(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	instance_extension_names.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	instance_extension_names.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#else
	instance_extension_names.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#endif
#ifdef _DEBUG
	//instance_extension_names.push_back(VK_EXT_DEBUG_REPORT_SPEC_VERSION);
	instance_extension_names.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
#endif // _DEBUG


	VkInstanceCreateInfo inst_info;
	inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_info.pNext = NULL;
	inst_info.flags = 0;
	inst_info.pApplicationInfo = &app_info;
	inst_info.enabledLayerCount = (uint32_t)instance_layer_names.size();
	inst_info.ppEnabledLayerNames = instance_layer_names.size() ? instance_layer_names.data() : NULL;
	inst_info.enabledExtensionCount = (uint32_t)instance_extension_names.size();
	inst_info.ppEnabledExtensionNames = instance_extension_names.data();
	//レイヤも拡張機能も使わない場合は0を設定

	//第二引数がNULLなのはメモリアロケータを使用しないから
	vulkan::Error::Window(vkCreateInstance(&inst_info, NULL, &instance),"Instance生成エラー");
}

void vulkan::data::Instance::Uninit()
{
	vkDestroyInstance(instance, NULL);
}
