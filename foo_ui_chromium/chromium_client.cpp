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

CefRefPtr<CefRequestHandler> ChromiumClient::GetRequestHandler() {
	return this;
}

bool ChromiumClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) {
	CEF_REQUIRE_UI_THREAD();
	return this->message_router->OnProcessMessageReceived(browser, source_process, message);
}

void ChromiumClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	browser_ins = browser;
	// Initialize message router when it is not created.
	if (this->message_router == nullptr) {
		CefMessageRouterConfig config;
		this->message_router = CefMessageRouterBrowserSide::Create(config);
		this->message_router->AddHandler(&this->message_handler, true);
	}
}

bool ChromiumClient::DoClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	return false;
}

void ChromiumClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	this->message_router->RemoveHandler(&this->message_handler);
	this->message_router = nullptr;
}

bool ChromiumClient::OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool user_gesture, bool is_redirect) {
	CEF_REQUIRE_UI_THREAD();
	this->message_router->OnBeforeBrowse(browser, frame);
	return false;
}

void ChromiumClient::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus status) {
	CEF_REQUIRE_UI_THREAD();
	this->message_router->OnRenderProcessTerminated(browser);
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