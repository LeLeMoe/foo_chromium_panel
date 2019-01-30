#include "stdafx.h"

namespace core_api {
	pfc::string8 get_my_work_path() {
		pfc::string8 path(core_api::get_my_full_path());
		path.truncate_to_parent_path();
		return path;
	}
}