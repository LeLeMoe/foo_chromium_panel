#include "stdafx.h"
#include "chromium_app.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	CefMainArgs main_args(hInstance);
	CefRefPtr<ChromiumApp> app(new ChromiumApp);
	return CefExecuteProcess(main_args, app, NULL);
}