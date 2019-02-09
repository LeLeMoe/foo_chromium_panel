#pragma once

class ChromiumApp;
class ChromiumClient;

struct BrowserInfo {
public:
	HWND parent_window;
	pfc::string8 url;

private:
	friend ChromiumApp;

private:
	CefRefPtr<ChromiumClient> client;
};