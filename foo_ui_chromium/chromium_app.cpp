#include "stdafx.h"
#include "chromium_app.h"
#include "chromium_client.h"
#include "helper.h"

UINT ChromiumApp::timer_event = 0;
bool ChromiumApp::is_initialize_cef = false;
pfc::list_t<BrowserInfo> ChromiumApp::window_list;

CefRefPtr<CefBrowserProcessHandler> ChromiumApp::GetBrowserProcessHandler() {
	return this;
}

void ChromiumApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();
	for(size_t i = 0; i < window_list.get_count(); ++i) {
		BrowserInfo item;
		window_list.get_item_ex(item, i);
		// Browser settings
		CefBrowserSettings browser_settings;
		// Window info
		CefWindowInfo window_info;
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.right = 1200;
		rect.bottom = 800;
		window_info.SetAsChild(item.parent_window, rect);
		CefBrowserHost::CreateBrowser(window_info, item.client, item.url.c_str(), browser_settings, nullptr);
	}
	window_list.remove_all();
}

CefRefPtr<ChromiumClient> ChromiumApp::register_window(BrowserInfo &info) {
	info.client = CefRefPtr<ChromiumClient>(new ChromiumClient(info));
	window_list.add_item(info);
	return info.client;
}

bool ChromiumApp::initialize_cef() {
	timer_event = SetTimer(nullptr, 0, 2, timer_callback);
	if(timer_event == 0) {
		return false;
	} else {
		return true;
	}
}

void ChromiumApp::shutdown_cef() {
	// ChromiumClient::close_all_browser();
	KillTimer(nullptr, timer_event);
	CefShutdown();
}

void CALLBACK ChromiumApp::timer_callback(HWND arg1, UINT arg2, UINT_PTR arg3, DWORD arg4) {
	if(is_initialize_cef == true) {
		CefDoMessageLoopWork();
	} else if(core_api::is_initializing() == false) {
		// Enable highr DPI support
		CefEnableHighDPISupport();
		// Set main args
		CefMainArgs main_args(core_api::get_my_instance());
		// Create cef app
		CefRefPtr<ChromiumApp> app(new ChromiumApp);
		// Cef setting
		CefSettings settings;
		CefString(&settings.browser_subprocess_path).FromASCII(core_api::get_my_render_path().c_str());
		CefString(&settings.log_file).FromASCII(core_api::get_my_log_path().c_str());
		settings.no_sandbox = true;
		settings.ignore_certificate_errors = true;
		// Initialize cef
		CefInitialize(main_args, settings, app, nullptr);
		is_initialize_cef = true;
	}
}