#include "stdafx.h"

class UserInterfaceChromium : public user_interface_v2 {
public:
	UserInterfaceChromium() = default;
	~UserInterfaceChromium() = default;

public:
	const char *get_name() override {
		return FOO_UI_CHROMIUM_NAME;
	}
	HWND init(HookProc_t hook) override {
		return ChromiumWindow::chromium_wiundow.initialize(hook);
	}
	void activate() override {
		// TODO
	}
	void hide() override {
		// TODO
	}
	void shutdown() override {
		// TODO
	}
	bool is_visible() override {
		//TODO
		return true;
	}
	GUID get_guid() override {
		return GUID(GUID_USER_INTERFACE);
	}
	void override_statusbar_text(const char * p_text) override {
		// TODO
	}
	void revert_statusbar_text() override {
		// TODO
	}
	void show_now_playing() override {
		// TODO
	}
	bool query_capability(const GUID & cap) override {
		return false;
	}
};

static user_interface_factory<UserInterfaceChromium> user_interface_chromium;