#include "stdafx.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	CefMainArgs main_args(hInstance);
	CefRefPtr<CefApp> app(new CefApp);
	return CefExecuteProcess(main_args, app.get());
}