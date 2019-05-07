#include "vulkan_api.h"

void vulkan::data::Scissor::Init(Utility::Int_Vec2 in_win)
{
	scissor.extent.width = in_win.x;
	scissor.extent.height = in_win.y;
	scissor.offset.x = 0;
	scissor.offset.y = 0;
}
