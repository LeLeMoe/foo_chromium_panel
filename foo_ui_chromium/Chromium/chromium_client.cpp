#include "../stdafx.h"

ChromiumClient::ChromiumClient() : browser(nullptr) {}

void ChromiumClient::destroy() {
	this->browser->GetHost()->CloseBrowser(true);
}

void ChromiumClient::resize_browser(unsigned int width, unsigned int height) {
	if (this->browser != nullptr) {
		MoveWindow(this->browser->GetHost()->GetWindowHandle(), 0, 0, width, height, true);
	}
}

CefRefPtr<CefLifeSpanHandler> ChromiumClient::GetLifeSpanHandler() {
	return this;
}

void ChromiumClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	this->browser = browser;
}

bool ChromiumClient::DoClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	return false;
}

bool ChromiumClient::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access) {
	this->browser->GetMainFrame()->LoadURL(target_url);
	return true;
}