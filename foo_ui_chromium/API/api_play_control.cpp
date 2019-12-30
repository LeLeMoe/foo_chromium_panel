#include "../stdafx.h"

APIPlayControl::APIPlayControl(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response) :
		APIBase(post_json, callback, data_out, offest, bytes_to_read, response) {}

void APIPlayControl::callback_run() {
	auto playback_ptr = static_api_ptr_t<playback_control_v3>();
	switch (this->post_json->GetValue("cmd")->GetInt()) {
	case 0x00000: {
		standard_commands::main_play();
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00001: {
		standard_commands::main_pause();
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00002: {
		standard_commands::main_play_or_pause();
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00003: {
		standard_commands::main_stop();
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00004: {
		standard_commands::main_next();
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00005: {
		standard_commands::main_previous();
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00006: {
		if (this->post_json->HasKey("time") == true) {
			auto value = this->post_json->GetValue("time");
			if (value->GetType() == VTYPE_DOUBLE) {
				auto time = value->GetDouble();
				if (time <= playback_ptr->playback_get_length()) {
					playback_ptr->playback_seek(time);
					this->response->add_string("{\"status\":\"success\"}");
				} else {
					this->response->add_string("{\"status\":\"fail\",\"detial\":\"parameters out of range\"}");
				}
			} else {
				this->response->add_string("{\"status\":\"fail\",\"detial\":\"wrong type of parameters\"}");
			}
		} else {
			this->response->add_string("{\"status\":\"fail\",\"detial\":\"lack parameters\"}");
		}
		break;
	}
	case 0x00007: {
		CefRefPtr<CefDictionaryValue> json_root = CefDictionaryValue::Create();
		CefRefPtr<CefValue> json_value = CefValue::Create();
		json_root->SetString("status", "success");
		json_root->SetDouble("time", playback_ptr->playback_get_length());
		json_value->SetDictionary(json_root);
		this->response->add_string(CefWriteJSON(json_value, JSON_WRITER_DEFAULT).ToString().c_str());
		break;
	}
	case 0x00008: {
		CefRefPtr<CefDictionaryValue> json_root = CefDictionaryValue::Create();
		CefRefPtr<CefValue> json_value = CefValue::Create();
		json_root->SetString("status", "success");
		json_root->SetDouble("time", playback_ptr->playback_get_position());
		json_value->SetDictionary(json_root);
		this->response->add_string(CefWriteJSON(json_value, JSON_WRITER_DEFAULT).ToString().c_str());
		break;
	}
	}
	this->finish();
}

service_ptr_t<main_thread_callback> APIPlayControl::factory(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response) {
	return new service_impl_t<APIPlayControl>(post_json, callback, data_out, offest, bytes_to_read, response);
}