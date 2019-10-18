#include "../stdafx.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	SetProcessDPIAware();
	CefMainArgs main_args(hInstance);
	CefRefPtr<ChromiumApp> app(new ChromiumApp);
	return CefExecuteProcess(main_args, app, NULL);
}