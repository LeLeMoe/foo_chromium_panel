#include "../stdafx.h"

CefRefPtr<CefRenderProcessHandler> ChromiumApp::GetRenderProcessHandler() {
	return this;
}

void ChromiumApp::OnWebKitInitialized() {
	// Register extension
	HRSRC hrsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_JS_API), RT_RCDATA);
	HGLOBAL hglobal = LoadResource(NULL, hrsrc);
	std::string extensionCode(reinterpret_cast<char*>(LockResource(hglobal)), SizeofResource(NULL, hrsrc));
	CefRegisterExtension("v8/foo_ui_chromium_api", extensionCode, NULL);
}