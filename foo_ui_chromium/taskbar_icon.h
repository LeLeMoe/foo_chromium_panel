#pragma once

class TaskbarIcon {
public:
	TaskbarIcon() = delete;

public:
	static void initialize(HWND hwnd);
	static void show();
	static void hide();
	static void enable_icon();
	static void disable_icon();
	static void message_process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void destroy();

private:
	static HICON icon;
	static NOTIFYICONDATAA notify_icon;
	static HWND window_handle;
	static HMENU menu;
	static ITaskbarList *taskbar_list;
};