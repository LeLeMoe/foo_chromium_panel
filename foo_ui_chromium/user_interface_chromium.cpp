#include "stdafx.h"
#include "helper.h"

class UserInterfaceChromium : public user_interface_v2 {
public:
	UserInterfaceChromium() = default;
	~UserInterfaceChromium() = default;

public:
	const char *get_name() override {
		return FOO_UI_CHROMIUM_NAME;
	}
	HWND init(HookProc_t hook) override {
		hook_callback = hook;
		if(create_window(hook) == false) {
			MessageBox(nullptr, FOO_UI_CHROMIUM_MSGBOX_WINDOW_FAILED, FOO_UI_CHROMIUM_MSGBOX_TITLE, MB_OK | MB_ICONERROR);
			return nullptr;
		}
		if(create_pipe() == false) {
			MessageBox(nullptr, FOO_UI_CHROMIUM_MSGBOX_PIPE_FAILED, FOO_UI_CHROMIUM_MSGBOX_TITLE, MB_OK | MB_ICONERROR);
			return nullptr;
		}
		return window_handle;
	}
	void activate() override {
		// TODO
	}
	void hide() override {
		// TODO
	}
	void shutdown() override {
		close_pipe();
	}
	bool is_visible() override {
		//TODO
		return true;
	}
	GUID get_guid() override {
		return GUID(GUID_USER_INTERFACE);
	}
	void override_statusbar_text(const char * p_text) override {
		// TODO
	}
	void revert_statusbar_text() override {
		// TODO
	}
	void show_now_playing() override {
		// TODO
	}
	bool query_capability(const GUID & cap) override {
		return false;
	}

private:
	bool create_window(HookProc_t hook) {
		// Register class
		WNDCLASS wc = {};
		wc.hInstance = core_api::get_my_instance();
		wc.hIcon = ui_control::get()->get_main_icon();
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
		wc.lpszClassName = FOO_UI_CHROMIUM_WINDOW_CLASS;
		wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
		if(RegisterClass(&wc) == false) {
			return false;
		}
		// Create window

		return true;
	}
	bool create_pipe() {
		// Create pipe
		SECURITY_ATTRIBUTES sa = {};
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = nullptr;
		sa.bInheritHandle = true;
		pipe_handle = CreateNamedPipe(FOO_UI_CHROMIUM_PIPE_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_WAIT_FOREVER, &sa);
		if(pipe_handle == INVALID_HANDLE_VALUE) {
			return false;
		}
		// Create process
		STARTUPINFOA si = {};
		PROCESS_INFORMATION pi = {};
		pfc::string8 path = core_api::get_my_work_path();
		pfc::string8 command_line(path);
		command_line.add_string("\\");
		command_line.add_string(FOO_UI_CHROMIUM_SUB_FILENAME);
		if(CreateProcessA(command_line.get_ptr(), nullptr, &sa, &sa, true, 0, nullptr, path.get_ptr(), &si, &pi) == false) {
			return false;
		}
		// Connect pipe
		is_connect = ConnectNamedPipe(pipe_handle, nullptr);
		if(is_connect == false) {
			return false;
		}
		return true;
	}
	void close_window() {
		if(window_handle != nullptr) {
			DestroyWindow(window_handle);
			UnregisterClass(FOO_UI_CHROMIUM_WINDOW_CLASS, core_api::get_my_instance());
		}
	}
	void close_pipe() {
		if(is_connect == true) {
			DisconnectNamedPipe(pipe_handle);
			CloseHandle(pipe_handle);
		} else if(pipe_handle != INVALID_HANDLE_VALUE) {
			CloseHandle(pipe_handle);
		}
	}

private:
	HookProc_t hook_callback;
	HWND window_handle;
	HANDLE pipe_handle;
	bool is_connect;
};

static user_interface_factory<UserInterfaceChromium> user_interface_chromium;