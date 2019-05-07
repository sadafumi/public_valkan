#include "vulkan_api.h"
//
vulkan::Resources::Vertex::Vertex(Utility::Vec4 in_pos, Utility::Vec2 in_UV)
{
	this->Pos = in_pos;
	this->UV = in_UV;
}
//vulkan::Resources::Vertex::Vertex(Utility::Vec4 in_Pos, Utility::Vec4 in_Color)
//{
//	this->Pos = in_Pos;
//	this->color = in_Color;
//}
//vulkan::Resources::Vertex::Vertex(Utility::Vec2 in_Pos, Utility::Vec4 in_Color)
//{
//	this->Pos = in_Pos;
//	this->color = in_Color;
//}
//vulkan::Resources::Vertex::Vertex(Utility::Vec3 in_Pos, Utility::Vec4 in_Color)
//{
//	this->Pos = in_Pos;
//	this->color = in_Color;
//}
