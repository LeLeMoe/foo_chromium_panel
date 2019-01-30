#include "stdafx.h"
#include "distribute_pipe.h"

HANDLE DistributePipe::pipe_handle;

bool DistributePipe::connect() {
	// Check pipe
	WaitNamedPipe(FOO_UI_CHROMIUM_DISTRIBUTE_PIPE_NAME, NMPWAIT_WAIT_FOREVER);
	// Connect pipe
	HANDLE pipe_handle = CreateFile(FOO_UI_CHROMIUM_DISTRIBUTE_PIPE_NAME, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
	if(pipe_handle == INVALID_HANDLE_VALUE) {
		return false;
	}
	// Set pipe mode
	DWORD pipe_mode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	if(SetNamedPipeHandleState(pipe_handle, &pipe_mode, nullptr, nullptr) == false) {
		return false;
	}
}

std::string DistributePipe::get_message_pipe_name() {
	if(pipe_handle == INVALID_HANDLE_VALUE) {
		return std::string();
	}
	// Request message pipe
	const char message = 0xFF;
	DWORD written;
	if(WriteFile(pipe_handle, &message, sizeof(char), &written, nullptr) == false) {
		return std::string();
	} else if(written != sizeof(char)) {
		return std::string();
	}
	// Recive data
	char *recive_data;
	if(ReadFile(pipe_handle, recive_data, 46 * sizeof(char), &written, nullptr) == false) {			// magic number 46: length of pipe name, for example, \\.\pipe\892C1736-C9E5-4FA9-BAA9-762C55D62D60
		return std::string();
	} else if(written != 46 * sizeof(char)) {
		return std::string();
	}
	return std::string(recive_data);
}

bool DistributePipe::disconnect() {
	CloseHandle(pipe_handle);
}