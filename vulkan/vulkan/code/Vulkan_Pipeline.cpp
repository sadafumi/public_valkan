#include "vulkan.h"


void vulkan::data::Pipeline_cache::Init(Device* in_Device)
{
	VkPipelineCacheCreateInfo pipelineCache_info;
	pipelineCache_info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
	pipelineCache_info.pNext = NULL;
	pipelineCache_info.initialDataSize = 0;
	pipelineCache_info.pInitialData = NULL;
	pipelineCache_info.flags = 0;
	vulkan::Error::Window(vkCreatePipelineCache(in_Device->device, &pipelineCache_info, NULL, &this->pipelineCache), "パイプラインキャッシュの作成に失敗");
}

void vulkan::data::Pipeline_cache::Uninit(Device* in_Device)
{
	vkDestroyPipelineCache(in_Device->device, this->pipelineCache, NULL);
}

void vulkan::data::Pipeline::Init(Device* in_Device, ViewPort* in_vp, Scissor* in_sc, Resources::Buffer* in_buff, Resources::Shader* in_Shader, Render_Pass* in_render_pass, Pipeline_cache* in_pipline_cache, bool Depth_flag, VkBool32 include_vi)
{
	VkDynamicState dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
	VkPipelineDynamicStateCreateInfo dynamicState = {};
	memset(dynamicStateEnables, 0, sizeof dynamicStateEnables);
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.pNext = NULL;
	dynamicState.pDynamicStates = dynamicStateEnables;
	dynamicState.dynamicStateCount = 0;

	VkPipelineVertexInputStateCreateInfo vertex;
	memset(&vertex, 0, sizeof(vertex));
	vertex.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	if (include_vi)
	{
		vertex.pNext = NULL;
		vertex.flags = 0;
		vertex.vertexBindingDescriptionCount = 1;
		vertex.pVertexBindingDescriptions = &in_buff->vi_binding;
		vertex.vertexAttributeDescriptionCount = 2;
		vertex.pVertexAttributeDescriptions = in_buff->vi_attribs;
	}
	
	VkPipelineInputAssemblyStateCreateInfo ia;
	ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	ia.pNext = NULL;
	ia.flags = 0;
	ia.primitiveRestartEnable = VK_FALSE;
	ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	VkPipelineRasterizationStateCreateInfo rs;
	rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rs.pNext = NULL;
	rs.flags = 0;
	rs.polygonMode = VK_POLYGON_MODE_FILL;
	rs.cullMode = VK_CULL_MODE_BACK_BIT;
	rs.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rs.depthClampEnable = VK_FALSE;
	rs.rasterizerDiscardEnable = VK_FALSE;
	rs.depthBiasEnable = VK_FALSE;
	rs.depthBiasConstantFactor = 0;
	rs.depthBiasClamp = 0;
	rs.depthBiasSlopeFactor = 0;
	rs.lineWidth = 1.0f;

	VkPipelineColorBlendAttachmentState att_state[1];
	att_state[0].colorWriteMask = 0xf;
	att_state[0].blendEnable = VK_FALSE;
	att_state[0].alphaBlendOp = VK_BLEND_OP_ADD;
	att_state[0].colorBlendOp = VK_BLEND_OP_ADD;
	att_state[0].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	att_state[0].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	att_state[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	att_state[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

	VkPipelineColorBlendStateCreateInfo cb;
	cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	cb.flags = 0;
	cb.pNext = NULL;
	cb.attachmentCount = 1;
	cb.pAttachments = att_state;
	cb.logicOpEnable = VK_FALSE;
	cb.logicOp = VK_LOGIC_OP_NO_OP;
	cb.blendConstants[0] = 1.0f;
	cb.blendConstants[1] = 1.0f;
	cb.blendConstants[2] = 1.0f;
	cb.blendConstants[3] = 1.0f;

	VkPipelineViewportStateCreateInfo vp = {};
	vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	vp.pNext = NULL;
	vp.flags = 0;
	vp.viewportCount = 1;
	dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
	vp.scissorCount = 1;
	dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;
	vp.pViewports = &in_vp->viewport;
	vp.pScissors = &in_sc->scissor;
	

	VkPipelineDepthStencilStateCreateInfo ds;
	ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	ds.pNext = NULL;
	ds.flags = 0;
	ds.depthTestEnable = Depth_flag;
	ds.depthWriteEnable = Depth_flag;
	ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	ds.depthBoundsTestEnable = VK_FALSE;
	ds.back.failOp = VK_STENCIL_OP_KEEP;
	ds.back.passOp = VK_STENCIL_OP_KEEP;
	ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
	ds.back.compareMask = 0;
	ds.back.reference = 0;
	ds.back.depthFailOp = VK_STENCIL_OP_KEEP;
	ds.back.writeMask = 0;
	ds.minDepthBounds = 0;
	ds.maxDepthBounds = 0;
	ds.stencilTestEnable = VK_FALSE;
	ds.stencilTestEnable = VK_FALSE;
	ds.front = ds.back;

	VkPipelineMultisampleStateCreateInfo ms;
	ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	ms.pNext = NULL;
	ms.flags = 0;
	ms.pSampleMask = NULL;
	ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	ms.sampleShadingEnable = VK_FALSE;
	ms.alphaToCoverageEnable = VK_FALSE;
	ms.alphaToOneEnable = VK_FALSE;
	ms.minSampleShading = 0.0;

	VkGraphicsPipelineCreateInfo pipeline_info;
	pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline_info.pNext = NULL;
	pipeline_info.flags = 0;
	pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
	pipeline_info.basePipelineIndex = 0;
	pipeline_info.pVertexInputState = &vertex;
	pipeline_info.pTessellationState = NULL;
	pipeline_info.stageCount = 2;
	pipeline_info.pStages = in_Shader->shaderStages;
	pipeline_info.pInputAssemblyState = &ia;
	pipeline_info.pViewportState = &vp;
	pipeline_info.pDepthStencilState = &ds;
	pipeline_info.pRasterizationState = &rs;
	pipeline_info.pMultisampleState = &ms;
	pipeline_info.pColorBlendState = &cb;
	pipeline_info.pDynamicState = &dynamicState;
	pipeline_info.layout = pipeline_layout;
	pipeline_info.renderPass = in_render_pass->RenderPass;
	pipeline_info.subpass = 0;

	vulkan::Error::Window(vkCreateGraphicsPipelines(in_Device->device, in_pipline_cache->pipelineCache, 1, &pipeline_info, NULL, &pipeline),"パイプラインの設定ができませんでした");
}

void vulkan::data::Pipeline::Create_Layout(Device * in_Device, Descriptor_Pool* in_dec)
{
	VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {};
	pPipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pPipelineLayoutCreateInfo.pNext = NULL;
	pPipelineLayoutCreateInfo.pushConstantRangeCount = 0;
	pPipelineLayoutCreateInfo.pPushConstantRanges = NULL;

	if (in_dec != NULL)
	{
		pPipelineLayoutCreateInfo.setLayoutCount = NUM_DESCRIPTOR_SETS;
		pPipelineLayoutCreateInfo.pSetLayouts = in_dec->desc_layout.data();
	}

	vulkan::Error::Window(vkCreatePipelineLayout(in_Device->device, &pPipelineLayoutCreateInfo, NULL, &this->pipeline_layout), "パイラインレイアウトの設定に失敗");
}

void vulkan::data::Pipeline::Uninit(Device* in_Device)
{
	vkDestroyPipeline(in_Device->device, this->pipeline, NULL);
	vkDestroyPipelineLayout(in_Device->device, this->pipeline_layout, NULL);
}

//Valid Usage
//If pipelineBindPoint is VK_PIPELINE_BIND_POINT_COMPUTE, the VkCommandPool that commandBuffer was allocated from must support compute operations
//If pipelineBindPoint is VK_PIPELINE_BIND_POINT_GRAPHICS, the VkCommandPool that commandBuffer was allocated from must support graphics operations
//If pipelineBindPoint is VK_PIPELINE_BIND_POINT_COMPUTE, pipeline must be a compute pipeline
//If pipelineBindPoint is VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline must be a graphics pipeline
//If the variable multisample rate feature is not supported, pipeline is a graphics pipeline, the current subpass has no attachments, and this is not the first call to this function with a graphics pipeline after transitioning to the current subpass, then the sample count specified by this pipeline must match that set in the previous pipeline
//If VkPhysicalDeviceSampleLocationsPropertiesEXT::variableSampleLocations is VK_FALSE, and pipeline is a graphics pipeline created with a VkPipelineSampleLocationsStateCreateInfoEXT structure having its sampleLocationsEnable member set to VK_TRUE but without VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT enabled then the current render pass instance must have been begun by specifying a VkRenderPassSampleLocationsBeginInfoEXT structure whose pPostSubpassSampleLocations member contains an element with a subpassIndex matching the current subpass index and the sampleLocationsInfo member of that element must match the sampleLocationsInfo specified in VkPipelineSampleLocationsStateCreateInfoEXT when the pipeline was created
//This command must not be recorded when transform feedback is active
//If pipelineBindPoint is VK_PIPELINE_BIND_POINT_RAY_TRACING_NV, the VkCommandPool that commandBuffer was allocated from must support compute operations
//If pipelineBindPoint is VK_PIPELINE_BIND_POINT_RAY_TRACING_NV, the pipeline must be a ray tracing pipeline
//Valid Usage(Implicit)
//commandBuffer must be a valid VkCommandBuffer handle
//pipelineBindPoint must be a valid VkPipelineBindPoint value
//pipeline must be a valid VkPipeline handle
//commandBuffer must be in the recording state
//The VkCommandPool that commandBuffer was allocated from must support graphics, or compute operations
//Both of commandBuffer, and pipeline must have been created, allocated, or retrieved from the same VkDevice
//Host Synchronization
//Host access to commandBuffer must be externally synchronized
//Host access to the VkCommandPool that commandBuffer was allocated from must be externally synchronized