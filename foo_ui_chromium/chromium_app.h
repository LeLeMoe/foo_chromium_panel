#pragma once
#include "chromium_client.h"
#include "chromium_browser_info.h"

class ChromiumApp : public CefApp, public CefBrowserProcessHandler {
public:
	ChromiumApp() = default;

public:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
	
public:
	virtual void OnContextInitialized() override;

public:
	static CefRefPtr<ChromiumClient> register_window(BrowserInfo &info);
	static bool initialize_cef();
	static void shutdown_cef();

public:
	static void CALLBACK timer_callback(HWND arg1, UINT arg2, UINT_PTR arg3, DWORD arg4);

private:
	static bool is_initialize_cef;
	static UINT timer_event;
	static pfc::list_t<BrowserInfo> window_list;
	IMPLEMENT_REFCOUNTING(ChromiumApp);
};