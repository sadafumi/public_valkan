#include "vulkan_api.h"
#include "Window_Data.h"

void vulkan::data::Surface::Init(Window_Data in_data, Instance *in_Instance)
{
#ifdef _WIN32
	VkWin32SurfaceCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = NULL;
	createInfo.hinstance = in_data.connect;
	createInfo.hwnd = in_data.wind;
	vulkan::Error::Window(vkCreateWin32SurfaceKHR(in_Instance->instance, &createInfo, NULL, &surface), "スワップチェインのsurfaceの作成に失敗");
#elif defined(__ANDROID__)
	GET_INSTANCE_PROC_ADDR(info.inst, CreateAndroidSurfaceKHR);

	VkAndroidSurfaceCreateInfoKHR createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = NULL;
	createInfo.flags = 0;
	createInfo.window = AndroidGetApplicationWindow();
	res = info.fpCreateAndroidSurfaceKHR(info.inst, &createInfo, NULL, &info.surface);
	vulkan::Error::Window(vkCreateWin32SurfaceKHR(in_Instance->instance, &createInfo, NULL, &surface), "スワップチェインのsurfaceの作成に失敗");
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	VkIOSSurfaceCreateInfoMVK createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
	createInfo.pNext = NULL;
	createInfo.flags = 0;
	createInfo.pView = info.window;
	vulkan::Error::Window(vkCreateIOSSurfaceMVK(in_Instance->instance, &createInfo, NULL, &surface)), "スワップチェインのsurfaceの作成に失敗");
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	VkMacOSSurfaceCreateInfoMVK createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
	createInfo.pNext = NULL;
	createInfo.flags = 0;
	createInfo.pView = info.window;
	res = vkCreateMacOSSurfaceMVK(info.inst, &createInfo, NULL, &info.surface);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	VkWaylandSurfaceCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = NULL;
	createInfo.display = info.display;
	createInfo.surface = info.window;
	res = vkCreateWaylandSurfaceKHR(info.inst, &createInfo, NULL, &info.surface);
#else
	VkXcbSurfaceCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = NULL;
	createInfo.connection = info.connection;
	createInfo.window = info.window;
	res = vkCreateXcbSurfaceKHR(info.inst, &createInfo, NULL, &info.surface);
#endif  // __ANDROID__  && _WIN32


}

void vulkan::data::Surface::Destroy(Instance *in_Instance)
{
	vkDestroySurfaceKHR(in_Instance->instance,this->surface,NULL);
}
