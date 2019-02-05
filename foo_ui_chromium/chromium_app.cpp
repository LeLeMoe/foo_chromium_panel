#include "stdafx.h"
#include "chromium_app.h"
#include "helper.h"

pfc::list_t<HWND> ChromiumApp::window_list;

CefRefPtr<CefBrowserProcessHandler> ChromiumApp::GetBrowserProcessHandler() {
	return this;
}

void ChromiumApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();

}

void ChromiumApp::register_window(HWND handle) {
	window_list.add_item(handle);
}

void ChromiumApp::initialize_cef() {
	CefMainArgs main_args(core_api::get_my_instance());
	CefRefPtr<ChromiumApp> app(new ChromiumApp);
	CefSettings settings;
	CefString(&settings.browser_subprocess_path).FromASCII(core_api::get_my_render_path().c_str());
	CefInitialize(main_args, settings, app.get(), nullptr);
}

void ChromiumApp::do_message_loop_work() {
	CefDoMessageLoopWork();
}

void ChromiumApp::shutdown_cef() {
	CefShutdown();
}