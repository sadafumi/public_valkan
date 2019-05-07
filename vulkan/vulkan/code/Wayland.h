#pragma once
#include "Utility.h"
#include "Window_Data.h"
#include <stdio.h>


#if defined(VK_USE_PLATFORM_WAYLAND_KHR)

class Wayland
{
public:
	void Create(Window_Data*);
	void Delete();
private:

};
#endif

