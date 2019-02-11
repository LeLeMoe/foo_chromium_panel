#include "stdafx.h"

cfg_bool cfg_use_custom_icon(GUID_PREFERENCE_TASKBAR_USE_CUSTOM_ICON, false);
cfg_string cfg_custom_icon_url(GUID_PREFERENCE_TASKBAR_CUSTOM_ICON_URL, "");
cfg_bool cfg_al_show_icon(GUID_PREFERENCE_TASKBAR_AL_SHOW_ICON, true);
cfg_bool cfg_min_to_icon(GUID_PREFERENCE_TASKBAR_MIN_TO_ICON, true);

class PreferenceTaskbar : public CDialogImpl<PreferenceTaskbar>, public preferences_page_instance {
public:
	PreferenceTaskbar(preferences_page_callback::ptr callback) : callback_function(callback), has_changed(false) {}

public:
	t_uint32 get_state() override {
		t_uint32 state = preferences_state::resettable;
		if(has_changed == true) {
			state |= preferences_state::changed;
		}
		return state;
	}
	void apply() override {
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
		// on_changed();
		// has_changed = false;
	}
	void reset() override {
		on_changed();
		has_changed = false;
	}

public:
	enum { IDD = IDD_PREFERENCE_TASKBAR };

	BEGIN_MSG_MAP(PreferenceTaskbar)
		MSG_WM_INITDIALOG(on_init_dialog)
		COMMAND_HANDLER_EX(IDC_CHECK_AL_SHOW_ICO, BN_CLICKED, on_check_clicked)
		COMMAND_HANDLER_EX(IDC_CHECK_MIN_TO_ICO, BN_CLICKED, on_check_clicked)
		COMMAND_HANDLER_EX(IDC_CHECK_EN_CUS_ICO, BN_CLICKED, on_cus_icon_check_clicked)
		COMMAND_HANDLER_EX(IDC_BUTTON_EN_CUS_ICO, BN_CLICKED, on_icon_button_clicked)
		MSG_WM_DESTROY(on_destory)
	END_MSG_MAP()

private:
	void on_changed() {
		has_changed = true;
		callback_function->on_state_changed();
	}
	void on_check_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
		on_changed();
	}
	bool on_init_dialog(CWindow, LPARAM) {
		// Set font of title
		title_font_large = CreateFont(24, 0, 0, 0, FW_DONTCARE, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
		SendDlgItemMessage(IDC_TITLE_TASKBAR, WM_SETFONT, reinterpret_cast<WPARAM>(title_font_large), true);
		// Set use custom icon check
		if(cfg_use_custom_icon == true) {
			SendDlgItemMessageA(get_wnd(), IDC_CHECK_EN_CUS_ICO, BM_SETCHECK, BST_CHECKED, NULL);
		} else {
			SendDlgItemMessageA(get_wnd(), IDC_CHECK_EN_CUS_ICO, BST_UNCHECKED, BST_CHECKED, NULL);
		}
		// Set custom icon url
		SendDlgItemMessageA(get_wnd(), IDC_EDIT_EN_CUS_ICO, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(cfg_custom_icon_url.c_str()));
		SendDlgItemMessageA(get_wnd(), IDC_EDIT_EN_CUS_ICO, EM_LIMITTEXT, MAX_PATH, NULL);
		// Set change button
		if(cfg_use_custom_icon == false) {
			this->GetDlgItem(IDC_BUTTON_EN_CUS_ICO).EnableWindow(false);
		}
		// Set always show icon check
		if(cfg_al_show_icon == true) {
			SendDlgItemMessageA(get_wnd(), IDC_CHECK_AL_SHOW_ICO, BM_SETCHECK, BST_CHECKED, NULL);
		} else {
			SendDlgItemMessageA(get_wnd(), IDC_CHECK_AL_SHOW_ICO, BST_UNCHECKED, BST_CHECKED, NULL);
		}
		// Set minimize to icon check
		if(cfg_min_to_icon == true) {
			SendDlgItemMessageA(get_wnd(), IDC_CHECK_MIN_TO_ICO, BM_SETCHECK, BST_CHECKED, NULL);
		} else {
			SendDlgItemMessageA(get_wnd(), IDC_CHECK_MIN_TO_ICO, BST_UNCHECKED, BST_CHECKED, NULL);
		}
		return false;
	}
	void on_cus_icon_check_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
		if(SendDlgItemMessageA(get_wnd(), IDC_CHECK_EN_CUS_ICO, BM_GETCHECK, NULL, NULL) == BST_UNCHECKED) {
			this->GetDlgItem(IDC_BUTTON_EN_CUS_ICO).EnableWindow(false);
		} else {
			this->GetDlgItem(IDC_BUTTON_EN_CUS_ICO).EnableWindow(true);
		}
		on_changed();
	}
	void on_icon_button_clicked(UINT wNotifyCode, int wID, HWND hWndCtl) {
		char buffer[MAX_PATH] = { 0 };
		OPENFILENAMEA ofn = { 0 };
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = get_wnd();
		ofn.lpstrFile = buffer;
		ofn.lpstrFilter = "Icon Images(*.ico)\0*.ico\0All Files\0*.*\0\0";
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
		if(GetOpenFileNameA(&ofn) == TRUE) {
			SendDlgItemMessageA(get_wnd(), IDC_EDIT_EN_CUS_ICO, WM_SETTEXT, NULL, reinterpret_cast<WPARAM>(buffer));
			on_changed();
		}
	}
	bool on_destory() {
		DeleteObject(title_font_large);
		return false;
	}

private:
	const preferences_page_callback::ptr callback_function;
	bool has_changed;
	HFONT title_font_large;
};

class PreferenceTaskbarImpl : public preferences_page_impl<PreferenceTaskbar> {
public:
	const char *get_name() override {
		return FOO_UI_PREFERNECE_TASKBAR_NAME;
	}
	GUID get_guid() override {
		return GUID(GUID_PREFERENCE_TASKBAR);
	}
	GUID get_parent_guid() override {
		return GUID(GUID_PREFERENCE_MAIN);
	}
};

static preferences_page_factory_t<PreferenceTaskbarImpl> preference_taskbar;