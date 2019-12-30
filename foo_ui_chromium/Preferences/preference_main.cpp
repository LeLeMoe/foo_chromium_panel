#include "../stdafx.h"

cfg_string cfg_main_url(FOO_UI_CHROMIUM_GUID_PREFERENCE_MAIN_URL, core_api::get_default_page_path().c_str());

static preferences_page_factory_t<PreferenceMainImpl> preference_main;

PreferenceMain::PreferenceMain(preferences_page_callback::ptr callback) : callback_function(callback), has_changed(false), title_font_large(NULL) {}

t_uint32 PreferenceMain::get_state() {
	t_uint32 state = preferences_state::resettable;
	if (this->has_changed == true) {
		state |= preferences_state::changed;
	}
	return state;
}

void PreferenceMain::apply() {
	// Set url
	char url_text[MAX_PATH] = { 0 };
	GetWindowTextA(this->GetDlgItem(IDC_EDIT_URL).m_hWnd, url_text, MAX_PATH);
	cfg_main_url = url_text;
	this->on_changed();
	this->has_changed = false;
}

void PreferenceMain::reset() {
	this->on_changed();
	this->has_changed = false;
}

void PreferenceMain::on_changed() {
	this->has_changed = true;
	this->callback_function->on_state_changed();
}

bool PreferenceMain::on_init_dialog(CWindow, LPARAM) {
	// Set font of title
	this->title_font_large = CreateFont(24, 0, 0, 0, FW_DONTCARE, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
	SendDlgItemMessage(IDC_TITLE_GENERAL, WM_SETFONT, reinterpret_cast<WPARAM>(this->title_font_large), true);
	// Set text of url edit
	SendDlgItemMessageA(get_wnd(), IDC_EDIT_URL, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(cfg_main_url.c_str()));
	// Set max length of url edit
	SendDlgItemMessageA(get_wnd(), IDC_EDIT_URL, EM_LIMITTEXT, MAX_PATH, NULL);
	return false;
}

void PreferenceMain::on_url_button_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
	char buffer[MAX_PATH] = { 0 };
	OPENFILENAMEA ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = get_wnd();
	ofn.lpstrFile = buffer;
	ofn.lpstrFilter = "HTML Files(*.html;*.htm)\0*.html;*.htm\0MHTML Files(*.mhtml)\0*.mhtml\0All Files\0*.*\0\0";
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
	if (GetOpenFileNameA(&ofn) == TRUE) {
		pfc::string8 path("file:///");
		path.add_string(buffer);
		path.replace_string("\\", "/");
		SendDlgItemMessageA(get_wnd(), IDC_EDIT_URL, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(path.c_str()));
		this->on_changed();
	}
}

void PreferenceMain::on_url_edit_changed(UINT wNotifyCode, int wID, HWND hWndCtl) {
	char url_text[MAX_PATH] = { 0 };
	GetWindowTextA(this->GetDlgItem(IDC_EDIT_URL).m_hWnd, url_text, MAX_PATH);
	pfc::string8 text(url_text);
	if (text != cfg_main_url) {
		this->on_changed();
	}
}

bool PreferenceMain::on_destory() {
	DeleteObject(this->title_font_large);
	return false;
}

const char* PreferenceMainImpl::get_name() {
	return FOO_UI_CHROMIUM_NAME;
}

GUID PreferenceMainImpl::get_guid() {
	return GUID(FOO_UI_CHROMIUM_GUID_PREFERENCE_MAIN);
}

GUID PreferenceMainImpl::get_parent_guid() {
	return preferences_page::guid_display;
}