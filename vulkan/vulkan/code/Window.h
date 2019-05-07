//========================================================================
//	maked by sadafumi 
//	2019/2/7
//========================================================================
#pragma once

#include <stdio.h>
#include "Utility.h"
#include "Windows_API.h"
#include "Wayland.h"
#include "Xorg.h"
#include "Window_Data.h"
#include "Graphics.h"

#ifdef _WIN32
#include <Windows.h>
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#include <linux/input.h>
#else

#endif  // _WIN32
class Window
{
public:
	Window();
	~Window();
	void Init();
	void Uninit();
	bool Update();
	void Draw();
private:
	//Ç±Ç±Ç©ÇÁâ∫ÇÕProjectÇ≤Ç∆Ç…ïœÇ¶ÇÈÇÃÇ‡Ç≈Ç»Ç¢Ç∆â¥Ç™ç¢ÇÈ
	Graphics Test;
	Window_Data data;
#ifdef _WIN32
	Windows_API wind;
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	Wayland wind;
#else

#endif  // _WIN32

};
