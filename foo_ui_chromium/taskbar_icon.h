#pragma once

#include "message_object.h"

class TaskbarIcon : public MessageObject {
public:
	TaskbarIcon();
	~TaskbarIcon() = default;

public:
	void initialize(HWND hwnd);
	void show();
	void hide();
	void enable_icon();
	void disable_icon();
	void destroy();

public:
	LRESULT process_mouse(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HICON icon;
	NOTIFYICONDATAA notify_icon;
	HWND window_handle;
	HMENU menu;
	ITaskbarList *taskbar_list;
};