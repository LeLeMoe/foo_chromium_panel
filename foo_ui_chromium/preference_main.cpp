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
	END_MSG_MAP()

private:
	bool on_init_dialog(CWindow, LPARAM) {
		return false;
	}
	bool has_changed() {
		// TODO
		return false;
	}

private:
	const preferences_page_callback::ptr callback_function;
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
		return guid_tools;
	}
};

static advconfig_branch_factory preference_main_branch(FOO_UI_CHROMIUM_NAME, GUID(GUID_PREFERENCE_MAIN_BRANCH), advconfig_branch::guid_branch_display, 0);
static preferences_page_factory_t<PreferenceMainImpl> preference_main;