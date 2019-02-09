#pragma once
#include "chromium_browser_info.h"

class ChromiumClient : public CefClient, public CefLifeSpanHandler {
public:
	ChromiumClient(const BrowserInfo &info);
	~ChromiumClient() = default;

public:
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;

public:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

public:
	void resize_browser(unsigned int width, unsigned height);

public:
	static void close_all_browser();

private:
	static pfc::list_t<CefRefPtr<ChromiumClient>> client_list;
	static bool is_closed;
	CefRefPtr<CefBrowser> browser_ins;
	BrowserInfo browser_info;
	IMPLEMENT_REFCOUNTING(ChromiumClient);
};