#pragma once

class ChromiumWindow {
private:
	ChromiumWindow() = default;
	~ChromiumWindow() = default;

public:
	HWND initialize(user_interface::HookProc_t hook);
	void shutdown();

public:
	static ChromiumWindow chromium_wiundow;
};