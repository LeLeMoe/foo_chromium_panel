#include "../stdafx.h"

pfc::map_t<UINT, MessageObject::RunableData> MessageObject::message_list;
user_interface_v2::HookProc_t MessageObject::hook_callback;

bool MessageObject::unregister_message(UINT message) {
	if (MessageObject::message_list.have_item(message)) {
		MessageObject::message_list.remove(message);
		return true;
	} else {
		return false;
	}
}

LRESULT CALLBACK MessageObject::message_process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	auto ptr = MessageObject::message_list.query_ptr(uMsg);
	LRESULT return_value;
	if (hook_callback(hwnd, uMsg, wParam, lParam, &return_value) != 0) {
		return return_value;
	} else if (ptr != NULL) {
		return (ptr->object->*ptr->function)(hwnd, uMsg, wParam, lParam);
	} else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void MessageObject::init(user_interface_v2::HookProc_t hook_callback) {
	MessageObject::hook_callback = hook_callback;
}