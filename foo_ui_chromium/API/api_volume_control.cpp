#include "../stdafx.h"

APIVolumeControl::APIVolumeControl(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response) :
	APIBase(post_json, callback, data_out, offest, bytes_to_read, response) {}

void APIVolumeControl::callback_run() {
	auto playback_ptr = static_api_ptr_t<playback_control_v3>();
	switch (this->post_json->GetValue("cmd")->GetInt()) {
	case 0x00100: {
		playback_ptr->volume_up();
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00101: {
		playback_ptr->volume_down();
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00102: {
		playback_ptr->set_volume(playback_ptr->volume_mute);
		this->response->add_string("{\"status\":\"success\"}");
		break;
	}
	case 0x00103: {
		if (this->post_json->HasKey("volume") == true) {
			auto value = this->post_json->GetValue("volume");
			if (value->GetType() == VTYPE_DOUBLE) {
				auto volume = value->GetDouble();
				if (volume <= 0 && volume >= playback_ptr->volume_mute) {
					playback_ptr->set_volume(volume);
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
	case 0x00104: {
		CefRefPtr<CefDictionaryValue> json_root = CefDictionaryValue::Create();
		CefRefPtr<CefValue> json_value = CefValue::Create();
		json_root->SetString("status", "success");
		json_root->SetDouble("volume", playback_ptr->get_volume());
		json_value->SetDictionary(json_root);
		this->response->add_string(CefWriteJSON(json_value, JSON_WRITER_DEFAULT).ToString().c_str());
		break;
	}
	}
	this->finish();
}

service_ptr_t<main_thread_callback> APIVolumeControl::factory(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response) {
	return new service_impl_t<APIVolumeControl>(post_json, callback, data_out, offest, bytes_to_read, response);
}