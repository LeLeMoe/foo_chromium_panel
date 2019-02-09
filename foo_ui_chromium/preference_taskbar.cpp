#include "stdafx.h"

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
	}
	void reset() override {
	}

public:
	enum { IDD = IDD_PREFERENCE_TASKBAR };

	BEGIN_MSG_MAP(PreferenceTaskbar)
		MSG_WM_INITDIALOG(on_init_dialog)
		MSG_WM_DESTROY(on_destory)
	END_MSG_MAP()

private:
	bool on_init_dialog(CWindow, LPARAM) {
		// Set font of title
		title_font_large = CreateFont(24, 0, 0, 0, FW_DONTCARE, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Shell Dlg");
		SendDlgItemMessage(IDC_TITLE_TASKBAR, WM_SETFONT, reinterpret_cast<WPARAM>(title_font_large), true);
		return false;
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