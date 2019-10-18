#pragma once

class ChromiumApp : public CefApp, public MessageObject, public CefBrowserProcessHandler {
public:
	ChromiumApp();
	~ChromiumApp() = default;

public:
	void init(HWND hwnd, pfc::string8 url);
	void resize_browser(unsigned int width, unsigned int height);
	void destroy();

public:
	LRESULT on_timer(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
	void OnContextInitialized() override;

private:
	HWND handle;
	pfc::string8 url;
	CefRefPtr<ChromiumClient> client;
	UINT timer_event;
	IMPLEMENT_REFCOUNTING(ChromiumApp);
};