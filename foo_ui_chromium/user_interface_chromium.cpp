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
		// Create window
		if(create_window() == false) {
			MessageBox(nullptr, FOO_UI_CHROMIUM_MSGBOX_WINDOW_FAILED, FOO_UI_CHROMIUM_MSGBOX_TITLE, MB_OK | MB_ICONERROR);
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
		close_window();
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
	bool create_window() {
		// Register class
		WNDCLASS wc = {};
		wc.hInstance = core_api::get_my_instance();
		wc.hIcon = ui_control::get()->get_main_icon();
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
		wc.lpszClassName = FOO_UI_CHROMIUM_WINDOW_CLASS;
		wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
		wc.lpfnWndProc = message_process;
		if(RegisterClass(&wc) == false) {
			return false;
		}
		// Create window
		auto window_style = WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN	| WS_CLIPSIBLINGS | WS_THICKFRAME;
		window_handle = CreateWindow(FOO_UI_CHROMIUM_WINDOW_CLASS, FOO_UI_CHROMIUM_WINDOW_NAME, window_style, CW_USEDEFAULT, CW_USEDEFAULT, 200, 200, nullptr, nullptr, core_api::get_my_instance(), nullptr);
		if(window_handle == nullptr) {
			UnregisterClass(FOO_UI_CHROMIUM_WINDOW_CLASS, core_api::get_my_instance());
			return false;
		}
		ShowWindow(window_handle, SW_SHOWNORMAL);
		UpdateWindow(window_handle);
		return true;
	}
	void close_window() {
		if(window_handle != nullptr) {
			DestroyWindow(window_handle);
			UnregisterClass(FOO_UI_CHROMIUM_WINDOW_CLASS, core_api::get_my_instance());
		}
	}

private:
	static LRESULT CALLBACK message_process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		// Check 
		LRESULT return_value;
		if(hook_callback(hwnd, uMsg, wParam, lParam, &return_value) != 0) {
			return return_value;
		}
		// Process message
		switch(uMsg) {
		case WM_CLOSE:
			standard_commands::main_exit();
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

private:
	static HookProc_t hook_callback;
	HWND window_handle;
};

user_interface_v2::HookProc_t UserInterfaceChromium::hook_callback;
static user_interface_factory<UserInterfaceChromium> user_interface_chromium;