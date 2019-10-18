#include "../stdafx.h"

ChromiumApp::ChromiumApp() : handle(NULL), url(), client(nullptr) {}

void ChromiumApp::init(HWND hwnd, pfc::string8 url) {
	this->handle = hwnd;
	this->url = url;
	this->client = CefRefPtr<ChromiumClient>(new ChromiumClient);
	CefEnableHighDPISupport();
	CefMainArgs main_args(core_api::get_my_instance());
	CefSettings settings;
	CefString(&settings.browser_subprocess_path).FromASCII(core_api::get_my_render_path().c_str());
	settings.no_sandbox = true;
	CefInitialize(main_args, settings, this, nullptr);
	this->timer_event = SetTimer(this->handle, 0, 5, NULL);
	this->register_message(WM_TIMER, this, &ChromiumApp::on_timer);
}

void ChromiumApp::resize_browser(unsigned int width, unsigned int height) {
	this->client->resize_browser(width, height);
}

void ChromiumApp::destroy() {
	this->client->destroy();
	KillTimer(NULL, this->timer_event);
	this->unregister_message(WM_TIMER);
	CefShutdown();
}

LRESULT ChromiumApp::on_timer(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	CefDoMessageLoopWork();
	return 0;
}

CefRefPtr<CefBrowserProcessHandler> ChromiumApp::GetBrowserProcessHandler() {
	return this;
}

void ChromiumApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();
	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;
	RECT rect;
	GetClientRect(this->handle, &rect);
	rect.right -= rect.left;
	rect.bottom -= rect.top;
	rect.top = 0;
	rect.left = 0;
	window_info.SetAsChild(this->handle, rect);
	CefBrowserHost::CreateBrowser(window_info, this->client, this->url.c_str(), browser_settings, nullptr, nullptr);
}