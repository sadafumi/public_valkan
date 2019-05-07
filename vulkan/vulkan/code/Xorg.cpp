#include "Xorg.h"

#if defined(VK_USE_PLATFORM_XCB_KHR)
void Xorg::Create(Window_Data *)
{
	assert(info.width > 0);
	assert(info.height > 0);

	uint32_t value_mask, value_list[32];

	info.window = xcb_generate_id(info.connection);

	value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	value_list[0] = info.screen->black_pixel;
	value_list[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE;

	xcb_create_window(info.connection, XCB_COPY_FROM_PARENT, info.window, info.screen->root, 0, 0, info.width, info.height, 0,
		XCB_WINDOW_CLASS_INPUT_OUTPUT, info.screen->root_visual, value_mask, value_list);

	/* Magic code that will send notification when window is destroyed */
	xcb_intern_atom_cookie_t cookie = xcb_intern_atom(info.connection, 1, 12, "WM_PROTOCOLS");
	xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(info.connection, cookie, 0);

	xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(info.connection, 0, 16, "WM_DELETE_WINDOW");
	info.atom_wm_delete_window = xcb_intern_atom_reply(info.connection, cookie2, 0);

	xcb_change_property(info.connection, XCB_PROP_MODE_REPLACE, info.window, (*reply).atom, 4, 32, 1,
		&(*info.atom_wm_delete_window).atom);
	free(reply);

	xcb_map_window(info.connection, info.window);

	// Force the x/y coordinates to 100,100 results are identical in consecutive
	// runs
	const uint32_t coords[] = { 100, 100 };
	xcb_configure_window(info.connection, info.window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);
	xcb_flush(info.connection);

	xcb_generic_event_t *e;
	while ((e = xcb_wait_for_event(info.connection))) {
		if ((e->response_type & ~0x80) == XCB_EXPOSE) break;
	}
}

void Xorg::Delete()
{
	vkDestroySurfaceKHR(info.inst, info.surface, NULL);
	xcb_destroy_window(info.connection, info.window);
	xcb_disconnect(info.connection);
}
#endif