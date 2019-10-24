#include "../stdafx.h"

APIPlayControl::APIPlayControl(CefRefPtr<CefDictionaryValue> json) : APIBase(json) {}

bool APIPlayControl::Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) {
	CEF_REQUIRE_IO_THREAD();
	if (this->json_request->GetValue("cmd")->GetString() == "fb2k.play_control.play") {
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(new service_impl_t<MainThreadCallbackPlay>);
		this->reposnd = "{}";
		this->status_code = 200;
	} else if (this->json_request->GetValue("cmd")->GetString() == "fb2k.play_control.pause") {
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(new service_impl_t<MainThreadCallbackPause>);
		this->reposnd = "{}";
		this->status_code = 200;
	} else if (this->json_request->GetValue("cmd")->GetString() == "fb2k.play_control.play_or_pause") {
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(new service_impl_t<MainThreadCallbackPlayOrPause>);
		this->reposnd = "{}";
		this->status_code = 200;
	} else if (this->json_request->GetValue("cmd")->GetString() == "fb2k.play_control.stop") {
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(new service_impl_t<MainThreadCallbackStop>);
		this->reposnd = "{}";
		this->status_code = 200;
	} else if (this->json_request->GetValue("cmd")->GetString() == "fb2k.play_control.next") {
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(new service_impl_t<MainThreadCallbackNext>);
		this->reposnd = "{}";
		this->status_code = 200;
	} else if (this->json_request->GetValue("cmd")->GetString() == "fb2k.play_control.previous") {
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(new service_impl_t<MainThreadCallbackPrevious>);
		this->reposnd = "{}";
		this->status_code = 200;
	}
	handle_request = true;
	return true;
}

CefRefPtr<CefResourceHandler> APIPlayControl::api_factory(CefRefPtr<CefDictionaryValue> json) {
	return new APIPlayControl(json);
}

void APIPlayControl::MainThreadCallbackPlay::callback_run() {
	standard_commands::main_play();
}
void APIPlayControl::MainThreadCallbackPause::callback_run() {
	standard_commands::main_pause();
}
void APIPlayControl::MainThreadCallbackPlayOrPause::callback_run() {
	standard_commands::main_play_or_pause();
}
void APIPlayControl::MainThreadCallbackStop::callback_run() {
	standard_commands::main_stop();
}
void APIPlayControl::MainThreadCallbackNext::callback_run() {
	standard_commands::main_next();
}
void APIPlayControl::MainThreadCallbackPrevious::callback_run() {
	standard_commands::main_previous();
}