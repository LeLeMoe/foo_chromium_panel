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
		// GUID: 7FD0C17B-A650-4207-BF24-B57F09F005D1
		return { 0x7fd0c17b, 0xa650, 0x4207, { 0xbf, 0x24, 0xb5, 0x7f, 0x9, 0xf0, 0x5, 0xd1 } };
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