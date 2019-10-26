#include "../stdafx.h"

APIPlayControl::APIPlayControl(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response) :
		APIBase(post_json, callback, data_out, offest, bytes_to_read, response) {}

void APIPlayControl::callback_run() {
	if (this->post_json->GetValue("cmd")->GetString() == "fb2k.play_control.play") {
		standard_commands::main_play();
		this->response->add_string("{\"status\":\"success\"}");
	} else if (this->post_json->GetValue("cmd")->GetString() == "fb2k.play_control.pause") {
		standard_commands::main_pause();
		this->response->add_string("{\"status\":\"success\"}");
	} else if (this->post_json->GetValue("cmd")->GetString() == "fb2k.play_control.play_or_pause") {
		standard_commands::main_play_or_pause();
		this->response->add_string("{\"status\":\"success\"}");
	} else if (this->post_json->GetValue("cmd")->GetString() == "fb2k.play_control.stop") {
		standard_commands::main_stop();
		this->response->add_string("{\"status\":\"success\"}");
	} else if (this->post_json->GetValue("cmd")->GetString() == "fb2k.play_control.next") {
		standard_commands::main_next();
		this->response->add_string("{\"status\":\"success\"}");
	} else if (this->post_json->GetValue("cmd")->GetString() == "fb2k.play_control.previous") {
		standard_commands::main_previous();
		this->response->add_string("{\"status\":\"success\"}");
	}
	this->finish();
}

service_ptr_t<main_thread_callback> APIPlayControl::factory(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response) {
	return new service_impl_t<APIPlayControl>(post_json, callback, data_out, offest, bytes_to_read, response);
}