#include "stdafx.h"
#include "chromium_client.h"

pfc::list_t<CefRefPtr<ChromiumClient>> ChromiumClient::client_list;
bool ChromiumClient::is_closed = false;

ChromiumClient::ChromiumClient(const BrowserInfo &info) : browser_info(info), browser_ins(nullptr) {
	client_list.add_item(this);
}

CefRefPtr<CefLifeSpanHandler> ChromiumClient::GetLifeSpanHandler() {
	return this;
}

void ChromiumClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	browser_ins = browser;
}

bool ChromiumClient::DoClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	return false;
}

void ChromiumClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
}

void ChromiumClient::resize_browser(unsigned int width, unsigned height) {
	if(this->browser_ins != nullptr) {
		SetWindowPos(browser_ins->GetHost()->GetWindowHandle(), nullptr, 0, 0, width, height, NULL);
	}
}

void ChromiumClient::close_all_browser() {
	if(is_closed == false) {
		for(size_t i = 0; i < client_list.get_count(); ++i) {
			client_list.get_item(i)->browser_ins->GetHost()->CloseBrowser(false);
		}
		is_closed = true;
	}
}