#include "stdafx.h"
#include "helper.h"
#include "message_object.h"
#include "chromium_app.h"
#include "chromium_client.h"
#include "preference_main.h"
#include "preference_taskbar.h"
#include "preference_private.h"
#include "taskbar_icon.h"

class UserInterfaceChromium : public user_interface_v2, public MessageObject {
public:
	UserInterfaceChromium() = default;
	~UserInterfaceChromium() = default;

public:
	const char *get_name() override {
		return FOO_UI_CHROMIUM_NAME;
	}
	HWND init(HookProc_t hook) override {
		// hook_callback = hook;
		MessageObject::set_hook_function(hook);
		if(on_initialize() == false) {
			return nullptr;
		} else {
			return window_handle;
		}
 	}
	void activate() override {
		// TODO
	}
	void hide() override {
		// TODO
	}
	void shutdown() override {
		on_shutdown();
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

public:
	LRESULT process_destroy(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		standard_commands::main_exit();
		return 0;
	}
	LRESULT process_size(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (chromium_client != nullptr) {
			chromium_client->resize_browser(LOWORD(lParam), HIWORD(lParam));
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	LRESULT process_syscommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (wParam) {
		case SC_MINIMIZE:
			if (cfg_window_is_max == false) {
				window_control::save_window_size(hwnd);
			}
			if (cfg_min_to_icon == true) {
				ShowWindow(hwnd, SW_MINIMIZE);
				taskbar_icon.disable_icon();
				if (cfg_al_show_icon == false) {
					taskbar_icon.show();
				}
			}
			break;
		case SC_MAXIMIZE:
			cfg_window_is_max = true;
			break;
		case SC_RESTORE:
			cfg_window_is_max = false;
			break;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

private:
	bool on_initialize() {
		// Register class
		WNDCLASS wc = {};
		wc.hInstance = core_api::get_my_instance();
		wc.hIcon = ui_control::get()->get_main_icon();
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
		wc.lpszClassName = FOO_UI_CHROMIUM_WINDOW_CLASS;
		wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
		// wc.lpfnWndProc = message_process;
		wc.lpfnWndProc = MessageObject::message_process;
		if(RegisterClass(&wc) == false) {
			return false;
		}
		// Register message
		this->register_message(WM_DESTROY, this, &UserInterfaceChromium::process_destroy);
		this->register_message(WM_SIZE, this, &UserInterfaceChromium::process_size);
		this->register_message(WM_SYSCOMMAND, this, &UserInterfaceChromium::process_syscommand);
		// Create window
		auto window_style = WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_THICKFRAME;
		window_handle = CreateWindowEx(WS_EX_APPWINDOW, FOO_UI_CHROMIUM_WINDOW_CLASS, FOO_UI_CHROMIUM_WINDOW_NAME, window_style, cfg_window_x, cfg_window_y, cfg_window_width, cfg_window_height, nullptr, nullptr, core_api::get_my_instance(), nullptr);
		if(window_handle == nullptr) {
			UnregisterClass(FOO_UI_CHROMIUM_WINDOW_CLASS, core_api::get_my_instance());
			return false;
		}
		// Register window to cef
		BrowserInfo info;
		info.parent_window = window_handle;
		info.url = cfg_main_url;
		chromium_client = ChromiumApp::register_window(info);
		// Initialize cef
		if(ChromiumApp::initialize_cef() == false) {
			DestroyWindow(window_handle);
			this->unregister_message(WM_DESTROY);
			this->unregister_message(WM_SIZE);
			this->unregister_message(WM_SYSCOMMAND);
			UnregisterClass(FOO_UI_CHROMIUM_WINDOW_CLASS, core_api::get_my_instance());
			return false;
		}
		// Show window
		ShowWindow(window_handle, SW_SHOWNORMAL);
		UpdateWindow(window_handle);
		// Initialize taskbar icon
		taskbar_icon.initialize(window_handle);
		if(cfg_al_show_icon == true) {
			taskbar_icon.show();
		}
		return true;
	}
	void on_shutdown() {
		if(window_handle != nullptr) {
			// Delete taskbar icon
			taskbar_icon.destroy();
			// hide window
			ShowWindow(window_handle, SW_MINIMIZE);
			// Close cef
			ChromiumApp::shutdown_cef();
			// Unregister message
			this->unregister_message(WM_DESTROY);
			this->unregister_message(WM_SIZE);
			this->unregister_message(WM_SYSCOMMAND);
			// Unregister class
			UnregisterClass(FOO_UI_CHROMIUM_WINDOW_CLASS, core_api::get_my_instance());
		}
	}

private:
	static HookProc_t hook_callback;
	static CefRefPtr<ChromiumClient> chromium_client;
	HWND window_handle;
	TaskbarIcon taskbar_icon;
};

user_interface_v2::HookProc_t UserInterfaceChromium::hook_callback;
CefRefPtr<ChromiumClient> UserInterfaceChromium::chromium_client = nullptr;
static user_interface_factory<UserInterfaceChromium> user_interface_chromium;