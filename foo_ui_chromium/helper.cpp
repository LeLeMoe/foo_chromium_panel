#include "stdafx.h"

namespace core_api {
	pfc::string8 get_my_work_path() {
		pfc::string8 path(core_api::get_my_full_path());
		path.truncate_to_parent_path();
		return path;
	}

	pfc::string get_my_render_path() {
		pfc::string8 work_path = get_my_work_path();
		work_path.add_string("/");
		work_path.add_string(FOO_UI_CHROMIUM_SUB_FILENAME);
		return work_path;
	}
}