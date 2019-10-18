#pragma once

class UserInterfaceChromium : public user_interface_v2, public MessageObject {
public:
	UserInterfaceChromium();
	~UserInterfaceChromium() = default;

public:
	const char* get_name() override;
	HWND init(HookProc_t hook) override;
	void activate() override;
	void hide() override;
	void shutdown() override;
	bool is_visible() override;
	GUID get_guid() override;
	void override_statusbar_text(const char* p_text) override;
	void revert_statusbar_text() override;
	void show_now_playing() override;
	bool query_capability(const GUID& cap) override;

private:
	void save_window_size();

private:
	HWND process_init();
	void process_shutdown();

private:
	LRESULT on_destroy(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT on_size(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT on_syscommand(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND window_handle;
	NotifyIcon notify_icon;
	CefRefPtr<ChromiumApp> app;
};