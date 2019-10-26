#include "../stdafx.h"

ChromiumResourceHandler::ChromiumResourceHandler(ChromiumResourceHandler::SchemeFactory factory, CefRefPtr<CefDictionaryValue> post_json) :
	factory(factory), post_json(post_json), api_ins(nullptr), response(""), offest(0) {}

bool ChromiumResourceHandler::Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) {
	CEF_REQUIRE_IO_THREAD();
	handle_request = true;
	callback->Continue();
	return true;
}

void ChromiumResourceHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) {
	CEF_REQUIRE_IO_THREAD();
	CefResponse::HeaderMap header_map;
	header_map.insert(std::make_pair("Access-Control-Allow-Origin", "*"));
	response->SetHeaderMap(header_map);
	response->SetMimeType("text/plain");
	response->SetStatus(200);
	response_length = -1;
}

bool ChromiumResourceHandler::Read(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefResourceReadCallback> callback) {
	CEF_REQUIRE_IO_THREAD();
	if (this->api_ins == nullptr) {
		this->api_ins = this->factory(this->post_json, callback, data_out, &this->offest, bytes_to_read, &this->response);
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(this->api_ins);
		bytes_read = 0;
		return true;
	} else {
		bool has_data = false;
		bytes_read = 0;
		if (this->offest < this->response.get_length()) {
			int transfer_size = min(bytes_to_read, static_cast<int>(this->response.get_length() - this->offest));
			memcpy(data_out, this->response.c_str() + this->offest, transfer_size);
			this->offest += transfer_size;
			bytes_read = transfer_size;
			has_data = true;
		}
		return has_data;
	}
}

void ChromiumResourceHandler::Cancel() {
	CEF_REQUIRE_IO_THREAD();
}