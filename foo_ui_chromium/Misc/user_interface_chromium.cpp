#include "../stdafx.h"

static user_interface_factory<UserInterfaceChromium> user_interface_chromium;

UserInterfaceChromium::UserInterfaceChromium() : window_handle(NULL), notify_icon(), app(nullptr) {}

const char* UserInterfaceChromium::get_name() {
	return FOO_UI_CHROMIUM_NAME;
}

HWND UserInterfaceChromium::init(HookProc_t hook) {
	MessageObject::init(hook);
	return this->process_init();
}

void UserInterfaceChromium::activate() {
	// TODO
}

void UserInterfaceChromium::hide() {
	// TODO
}

void UserInterfaceChromium::shutdown() {
	this->process_shutdown();
}

bool UserInterfaceChromium::is_visible() {
	// TODO
	return true;
}

GUID UserInterfaceChromium::get_guid() {
	return GUID(FOO_UI_CHROMIUM_GUID_USER_INTERFACE);
}

void UserInterfaceChromium::override_statusbar_text(const char* p_text) {
	// TODO
}

void UserInterfaceChromium::revert_statusbar_text() {
	// TODO
}

void UserInterfaceChromium::show_now_playing() {
	// TODO
}

bool UserInterfaceChromium::query_capability(const GUID& cap) {
	return false;
}

void UserInterfaceChromium::save_window_size() {
	RECT window_rect;
	if (GetWindowRect(this->window_handle, &window_rect) != FALSE) {
		cfg_window_x = window_rect.left;
		cfg_window_y = window_rect.top;
		cfg_window_width = window_rect.right - window_rect.left;
		cfg_window_height = window_rect.bottom - window_rect.top;
	}
}

HWND UserInterfaceChromium::process_init() {
	// Register window class
	WNDCLASS wc = {};
	wc.hInstance = core_api::get_my_instance();
	wc.hIcon = ui_control::get()->get_main_icon();
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	wc.lpszClassName = FOO_UI_CHROMIUM_WINDOW_CLASS;
	wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = MessageObject::message_process;
	if (!RegisterClass(&wc)) {
		return NULL;
	}
	// Register message
	MessageObject::register_message(WM_CLOSE, this, &UserInterfaceChromium::on_close);
	MessageObject::register_message(WM_SIZE, this, &UserInterfaceChromium::on_size);
	MessageObject::register_message(WM_MOVE, this, &UserInterfaceChromium::on_move);
	// Create window
	auto window_style = WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_THICKFRAME;
	this->window_handle = CreateWindowEx(WS_EX_APPWINDOW, FOO_UI_CHROMIUM_WINDOW_CLASS, FOO_UI_CHROMIUM_WINDOW_NAME, window_style, cfg_window_x, cfg_window_y, cfg_window_width, cfg_window_height, nullptr, nullptr, core_api::get_my_instance(), nullptr);
	if (window_handle == nullptr) {
		UnregisterClass(FOO_UI_CHROMIUM_WINDOW_CLASS, core_api::get_my_instance());
		return NULL;
	}
	// Initialize cef
	this->app = new ChromiumApp;
	this->app->init(this->window_handle, cfg_main_url);
	// Show window
	ShowWindow(this->window_handle, SW_SHOWNORMAL);
	UpdateWindow(this->window_handle);
	// Notification icon
	this->notify_icon.init(this->window_handle);
	if (cfg_al_show_icon == true) {
		this->notify_icon.show();
	}
	return this->window_handle;
}
 
void UserInterfaceChromium::process_shutdown() {
	if (this->window_handle != NULL) {
		// Delete taskbar icon
		this->notify_icon.destroy();
		// hide window
		ShowWindow(this->window_handle, SW_HIDE);
		DestroyWindow(this->window_handle);
		// Close cef
		this->app->destroy();
		// Unregister message
		this->unregister_message(WM_CLOSE);
		this->unregister_message(WM_SIZE);
		this->unregister_message(WM_MOVE);
		// Unregister class
		UnregisterClass(FOO_UI_CHROMIUM_WINDOW_CLASS, core_api::get_my_instance());
	}
}

LRESULT UserInterfaceChromium::on_close(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	cfg_window_is_max = false;
	standard_commands::main_exit();
	return 0;
}

LRESULT UserInterfaceChromium::on_size(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (wParam == SIZE_MAXIMIZED) {
		cfg_window_is_max = true;
	} else if (wParam == SIZE_MINIMIZED) {
		if (cfg_window_is_max == false) {
			this->save_window_size();
		}
		if (cfg_min_to_icon == true) {
			ShowWindow(hwnd, SW_MINIMIZE);
			this->notify_icon.disable_icon();
			if (cfg_al_show_icon == false) {
				this->notify_icon.show();
			}
		}
	} else if (wParam == SIZE_RESTORED) {
		cfg_window_is_max = false;
		this->save_window_size();
	}
	if (this->app != nullptr) {
		this->app->resize_browser(LOWORD(lParam), HIWORD(lParam));
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT UserInterfaceChromium::on_move(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (cfg_window_is_max == false) {
		this->save_window_size();
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}