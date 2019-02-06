#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 uv;

layout(location = 0) out vec2 uv_out;
out gl_PerVertex { vec4 gl_Position; };

void main()
{
	gl_Position = pos;
	uv_out = uv;
}
