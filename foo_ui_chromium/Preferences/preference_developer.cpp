#include "../stdafx.h"

cfg_string cfg_developer_log(FOO_UI_CHROMIUM_GUID_PREFERENCE_DEVELOPER_LOG, core_api::get_my_log_path().c_str());

PreferenceDeveloper::PreferenceDeveloper(preferences_page_callback::ptr callback) : callback_function(callback), has_changed(false), title_font_large(NULL) {}

t_uint32 PreferenceDeveloper::get_state() {
	t_uint32 state = preferences_state::resettable;
	if (this->has_changed == true) {
		state |= preferences_state::changed;
	}
	return state;
}

void PreferenceDeveloper::apply() {
}

void PreferenceDeveloper::reset() {
}

void PreferenceDeveloper::on_changed() {

}

bool PreferenceDeveloper::on_init_dialog(CWindow, LPARAM) {
	// Set font of title
	this->title_font_large = CreateFont(24, 0, 0, 0, FW_DONTCARE, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
	SendDlgItemMessage(IDC_TITLE_DEVELOPER, WM_SETFONT, reinterpret_cast<WPARAM>(this->title_font_large), true);
	// Set text of url edit
	SendDlgItemMessageA(get_wnd(), IDC_EDIT_LOG, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(cfg_developer_log.c_str()));
	// Set max length of url edit
	SendDlgItemMessageA(get_wnd(), IDC_EDIT_LOG, EM_LIMITTEXT, MAX_PATH, NULL);
	return false;
}

void PreferenceDeveloper::on_log_button_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
	char buffer[MAX_PATH] = { 0 };
	BROWSEINFO bi = { 0 };

}

void PreferenceDeveloper::on_log_edit_changed(UINT wNotifyCode, int wID, HWND hWndCtl) {

}

bool PreferenceDeveloper::on_destory() {

}