#pragma once
#include "Utility.h"
#ifdef _WIN32
#include <Windows.h>
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#include <linux/input.h>
#else

#endif  // _WIN32

class Window_Data
{
public:
#ifdef _WIN32
	HWND wind;
	HINSTANCE connect;
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	wl_display *display;
	wl_registry *registry;
	wl_compositor *compositor;
	wl_surface *window;
	wl_shell *shell;
	wl_shell_surface *shell_surface;
#else
	xcb_connection_t *connection;
	xcb_screen_t *screen;
	xcb_window_t window;
	xcb_intern_atom_reply_t *atom_wm_delete_window;
#endif  // _WIN32
	const int Screen_Width_Size = 1280;
	const int Screen_Hiegth_Size = 720;
	Utility::Int_Vec2 Get_Windows_Size();
};

