#include "stdafx.h"
#include "resource.h"

class PreferenceMain : public CDialogImpl<PreferenceMain>, public preferences_page_instance {
public:
	PreferenceMain(preferences_page_callback::ptr callback) : callback_function(callback) {}

public:
	t_uint32 get_state() override {
		t_uint32 state = preferences_state::resettable;
		if(has_changed()) {
			state |= preferences_state::changed;
		}
		return state;
	}
	void apply() override {
		// TODO
	}
	void reset() override {
		// TODO
	}


public:
	enum { IDD = IDD_PREFERENCE_MAIN };

	BEGIN_MSG_MAP(PreferenceMain)
		MSG_WM_INITDIALOG(on_init_dialog)
		MSG_WM_DESTROY(on_destory)
	END_MSG_MAP()

private:
	bool on_init_dialog(CWindow, LPARAM) {
		// Set font of title
		HFONT title_font_large = CreateFont(24, 0, 0, 0, FW_DONTCARE, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
		SendDlgItemMessage(IDC_TITLE1, WM_SETFONT, reinterpret_cast<WPARAM>(title_font_large), true);
		return false;
	}
	bool on_destory() {
		DeleteObject(title_font_large);
		return false;
	}
	bool has_changed() {
		// TODO
		return false;
	}

private:
	const preferences_page_callback::ptr callback_function;
	HFONT title_font_large;
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