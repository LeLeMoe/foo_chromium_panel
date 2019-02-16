#include "stdafx.h"
#include "helper.h"
#include "preference_main.h"

cfg_string cfg_main_url(GUID_PREFERENCE_MAIN_URL, core_api::get_default_page_path().c_str());

class PreferenceMain : public CDialogImpl<PreferenceMain>, public preferences_page_instance {
public:
	PreferenceMain(preferences_page_callback::ptr callback) : callback_function(callback), has_changed(false) {}

public:
	t_uint32 get_state() override {
		t_uint32 state = preferences_state::resettable;
		if(has_changed == true) {
			state |= preferences_state::changed;
		}
		return state;
	}
	void apply() override {
		// Set url
		char url_text[MAX_PATH] = { 0 };
		GetWindowTextA(this->GetDlgItem(IDC_EDIT_URL).m_hWnd, url_text, MAX_PATH);
		cfg_main_url = url_text;
		on_changed();
		has_changed = false;
	}
	void reset() override {
		on_changed();
		has_changed = false;
	}


public:
	enum { IDD = IDD_PREFERENCE_MAIN };

	BEGIN_MSG_MAP(PreferenceMain)
		MSG_WM_INITDIALOG(on_init_dialog)
		COMMAND_HANDLER_EX(IDC_BUTTON_URL, BN_CLICKED, on_url_button_clicked)
		COMMAND_HANDLER_EX(IDC_EDIT_URL, EN_CHANGE, on_url_edit_changed)
		MSG_WM_DESTROY(on_destory)
	END_MSG_MAP()

private:
	void on_changed() {
		has_changed = true;
		callback_function->on_state_changed();
	}
	bool on_init_dialog(CWindow, LPARAM) {
		// Set font of title
		title_font_large = CreateFont(24, 0, 0, 0, FW_DONTCARE, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
		SendDlgItemMessage(IDC_TITLE_GENERAL, WM_SETFONT, reinterpret_cast<WPARAM>(title_font_large), true);
		// Set text of url edit
		SendDlgItemMessageA(get_wnd(), IDC_EDIT_URL, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(cfg_main_url.c_str()));
		// Set max length of url edit
		SendDlgItemMessageA(get_wnd(), IDC_EDIT_URL, EM_LIMITTEXT, MAX_PATH, NULL);
		return false;
	}
	void on_url_button_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
		char buffer[MAX_PATH] = { 0 };
		OPENFILENAMEA ofn = { 0 };
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = get_wnd();
		ofn.lpstrFile = buffer;
		ofn.lpstrFilter = "HTML Files(*.html;*.htm)\0*.html;*.htm\0MHTML Files(*.mhtml)\0*.mhtml\0All Files\0*.*\0\0";
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
		if(GetOpenFileNameA(&ofn) == TRUE) {
			pfc::string8 path("file:///");
			path.add_string(buffer);
			path.replace_string("\\", "/");
			SendDlgItemMessageA(get_wnd(), IDC_EDIT_URL, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(path.c_str()));
			on_changed();
		}
	}
	void on_url_edit_changed(UINT wNotifyCode, int wID, HWND hWndCtl) {
		char url_text[MAX_PATH] = { 0 };
		GetWindowTextA(this->GetDlgItem(IDC_EDIT_URL).m_hWnd, url_text, MAX_PATH);
		pfc::string8 text(url_text);
		if(text != cfg_main_url) {
			on_changed();
		}
	}
	bool on_destory() {
		DeleteObject(title_font_large);
		return false;
	}

private:
	const preferences_page_callback::ptr callback_function;
	HFONT title_font_large;
	bool has_changed;
};

class PreferenceMainImpl : public preferences_page_impl<PreferenceMain> {
public:
	const char *get_name() override {
		return FOO_UI_CHROMIUM_NAME;
	}
	GUID get_guid() override {
		return GUID(GUID_PREFERENCE_MAIN);
	}
	GUID get_parent_guid() override {
		return preferences_page::guid_display;
	}
};

static preferences_page_factory_t<PreferenceMainImpl> preference_main;