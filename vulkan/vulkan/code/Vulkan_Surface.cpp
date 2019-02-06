#include "vulkan.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

void vulkan::data::Surface::Init(HWND hWnd, HINSTANCE hInstance, Instance *in_Instance)
{
	VkWin32SurfaceCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = NULL;
	createInfo.hinstance = hInstance;
	createInfo.hwnd = hWnd;
	vulkan::Error::Window(vkCreateWin32SurfaceKHR(in_Instance->instance, &createInfo, NULL, &surface), "スワップチェインのsurfaceの作成に失敗");
}

void vulkan::data::Surface::Destroy(Instance *in_Instance)
{
	vkDestroySurfaceKHR(in_Instance->instance,this->surface,NULL);
}
