#include "stdafx.h"
#include "preference_private.h"

namespace core_api {
	pfc::string8 get_my_work_path() {
		pfc::string8 path(core_api::get_my_full_path());
		path.truncate_to_parent_path();
		return path;
	}

	pfc::string8 get_my_render_path() {
		pfc::string8 work_path = get_my_work_path();
		work_path.add_string("\\");
		work_path.add_string(FOO_UI_CHROMIUM_SUB_FILENAME);
		return work_path;
	}

	pfc::string8 get_my_log_path() {
		pfc::string8 work_path = get_my_work_path();
		work_path.add_string("\\log.txt");
		return work_path;
	}

	pfc::string8 get_default_page_path() {
		pfc::string8 work_path = get_my_work_path();
		work_path.add_string("\\default\\index.html");
		return work_path;
	}
}

namespace window_control {
	void save_window_size(HWND handle) {
		RECT window_rect;
		if(GetWindowRect(handle, &window_rect) != FALSE) {
			cfg_window_x = window_rect.left;
			cfg_window_y = window_rect.top;
			cfg_window_width = window_rect.right - window_rect.left;
			cfg_window_height = window_rect.bottom - window_rect.top;
		}
	}

	void enable_window_size(HWND handle) {
		SetWindowPos(handle, NULL, cfg_window_x, cfg_window_y, cfg_window_width, cfg_window_height, NULL);
	}
}