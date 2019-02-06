
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (std140, binding = 0) uniform buf 
{
	mat4 mvp;
}	ubuf;

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 in_Color;
layout (location = 0) out vec4 out_Color;

void main() 
{
	out_Color = in_Color;
	gl_Position = ubuf.mvp * pos;
}
