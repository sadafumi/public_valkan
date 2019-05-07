#include "Program_Loop.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <chrono>
#include <Thread>
#include "Window.h"

#ifdef _WIN32
void Program_Loop()
{
	Window wind;
	MSG msg;

	std::chrono::system_clock::time_point now, old;

	old = std::chrono::system_clock::now();
	wind.Init();
	float elapsed;
	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			elapsed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - old).count();
			if (elapsed * 60 >= 1000)
			{
				if (wind.Update())
				{
					break;
				}
				wind.Draw();
				old = now;
			}
		}
	}
	wind.Uninit();
}
#elif defined(__ANDROID__)
void Program_Loop()
{
	Window wind;

	std::chrono::system_clock::time_point now, old;

	old = std::chrono::system_clock::now();
	wind.Init();
	float elapsed;
	for (;;)
	{
		elapsed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - old).count();
		if (elapsed * 60 >= 1000)
		{
			if (wind.Update())
			{
				break;
			}
			wind.Draw();
			old = now;
		}
	}
	wind.Uninit();
}
#elif defined(VK_USE_PLATFORM_IOS_MVK)
void Program_Loop()
{
	Window wind;

	std::chrono::system_clock::time_point now, old;

	old = std::chrono::system_clock::now();
	wind.Init();
	float elapsed;
	for (;;)
	{
		elapsed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - old).count();
		if (elapsed * 60 >= 1000)
		{
			if (wind.Update())
			{
				break;
			}
			wind.Draw();
			old = now;
		}
	}
	wind.Uninit();
}
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
void Program_Loop()
{
	Window wind;

	std::chrono::system_clock::time_point now, old;

	old = std::chrono::system_clock::now();
	wind.Init();
	float elapsed;
	for (;;)
	{
		elapsed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - old).count();
		if (elapsed * 60 >= 1000)
		{
			if (wind.Update())
			{
				break;
			}
			wind.Draw();
			old = now;
		}
	}
	wind.Uninit();
}
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
void Program_Loop()
{
	Window wind;

	std::chrono::system_clock::time_point now, old;

	old = std::chrono::system_clock::now();
	wind.Init();
	float elapsed;
	for (;;)
	{
		elapsed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - old).count();
		if (elapsed * 60 >= 1000)
		{
			if (wind.Update())
			{
				break;
			}
			wind.Draw();
			old = now;
		}
	}
	wind.Uninit();
}
#elif defined(VK_USE_PLATFORM_XCB_KHR)
void Program_Loop()
{
	Window wind;
	
	std::chrono::system_clock::time_point now, old;

	old = std::chrono::system_clock::now();
	wind.Init();
	float elapsed;
	for (;;)
	{
		elapsed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - old).count();
		if (elapsed * 60 >= 1000)
		{
			if (wind.Update())
			{
				break;
			}
			wind.Draw();
			old = now;
		}
	}
	wind.Uninit();
}
#endif 
