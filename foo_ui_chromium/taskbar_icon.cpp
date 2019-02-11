#include "stdafx.h"
#include "taskbar_icon.h"
#include "preference_taskbar.h"

HICON TaskbarIcon::icon = nullptr;
NOTIFYICONDATAA TaskbarIcon::notify_icon = { 0 };
HWND TaskbarIcon::window_handle = nullptr;
HMENU TaskbarIcon::menu = nullptr;
ITaskbarList *TaskbarIcon::taskbar_list = nullptr;

void TaskbarIcon::initialize(HWND hwnd) {
	// Save window's handle
	window_handle = hwnd;
	// Load icon
	if(cfg_use_custom_icon == true) {
		icon = static_cast<HICON>(LoadImageA(core_api::get_my_instance(), cfg_custom_icon_url.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_LOADFROMFILE));
	}
	if(icon == nullptr || cfg_use_custom_icon == false) {
		icon = ui_control::get()->get_main_icon();
	}
	// Set NOTIFYICONDATA struct
	notify_icon.cbSize = sizeof(NOTIFYICONDATAA);
	notify_icon.hWnd = window_handle;
	notify_icon.uFlags = NIF_ICON | NIF_GUID | NIF_TIP | NIF_MESSAGE;
	notify_icon.hIcon = icon;
	notify_icon.guidItem = GUID(GUID_TASKBAR_ICON);
	notify_icon.uCallbackMessage = WM_USER;
	strcpy_s(notify_icon.szTip, "foobar2000");
	// Create menu
	menu = CreatePopupMenu();
	AppendMenuA(menu, MF_STRING, FOO_UI_CHROMIUM_MENU_PREFERENCE, "Preferences");
	AppendMenuA(menu, MF_MENUBARBREAK, NULL, nullptr);
	AppendMenuA(menu, MF_STRING, FOO_UI_CHROMIUM_MENU_EXIT, "Exit");
	// Create taskbar list controler
	CoInitialize(nullptr);
	CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void **)&taskbar_list);
	taskbar_list->HrInit();
}

void TaskbarIcon::show() {
	Shell_NotifyIconA(NIM_ADD, &notify_icon);
}

void TaskbarIcon::hide() {
	Shell_NotifyIconA(NIM_DELETE, &notify_icon);
}

void TaskbarIcon::enable_icon() {
	taskbar_list->AddTab(window_handle);
}

void TaskbarIcon::disable_icon() {
	taskbar_list->DeleteTab(window_handle);
}

void TaskbarIcon::message_process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if(uMsg == WM_USER) {
		switch(lParam) {
		case WM_LBUTTONDBLCLK:
			if(cfg_min_to_icon == true) {
				enable_icon();
				ShowWindow(hwnd, SW_SHOWNORMAL);
				if(cfg_al_show_icon == false) {
					TaskbarIcon::hide();
				}
			}
			break;
		case WM_RBUTTONDOWN:
			if(menu != nullptr) {
				POINT mouse_point;
				SetForegroundWindow(window_handle);
				GetCursorPos(&mouse_point);
				auto select_item = TrackPopupMenu(menu, TPM_RETURNCMD, mouse_point.x, mouse_point.y, NULL, window_handle, NULL);
				switch(select_item) {
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
	}
}

void TaskbarIcon::destroy() {
	Shell_NotifyIconA(NIM_DELETE, &notify_icon);
	if(menu != nullptr) {
		DestroyMenu(menu);
	}
	if(icon != nullptr) {
		DestroyIcon(icon);
	}
	taskbar_list->Release();
	CoUninitialize();
}