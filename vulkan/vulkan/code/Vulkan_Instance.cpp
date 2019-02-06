#include "vulkan.h"
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

void vulkan::data::Instance::Init()
{
	const VkApplicationInfo app_info =
	{
		VK_STRUCTURE_TYPE_APPLICATION_INFO, //sType
		NULL,//pNext
		"Test1",//�A�v���̖��O
		0,//�A�v���̃o�[�W����
		"Test1",//�A�v�������G���W����*�Ȃ��̂ŃA�v����
		0,//�A�v���쐬�Ɏg���G���W���̃o�[�W����
		VK_API_VERSION_1_0 //�A�v���Ɏg�p����Vulkan�̃o�[�W����
	};
	std::vector<const char *> instance_layer_names;
	std::vector<const char *> instance_extension_names;
	instance_layer_names.push_back("VK_LAYER_LUNARG_standard_validation");

	instance_extension_names.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	instance_extension_names.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	//instance_extension_names.push_back(VK_EXT_DEBUG_REPORT_SPEC_VERSION);
	instance_extension_names.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

	VkInstanceCreateInfo inst_info;
	inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_info.pNext = NULL;
	inst_info.flags = 0;
	inst_info.pApplicationInfo = &app_info;
	inst_info.enabledLayerCount = (uint32_t)instance_layer_names.size();
	inst_info.ppEnabledLayerNames = instance_layer_names.size() ? instance_layer_names.data() : NULL;
	inst_info.enabledExtensionCount = (uint32_t)instance_extension_names.size();
	inst_info.ppEnabledExtensionNames = instance_extension_names.data();
	//���C�����g���@�\���g��Ȃ��ꍇ��0��ݒ�

	//��������NULL�Ȃ̂̓������A���P�[�^���g�p���Ȃ�����
	vulkan::Error::Window(vkCreateInstance(&inst_info, NULL, &instance),"Instance�����G���[");
}

void vulkan::data::Instance::Uninit()
{
	vkDestroyInstance(instance, NULL);
}
