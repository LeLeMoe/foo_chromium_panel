#pragma once
#include "stdafx.h"
#include "Windows.h"
#include <map>
#include <utility>

class message_object {
public:
	template <typename T>
	using message_function = LRESULT(T::*)(HWND, UINT, WPARAM, LPARAM);

public:
	message_object() = default;
	~message_object() = default;

protected:
	template <typename T>
	bool register_message(UINT message, message_function<T> function) {
		auto function_gen = dynamic_cast<message_function_gen>(function);
		if (this->message_list.find(message) == this->message_list.end()) {
			return false;
		}
		else {
			this->message_list.insert(std::make_pair(message, std::make_pair(this, function)));
			return true;
		}
	}
	bool unregister_message(UINT message);

protected:
	static LRESULT CALLBACK message_process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void set_hook_function(user_interface_v2::HookProc_t hook_callback);

private:
	using message_function_gen = LRESULT(message_object::*)(HWND, UINT, WPARAM, LPARAM);

private:
	static std::map<UINT, std::pair<message_object *, message_function_gen>> message_list;
	static user_interface_v2::HookProc_t hook_callback;
};