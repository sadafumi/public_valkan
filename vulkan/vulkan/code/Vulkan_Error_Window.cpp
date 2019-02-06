#include "vulkan.h"
#include <string>


void vulkan::Error::Window(VkResult err, const char* out_cher)
{
	if (err != VK_SUCCESS)
	{
		std::string in_cher(out_cher);
		std::string end_chsr("\n");
		std::string add_cher;
		if(err == VK_NOT_READY)
		{
			std::string err_code("VK_NOT_READY");
			add_cher = err_code;
		}
		if (err == VK_TIMEOUT)
		{
			std::string err_code("VK_TIMEOUT");
			add_cher = err_code;
		}
		if (err == VK_EVENT_SET)
		{
			std::string err_code("VK_EVENT_SET");
			add_cher = err_code;
		}
		if (err == VK_EVENT_RESET)
		{
			std::string err_code("VK_EVENT_RESET");
			add_cher = err_code;
		}
		if (err == VK_INCOMPLETE)
		{
			std::string err_code("VK_INCOMPLETE");
			add_cher = err_code;
		}
		if (err == VK_ERROR_OUT_OF_HOST_MEMORY)
		{
			std::string err_code("VK_ERROR_OUT_OF_HOST_MEMORY");
			add_cher = err_code;
		}
		if (err == VK_ERROR_OUT_OF_DEVICE_MEMORY)
		{
			std::string err_code("VK_ERROR_OUT_OF_DEVICE_MEMORY");
			add_cher = err_code;
		}
		if (err == VK_ERROR_INITIALIZATION_FAILED)
		{
			std::string err_code("VK_ERROR_INITIALIZATION_FAILED");
			add_cher = err_code;
		}
		if (err == VK_ERROR_DEVICE_LOST)
		{
			std::string err_code("VK_ERROR_DEVICE_LOST");
			add_cher = err_code;
		}
		if (err == VK_ERROR_MEMORY_MAP_FAILED)
		{
			std::string err_code("VK_ERROR_MEMORY_MAP_FAILED");
			add_cher = err_code;
		}
		if (err == VK_ERROR_LAYER_NOT_PRESENT)
		{
			std::string err_code("VK_ERROR_LAYER_NOT_PRESENT");
			add_cher = err_code;
		}
		if (err == VK_ERROR_EXTENSION_NOT_PRESENT)
		{
			std::string err_code("VK_ERROR_EXTENSION_NOT_PRESENT");
			add_cher = err_code;
		}
		if (err == VK_ERROR_FEATURE_NOT_PRESENT)
		{
			std::string err_code("VK_ERROR_FEATURE_NOT_PRESENT");
			add_cher = err_code;
		}
		if (err == VK_ERROR_INCOMPATIBLE_DRIVER)
		{
			std::string err_code("VK_ERROR_INCOMPATIBLE_DRIVER");
			add_cher = err_code;
		}
		if (err == VK_ERROR_TOO_MANY_OBJECTS)
		{
			std::string err_code("VK_ERROR_TOO_MANY_OBJECTS");
			add_cher = err_code;
		}
		if (err == VK_ERROR_FORMAT_NOT_SUPPORTED)
		{
			std::string err_code("VK_ERROR_FORMAT_NOT_SUPPORTED");
			add_cher = err_code;
		}
		if (err == VK_ERROR_FRAGMENTED_POOL)
		{
			std::string err_code("VK_ERROR_FRAGMENTED_POOL");
			add_cher = err_code;
		}
		if (err == VK_ERROR_OUT_OF_POOL_MEMORY)
		{
			std::string err_code("VK_ERROR_OUT_OF_POOL_MEMORY");
			add_cher = err_code;
		}
		if (err == VK_ERROR_INVALID_EXTERNAL_HANDLE)
		{
			std::string err_code("VK_ERROR_INVALID_EXTERNAL_HANDLE");
			add_cher = err_code;
		}
		if (err == VK_ERROR_SURFACE_LOST_KHR)
		{
			std::string err_code("VK_ERROR_SURFACE_LOST_KHR");
			add_cher = err_code;
		}
		if (err == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR)
		{
			std::string err_code("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");
			add_cher = err_code;
		}
		if (err == VK_SUBOPTIMAL_KHR)
		{
			std::string err_code("VK_SUBOPTIMAL_KHR");
			add_cher = err_code;
		}
		if (err == VK_ERROR_OUT_OF_DATE_KHR)
		{
			std::string err_code("VK_ERROR_OUT_OF_DATE_KHR");
			add_cher = err_code;
		}
		if (err == VK_ERROR_INCOMPATIBLE_DISPLAY_KHR)
		{
			std::string err_code("VK_ERROR_INCOMPATIBLE_DISPLAY_KHR");
			add_cher = err_code;
		}
		if (err == VK_ERROR_VALIDATION_FAILED_EXT)
		{
			std::string err_code("VK_ERROR_VALIDATION_FAILED_EXT");
			add_cher = err_code;
		}
		if (err == VK_ERROR_INVALID_SHADER_NV)
		{
			std::string err_code("VK_ERROR_INVALID_SHADER_NV");
			add_cher = err_code;
		}
		if (err == VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT)
		{
			std::string err_code("VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT");
			add_cher = err_code;
		}
		if (err == VK_ERROR_FRAGMENTATION_EXT)
		{
			std::string err_code("VK_ERROR_FRAGMENTATION_EXT");
			add_cher = err_code;
		}
		if (err == VK_ERROR_NOT_PERMITTED_EXT)
		{
			std::string err_code("VK_ERROR_NOT_PERMITTED_EXT");
			add_cher = err_code;
		}
		if (err == VK_ERROR_OUT_OF_POOL_MEMORY_KHR)
		{
			std::string err_code("VK_ERROR_OUT_OF_POOL_MEMORY_KHR");
			add_cher = err_code;
		}
		if (err == VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR)
		{
			std::string err_code("VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR");
			add_cher = err_code;
		}
		if (err == VK_RESULT_BEGIN_RANGE)
		{
			std::string err_code("VK_RESULT_BEGIN_RANGE");
			add_cher = err_code;
		}
		if (err == VK_RESULT_END_RANGE)
		{
			std::string err_code("VK_RESULT_END_RANGE");
			add_cher = err_code;
		}
		if (err == VK_RESULT_RANGE_SIZE)
		{
			std::string err_code("VK_RESULT_RANGE_SIZE");
			add_cher = err_code;
		}
		if (err == VK_RESULT_MAX_ENUM)
		{
			std::string err_code("VK_RESULT_MAX_ENUM");
			add_cher = err_code;
		}
		if (err != VK_SUCCESS)
		{
			std::string err_code("なにか良くなかった");
			add_cher = err_code;
		}

		std::string out_string;
		out_string = in_cher + end_chsr;
		out_string = out_string + add_cher;
		MessageBox(NULL, out_string.data(), "Errorメッセージ", MB_OK);
		//throw out_string.data();
		exit(-1);
	}
}

void vulkan::Error::Window(bool Check, const char * out_cher)
{
	if (Check)
	{	
		MessageBox(NULL, out_cher, "boolでのErrorメッセージ", MB_OK);
		exit(-1);
	}
}
