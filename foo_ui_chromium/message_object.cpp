#include "stdafx.h"
#include "message_object.h"

std::map<UINT, std::pair<MessageObject *, MessageObject::message_function_gen>> MessageObject::message_list;
user_interface_v2::HookProc_t MessageObject::hook_callback;

bool MessageObject::unregister_message(UINT message) {
	auto itr = this->message_list.find(message);
	if (itr == this->message_list.end()) {
		return false;
	} else {
		this->message_list.erase(itr);
		return true;
	}
}

LRESULT CALLBACK MessageObject::message_process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	auto itr = MessageObject::message_list.find(uMsg);
	LRESULT return_value;
	if (hook_callback(hwnd, uMsg, wParam, lParam, &return_value) != 0) {
		return return_value;
	} else if (itr == MessageObject::message_list.end()) {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	} else {
		auto pair = itr->second;
		return (pair.first->*pair.second)(hwnd, uMsg, wParam, lParam);
	}
}

void MessageObject::set_hook_function(user_interface_v2::HookProc_t hook_callback) {
	MessageObject::hook_callback = hook_callback;
}