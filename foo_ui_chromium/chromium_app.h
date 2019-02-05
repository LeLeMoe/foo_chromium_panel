#pragma once

class ChromiumApp : public CefApp, public CefBrowserProcessHandler {
public:
	ChromiumApp() = default;

public:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
	
public:
	virtual void OnContextInitialized() override;

public:
	static void register_window(HWND handle);
	static void initialize_cef();
	static void do_message_loop_work();
	static void shutdown_cef();

private:
	static pfc::list_t<HWND> window_list;
	IMPLEMENT_REFCOUNTING(ChromiumApp);
};