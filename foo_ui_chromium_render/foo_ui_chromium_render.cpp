#include "stdafx.h"
#include "distribute_pipe.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// Get name of message pipe from distribute pipe
	if(DistributePipe::connect() == false) {
		MessageBox(nullptr, FOO_UI_CHROMIUM_MSGBOX_PIPE_FAILED, FOO_UI_CHROMIUM_MSGBOX_TITLE, MB_OK | MB_ICONERROR);
		return 0;
	}
	std::string message_pipe_name = DistributePipe::get_message_pipe_name();
	if(message_pipe_name.empty() == true) {
		MessageBox(nullptr, FOO_UI_CHROMIUM_MSGBOX_PIPE_FAILED, FOO_UI_CHROMIUM_MSGBOX_TITLE, MB_OK | MB_ICONERROR);
		DistributePipe::connect();
		return 0;
	}
	DistributePipe::disconnect();
	// Connect message pipe
	// TODO
	// Initialize cef3
	CefMainArgs main_args(hInstance);
	// Messgae loop
	MessageBox(nullptr, L"WOW!", FOO_UI_CHROMIUM_MSGBOX_TITLE, MB_OK | MB_ICONERROR);
	return 0;
}