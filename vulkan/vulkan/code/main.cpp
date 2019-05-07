#include "Program_Loop.h"

#ifdef _WIN32
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#endif  // _WIN32
#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "winmm.lib")
int main()
{	
	Program_Loop();
}

#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#endif  // _WIN32
