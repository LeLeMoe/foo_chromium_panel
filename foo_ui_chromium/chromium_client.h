#pragma once
#include "chromium_browser_info.h"
#include "chromium_message_handler.h"

class ChromiumClient : public CefClient, public CefLifeSpanHandler, public CefRequestHandler {
public:
	ChromiumClient(const BrowserInfo &info);
	~ChromiumClient() = default;

public:
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override;
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;

public:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

public:
	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool user_gesture, bool is_redirect) override;
	virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus status) override;

public:
	void resize_browser(unsigned int width, unsigned height);

public:
	static void close_all_browser();

private:
	static pfc::list_t<CefRefPtr<ChromiumClient>> client_list;
	static bool is_closed;
	CefRefPtr<CefBrowser> browser_ins;
	CefRefPtr<CefMessageRouterBrowserSide> message_router;
	ChromiumMessageHandler message_handler;
	BrowserInfo browser_info;
	IMPLEMENT_REFCOUNTING(ChromiumClient);
};