#pragma once

namespace core_api {
	pfc::string8 get_my_work_path();
	pfc::string8 get_my_render_path();
	pfc::string8 get_my_log_path();
	pfc::string8 get_default_page_path();
}

namespace window_control {
	void save_window_size(HWND handle);
	void enable_window_size(HWND handle);
}