#include "../stdafx.h"

cfg_bool cfg_use_custom_icon(FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON_USE_CUSTOM_ICON, false);
cfg_string cfg_custom_icon_url(FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON_CUSTOM_ICON_URL, "");
cfg_bool cfg_al_show_icon(FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON_AL_SHOW_ICON, true);
cfg_bool cfg_min_to_icon(FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON_MIN_TO_ICON, true);

static preferences_page_factory_t<PreferenceTaskbarImpl> preference_taskbar;

PreferenceNotifyIcon::PreferenceNotifyIcon(preferences_page_callback::ptr callback) : callback_function(callback), has_changed(false), title_font_large(NULL) {}

t_uint32 PreferenceNotifyIcon::get_state() {
	t_uint32 state = preferences_state::resettable;
	if (this->has_changed == true) {
		state |= preferences_state::changed;
	}
	return state;
}

void PreferenceNotifyIcon::apply() {
	// Set use custom icon state
	cfg_use_custom_icon = SendDlgItemMessageA(get_wnd(), IDC_CHECK_EN_CUS_ICO, BM_GETCHECK, NULL, NULL) == BST_CHECKED;
	// Set custom icon url
	char url_text[MAX_PATH] = { 0 };
	GetWindowTextA(this->GetDlgItem(IDC_EDIT_EN_CUS_ICO).m_hWnd, url_text, MAX_PATH);
	cfg_custom_icon_url = url_text;
	// Set always show icon state
	cfg_al_show_icon = SendDlgItemMessageA(get_wnd(), IDC_CHECK_AL_SHOW_ICO, BM_GETCHECK, NULL, NULL) == BST_CHECKED;
	// Set minimize to icon state
	cfg_min_to_icon = SendDlgItemMessageA(get_wnd(), IDC_CHECK_MIN_TO_ICO, BM_GETCHECK, NULL, NULL) == BST_CHECKED;
	this->on_changed();
	this->has_changed = false;
}

void PreferenceNotifyIcon::reset() {
	this->on_changed();
	this->has_changed = false;
}

void PreferenceNotifyIcon::on_changed() {
	this->has_changed = true;
	this->callback_function->on_state_changed();
}

void PreferenceNotifyIcon::on_check_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
	this->on_changed();
}

bool PreferenceNotifyIcon::on_init_dialog(CWindow, LPARAM) {
	// Set font of title
	this->title_font_large = CreateFont(24, 0, 0, 0, FW_DONTCARE, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
	SendDlgItemMessage(IDC_TITLE_TASKBAR, WM_SETFONT, reinterpret_cast<WPARAM>(this->title_font_large), true);
	// Set use custom icon check
	if (cfg_use_custom_icon == true) {
		SendDlgItemMessageA(get_wnd(), IDC_CHECK_EN_CUS_ICO, BM_SETCHECK, BST_CHECKED, NULL);
	} else {
		SendDlgItemMessageA(get_wnd(), IDC_CHECK_EN_CUS_ICO, BST_UNCHECKED, BST_CHECKED, NULL);
	}
	// Set custom icon url
	SendDlgItemMessageA(get_wnd(), IDC_EDIT_EN_CUS_ICO, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(cfg_custom_icon_url.c_str()));
	SendDlgItemMessageA(get_wnd(), IDC_EDIT_EN_CUS_ICO, EM_LIMITTEXT, MAX_PATH, NULL);
	if (cfg_use_custom_icon == false) {
		this->GetDlgItem(IDC_EDIT_EN_CUS_ICO).EnableWindow(false);
	}
	// Set change button
	if (cfg_use_custom_icon == false) {
		this->GetDlgItem(IDC_BUTTON_EN_CUS_ICO).EnableWindow(false);
	}
	// Set always show icon check
	if (cfg_al_show_icon == true) {
		SendDlgItemMessageA(get_wnd(), IDC_CHECK_AL_SHOW_ICO, BM_SETCHECK, BST_CHECKED, NULL);
	} else {
		SendDlgItemMessageA(get_wnd(), IDC_CHECK_AL_SHOW_ICO, BST_UNCHECKED, BST_CHECKED, NULL);
	}
	// Set minimize to icon check
	if (cfg_min_to_icon == true) {
		SendDlgItemMessageA(get_wnd(), IDC_CHECK_MIN_TO_ICO, BM_SETCHECK, BST_CHECKED, NULL);
	} else {
		SendDlgItemMessageA(get_wnd(), IDC_CHECK_MIN_TO_ICO, BST_UNCHECKED, BST_CHECKED, NULL);
	}
	return false;
}

void PreferenceNotifyIcon::on_cus_icon_check_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
	if (SendDlgItemMessageA(get_wnd(), IDC_CHECK_EN_CUS_ICO, BM_GETCHECK, NULL, NULL) == BST_UNCHECKED) {
		this->GetDlgItem(IDC_EDIT_EN_CUS_ICO).EnableWindow(false);
		this->GetDlgItem(IDC_BUTTON_EN_CUS_ICO).EnableWindow(false);
	} else {
		this->GetDlgItem(IDC_EDIT_EN_CUS_ICO).EnableWindow(true);
		this->GetDlgItem(IDC_BUTTON_EN_CUS_ICO).EnableWindow(true);
	}
	this->on_changed();
}

void PreferenceNotifyIcon::on_icon_button_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
	char buffer[MAX_PATH] = { 0 };
	OPENFILENAMEA ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = get_wnd();
	ofn.lpstrFile = buffer;
	ofn.lpstrFilter = "Icon Images(*.ico)\0*.ico\0All Files\0*.*\0\0";
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
	if (GetOpenFileNameA(&ofn) == TRUE) {
		SendDlgItemMessageA(get_wnd(), IDC_EDIT_EN_CUS_ICO, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(buffer));
		this->on_changed();
	}
}

bool PreferenceNotifyIcon::on_destory() {
	DeleteObject(title_font_large);
	return false;
}

const char* PreferenceTaskbarImpl::get_name() {
	return FOO_UI_CHROMIUM_PREFERNECE_NOTIFY_ICON_NAME;
}

GUID PreferenceTaskbarImpl::get_guid() {
	return GUID(FOO_UI_CHROMIUM_GUID_NOTIFY_ICON);
}

GUID PreferenceTaskbarImpl::get_parent_guid() {
	return GUID(FOO_UI_CHROMIUM_GUID_PREFERENCE_MAIN);
}