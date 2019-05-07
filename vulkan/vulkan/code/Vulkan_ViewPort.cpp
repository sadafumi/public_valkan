#include "vulkan_api.h"

void vulkan::data::ViewPort::Init(Utility::Int_Vec2 in_win)
{
	viewport.height = (float)in_win.y;
	viewport.width = (float)in_win.x;
	viewport.minDepth = (float)0.0f;
	viewport.maxDepth = (float)1.0f;
	viewport.x = 0;
	viewport.y = 0;
}
