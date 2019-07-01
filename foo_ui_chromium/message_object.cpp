#include "stdafx.h"
#include "message_object.h"

std::map<UINT, std::pair<message_object *, message_object::message_function_gen>> message_object::message_list;
user_interface_v2::HookProc_t message_object::hook_callback;

bool message_object::unregister_message(UINT message) {
	auto itr = this->message_list.find(message);
	if (itr == this->message_list.end()) {
		return false;
	} else {
		this->message_list.erase(itr);
		return true;
	}
}

LRESULT CALLBACK message_object::message_process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	auto itr = message_object::message_list.find(uMsg);

	if (itr == message_object::message_list.end()) {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	} else {
		auto pair = itr->second;
		(pair.first->*pair.second)(hwnd, uMsg, wParam, lParam);
	}
}

void message_object::set_hook_function(user_interface_v2::HookProc_t hook_callback) {
	message_object::hook_callback = hook_callback;
}