#pragma once

class MessageObject {
public:
	template <typename T>
	using message_function = LRESULT(T::*)(HWND, UINT, WPARAM, LPARAM);

public:
	MessageObject() = default;
	virtual ~MessageObject() = default;

protected:
	template <typename T>
	bool register_message(UINT message, T* object, message_function<T> function) {
		if (MessageObject::message_list.have_item(message)) {
			return false;
		} else {
			RunableData data;
			data.object = reinterpret_cast<MessageObject *>(object);
			data.function = (message_function_gen)function;
			MessageObject::message_list.set(message, data);
			return true;
		}
	}
	bool unregister_message(UINT message);

protected:
	static LRESULT CALLBACK message_process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void init(user_interface_v2::HookProc_t hook_callback);

private:
	using message_function_gen = LRESULT(MessageObject::*)(HWND, UINT, WPARAM, LPARAM);

private:
	struct RunableData {
		MessageObject* object;
		message_function_gen function;
	};

private:
	static pfc::map_t<UINT, RunableData> message_list;
	static user_interface_v2::HookProc_t hook_callback;
};