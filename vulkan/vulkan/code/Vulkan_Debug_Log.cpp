#include "vulkan.h"
#include <sstream>
#include <iostream>

void vulkan::data::Debug_Log::Init(Instance * Instance)
{
	VkResult err;
	dbgCreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(Instance->instance, "vkCreateDebugReportCallbackEXT");
	if (!dbgCreateDebugReportCallback) 
	{
		MessageBox(NULL, "GetInstanceProcAddr: Unable to find vkCreateDebugReportCallbackEXT function.", "Alert1", MB_OK);
		//MessageBox(NULL, L"GetInstanceProcAddr: Unable to find vkCreateDebugReportCallbackEXT function.", L"Alert1", MB_OK);
		exit(1);
	}

	dbgDestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(Instance->instance, "vkDestroyDebugReportCallbackEXT");
	if (!dbgDestroyDebugReportCallback) 
	{
		MessageBox(NULL, "GetInstanceProcAddr: Unable to find vkDestroyDebugReportCallbackEXT function.", "Alert2", MB_OK);
		//MessageBox(NULL, L"GetInstanceProcAddr: Unable to find vkDestroyDebugReportCallbackEXT function.", L"Alert2", MB_OK);
		exit(1);
	}

	VkDebugReportCallbackCreateInfoEXT create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	create_info.pNext = NULL;
	create_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	create_info.pfnCallback = dbgFunc;
	create_info.pUserData = NULL;

	err = dbgCreateDebugReportCallback(Instance->instance, &create_info, NULL, &debug_report_callback);
	switch (err) 
	{
	case VK_SUCCESS:
		break;
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		MessageBox(NULL, "dbgCreateDebugReportCallback: out of host memory\n", "Alert", MB_OK);
		//MessageBox(NULL, L"dbgCreateDebugReportCallback: out of host memory\n", L"Alert", MB_OK);
		exit(1);
		break;
	default:
		MessageBox(NULL, "dbgCreateDebugReportCallback: unknown failure\n", "Alert", MB_OK);
		//MessageBox(NULL, L"dbgCreateDebugReportCallback: unknown failure\n", L"Alert", MB_OK);
		exit(1);
		break;
	}
}

void vulkan::data::Debug_Log::Uninit(Instance * Instance)
{
	dbgDestroyDebugReportCallback(Instance->instance, debug_report_callback, NULL);
}

VKAPI_ATTR VkBool32 VKAPI_CALL vulkan::data::Debug_Log::dbgFunc(VkDebugReportFlagsEXT msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location, int32_t msgCode, const char * pLayerPrefix, const char * pMsg, void * pUserData)
{
	pUserData = pUserData;
	objType = objType;
	srcObject = srcObject;
	location = location;
	std::ostringstream message;

	if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) 
	{
		message << "ERROR: ";
	}
	else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) 
	{
		message << "WARNING: ";
	}
	else if (msgFlags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) 
	{
		message << "PERFORMANCE WARNING: ";
	}
	else if (msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) 
	{
		message << "INFO: ";
	}
	else if (msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) 
	{
		message << "DEBUG: ";
	}
	message << "[" << pLayerPrefix << "] Code " << msgCode << " |" << pMsg  << "|\n";

#ifdef _WIN32
	//MessageBox(NULL, message.str().c_str(), "エラーメッセージ", MB_OK);
	std::cout << message.str() << std::endl;
	//std::cout << pMsg << std::endl;
	//MessageBox(NULL, (LPCTSTR)message.str().c_str(), L"Alert", MB_OK);
#else
	std::cout << message.str() << std::endl;
#endif

	/*
	 * false indicates that layer should not bail-out of an
	 * API call that had validation failures. This may mean that the
	 * app dies inside the driver due to invalid parameter(s).
	 * That's what would happen without validation layers, so we'll
	 * keep that behavior here.
	 */
	return false;
}
