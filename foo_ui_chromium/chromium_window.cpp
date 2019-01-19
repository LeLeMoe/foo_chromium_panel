#include "stdafx.h"
#include "chromium_window.h"
#include <include/cef_app.h>
#include <include/internal/cef_win.h>

ChromiumWindow ChromiumWindow::chromium_wiundow;

HWND ChromiumWindow::initialize(user_interface::HookProc_t hook) {
	// Enable high dpi support
	CefEnableHighDPISupport();
	// Set main args
	CefMainArgs main_args(core_api::get_my_instance());

	return nullptr;
}