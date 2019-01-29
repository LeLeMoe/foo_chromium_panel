#include "stdafx.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// Create pipe
	WaitNamedPipe(FOO_UI_CHROMIUM_PIPE_NAME, NMPWAIT_WAIT_FOREVER);
	HANDLE pipe_handle = CreateFile(FOO_UI_CHROMIUM_PIPE_NAME, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
	if(pipe_handle == INVALID_HANDLE_VALUE) {
		MessageBox(nullptr, FOO_UI_CHROMIUM_MSGBOX_TITLE, FOO_UI_CHROMIUM_MSGBOX_PIPE_FAILED, MB_OK | MB_ICONEXCLAMATION);
		return 1;
	}
	DWORD pipe_mode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	if(SetNamedPipeHandleState(pipe_handle, &pipe_mode, nullptr, nullptr) == false) {
		MessageBox(nullptr, FOO_UI_CHROMIUM_MSGBOX_TITLE, FOO_UI_CHROMIUM_MSGBOX_PIPE_FAILED, MB_OK | MB_ICONEXCLAMATION);
		return 1;
	}
	// Initialize cef3
	CefMainArgs main_args(hInstance);
	// Messgae loop
	while(1);
	return 0;
}