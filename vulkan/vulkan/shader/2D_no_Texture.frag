#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location = 0) in vec4 color;
layout(location = 0) out vec4 color_out;

void main()
{
	color_out = color; 
	//color_out = vec4(1.0f,1.0f,1.0f,1.0f); 
}
