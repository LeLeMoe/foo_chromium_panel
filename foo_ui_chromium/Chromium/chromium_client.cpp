#include "../stdafx.h"

ChromiumClient::ChromiumClient() : browser(nullptr) {}

void ChromiumClient::destroy() {
	this->browser->GetHost()->CloseBrowser(false);
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
	this->browser->GetHost()->SetZoomLevel(3.0f);
}

bool ChromiumClient::DoClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	return false;
}