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
	bool DoClose(CefRefPtr<CefBrowser> browser) override;
	bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access) override;

private:
	CefRefPtr<CefBrowser> browser;
	IMPLEMENT_REFCOUNTING(ChromiumClient);
};