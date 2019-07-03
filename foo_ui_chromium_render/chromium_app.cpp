#include "stdafx.h"
#include "chromium_app.h"

CefRefPtr<CefRenderProcessHandler> ChromiumApp::GetRenderProcessHandler() {
	return this;
}

bool ChromiumApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) {
	return this->message_router->OnProcessMessageReceived(browser, source_process, message);
}

void ChromiumApp::OnWebKitInitialized() {
	// Initialize message router
	CefMessageRouterConfig config;
	this->message_router = CefMessageRouterRendererSide::Create(config);
	// Register extension
	this->register_extension();
}

void ChromiumApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
	this->message_router->OnContextCreated(browser, frame, context);
}

void ChromiumApp::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
	this->message_router->OnContextReleased(browser, frame, context);
}

void ChromiumApp::register_extension() {
	// Load extension
	HRSRC hrsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_JS_API), RT_RCDATA);
	HGLOBAL hglobal = LoadResource(NULL, hrsrc);
	std::string extensionCode(reinterpret_cast<char *>(LockResource(hglobal)), SizeofResource(NULL, hrsrc));
	CefRegisterExtension(FOO_UI_CEF_EXTENSION_NAME, extensionCode, NULL);
}