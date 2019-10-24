#include "../stdafx.h"

APIBase::APIBase(CefRefPtr<CefDictionaryValue> json) : reposnd(""), json_request(json), status_code(200), offest(0) {}

void APIBase::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) {
	CEF_REQUIRE_IO_THREAD();
	response->SetMimeType("application/json");
	response->SetStatus(this->status_code);
	response_length = this->reposnd.get_length();
}

bool APIBase::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback) {
	CEF_REQUIRE_IO_THREAD();
	bool has_data = false;
	bytes_read = 0;
	if (this->offest < this->reposnd.get_length()) {
		int transfer_size = min(bytes_to_read, static_cast<int>(this->reposnd.get_length() - this->offest));
		memcpy(data_out, this->reposnd.c_str() + this->offest, transfer_size);
		this->offest += transfer_size;
		bytes_read = transfer_size;
		has_data = true;
	}
	return has_data;
}

void APIBase::Cancel() {
	CEF_REQUIRE_IO_THREAD();
}