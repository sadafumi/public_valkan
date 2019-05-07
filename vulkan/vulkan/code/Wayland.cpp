#include "Wayland.h"

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)

void Wayland::Create(Window_Data *)
{
	assert(info.width > 0);
	assert(info.height > 0);

	info.window = wl_compositor_create_surface(info.compositor);
	if (!info.window) {
		printf("Can not create wayland_surface from compositor!\n");
		fflush(stdout);
		exit(1);
	}

	info.shell_surface = wl_shell_get_shell_surface(info.shell, info.window);
	if (!info.shell_surface) {
		printf("Can not get shell_surface from wayland_surface!\n");
		fflush(stdout);
		exit(1);
	}

	wl_shell_surface_add_listener(info.shell_surface, &shell_surface_listener, &info);
	wl_shell_surface_set_toplevel(info.shell_surface);
}

void Wayland::Delete()
{
	wl_shell_surface_destroy(info.shell_surface);
	wl_surface_destroy(info.window);
	wl_shell_destroy(info.shell);
	wl_compositor_destroy(info.compositor);
	wl_registry_destroy(info.registry);
	wl_display_disconnect(info.display);
}
#endif