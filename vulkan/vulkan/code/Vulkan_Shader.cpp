#ifdef DEBUG

#endif // DEBUG
#include "vulkan.h"
#include <string>
#include <iostream>


#include <iostream>
#include <fstream>
using namespace std;
/* コンパイルできないときは上の３行を
#include <iostream.h>
#include <fstream.h>
に変えてみてください。*/


std::vector<char> vulkan::Resources::Shader::Load(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open()) 
	{
		throw std::runtime_error("failed to open file!");
	}
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

void vulkan::Resources::Shader::Create(Shader * out_Shader, const char *vertShaderText, const char *fragShaderText, data::Device* in_Device)
{
	out_Shader = out_Shader;
	vertShaderText = vertShaderText;
	fragShaderText = fragShaderText;
	in_Device = in_Device;

	if (!(vertShaderText || fragShaderText)) return;

	std::vector<char> vtx_spv;
	std::vector<char> frag_spv;
	vtx_spv = Load(vertShaderText);
	frag_spv = Load(fragShaderText);

	VkShaderModuleCreateInfo moduleCreateInfo;
	
	out_Shader->shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	out_Shader->shaderStages[0].pNext = NULL;
	out_Shader->shaderStages[0].pSpecializationInfo = NULL;
	out_Shader->shaderStages[0].flags = 0;
	out_Shader->shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	out_Shader->shaderStages[0].pName = "main";
	moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	moduleCreateInfo.pNext = NULL;
	moduleCreateInfo.flags = 0;
	moduleCreateInfo.codeSize = vtx_spv.size();
	moduleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(vtx_spv.data());
	vulkan::Error::Window(vkCreateShaderModule(in_Device->device, &moduleCreateInfo, NULL, &out_Shader->shaderStages[0].module),"頂点Shaderの作成に失敗しました");

	out_Shader->shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	out_Shader->shaderStages[1].pNext = NULL;
	out_Shader->shaderStages[1].pSpecializationInfo = NULL;
	out_Shader->shaderStages[1].flags = 0;
	out_Shader->shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	out_Shader->shaderStages[1].pName = "main";
	moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	moduleCreateInfo.pNext = NULL;
	moduleCreateInfo.flags = 0;
	moduleCreateInfo.codeSize = frag_spv.size();
	moduleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(frag_spv.data());
	vulkan::Error::Window(vkCreateShaderModule(in_Device->device, &moduleCreateInfo, NULL, &out_Shader->shaderStages[1].module),"フラグShaderの作成に失敗しました");	
}
void vulkan::Resources::Shader::Destroy(data::Device* in_Device)
{
	vkDestroyShaderModule(in_Device->device, shaderStages[0].module, NULL);
	vkDestroyShaderModule(in_Device->device, shaderStages[1].module, NULL);
}
