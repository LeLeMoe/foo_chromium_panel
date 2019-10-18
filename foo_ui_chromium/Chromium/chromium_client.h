#pragma once

class ChromiumClient : public CefClient, public CefLifeSpanHandler {
public:
	ChromiumClient();
	~ChromiumClient() = default;

public:
	void destroy();
	void resize_browser(unsigned int width, unsigned int height);

public:
	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
	void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	bool ChromiumClient::DoClose(CefRefPtr<CefBrowser> browser) override;

private:
	CefRefPtr<CefBrowser> browser;
	IMPLEMENT_REFCOUNTING(ChromiumClient);
};