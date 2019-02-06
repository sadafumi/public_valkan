#include "vulkan.h"

void vulkan::data::Scissor::Init(Utility::Int_Vec2 in_win)
{
	scissor.extent.width = in_win.x;
	scissor.extent.height = in_win.y;
	scissor.offset.x = 0;
	scissor.offset.y = 0;
}
void vulkan::data::Scissor::Set(Command_Buffer* in_cmd_buff)
{
	vkCmdSetScissor(in_cmd_buff->cmd_buff, 0, 1, &scissor);
}

