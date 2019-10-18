#include "../stdafx.h"

void NotifyIcon::init(HWND handle) {
	this->window_handle = handle;
	// Load icon
	if (cfg_use_custom_icon == true) {
		icon = static_cast<HICON>(LoadImageA(core_api::get_my_instance(), cfg_custom_icon_url.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_LOADFROMFILE));
	}
	if (icon == nullptr || cfg_use_custom_icon == false) {
		icon = ui_control::get()->get_main_icon();
	}
	// Set NOTIFYICONDATA struct
	this->notify_icon.cbSize = sizeof(NOTIFYICONDATAA);
	this->notify_icon.hWnd = this->window_handle;
	this->notify_icon.uFlags = NIF_ICON | NIF_GUID | NIF_TIP | NIF_MESSAGE;
	this->notify_icon.hIcon = this->icon;
	this->notify_icon.guidItem = GUID(FOO_UI_CHROMIUM_GUID_NOTIFY_ICON);
	this->notify_icon.uCallbackMessage = FOO_UI_CHROMIUM_MSG_ICONBAR;
	strcpy_s(this->notify_icon.szTip, "foobar2000");
	// Register message
	this->register_message(FOO_UI_CHROMIUM_MSG_ICONBAR, this, &NotifyIcon::on_mouse);
	// Create menu
	this->menu = CreatePopupMenu();
	AppendMenuA(this->menu, MF_STRING, FOO_UI_CHROMIUM_MENU_PREFERENCE, "Preferences");
	AppendMenuA(this->menu, MF_MENUBARBREAK, NULL, nullptr);
	AppendMenuA(this->menu, MF_STRING, FOO_UI_CHROMIUM_MENU_EXIT, "Exit");
	// Create taskbar list controler
	CoInitialize(nullptr);
	CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskbarList, reinterpret_cast<void**>(&this->taskbar_list));
	this->taskbar_list->HrInit();
}

void NotifyIcon::show() {
	Shell_NotifyIconA(NIM_ADD, &this->notify_icon);
}

void NotifyIcon::hide() {
	Shell_NotifyIconA(NIM_DELETE, &this->notify_icon);
}

void NotifyIcon::enable_icon() {
	this->taskbar_list->AddTab(this->window_handle);
}

void NotifyIcon::disable_icon() {
	this->taskbar_list->DeleteTab(this->window_handle);
}

void NotifyIcon::destroy() {
	// Remove notify icon
	Shell_NotifyIconA(NIM_DELETE, &this->notify_icon);
	if (menu != nullptr) {
		DestroyMenu(menu);
	}
	if (icon != nullptr) {
		DestroyIcon(icon);
	}
	this->taskbar_list->Release();
	CoUninitialize();
	// Unregister message
	this->unregister_message(FOO_UI_CHROMIUM_MSG_ICONBAR);
}

LRESULT NotifyIcon::on_mouse(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (lParam) {
	case WM_LBUTTONDBLCLK:
		if (cfg_min_to_icon == true) {
			this->enable_icon();
			if (cfg_window_is_max == false) {
				this->enable_window_size();
				ShowWindow(hwnd, SW_SHOWNORMAL);
			} else {
				ShowWindow(hwnd, SW_MAXIMIZE);
			}
			if (cfg_al_show_icon == false) {
				this->hide();
			}
		}
		break;
	case WM_RBUTTONDOWN:
		if (menu != nullptr) {
			POINT mouse_point;
			SetForegroundWindow(this->window_handle);
			GetCursorPos(&mouse_point);
			auto select_item = TrackPopupMenu(this->menu, TPM_RETURNCMD, mouse_point.x, mouse_point.y, NULL, this->window_handle, NULL);
			switch (select_item) {
			case FOO_UI_CHROMIUM_MENU_EXIT:
				standard_commands::main_exit();
				break;
			case FOO_UI_CHROMIUM_MENU_PREFERENCE:
				standard_commands::main_preferences();
				break;
			}
		}
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void NotifyIcon::enable_window_size() {
	SetWindowPos(this->window_handle, NULL, cfg_window_x, cfg_window_y, cfg_window_width, cfg_window_height, NULL);
}