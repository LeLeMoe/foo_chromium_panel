#pragma once

class NotifyIcon : public MessageObject {
public:
	NotifyIcon() = default;
	~NotifyIcon() = default;

public:
	void init(HWND handle);
	void show();
	void hide();
	void enable_icon();
	void disable_icon();
	void destroy();

public:
	LRESULT on_mouse(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void enable_window_size();

private:
	HICON icon;
	HMENU menu;
	HWND window_handle;
	NOTIFYICONDATAA notify_icon;
	ITaskbarList *taskbar_list;
};