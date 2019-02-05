#include "stdafx.h"
#include "chromium_app.h"

CefRefPtr<CefRenderProcessHandler> ChromiumApp::GetRenderProcessHandler() {
	return this;
}