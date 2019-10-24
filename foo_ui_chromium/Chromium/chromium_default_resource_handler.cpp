#include "../stdafx.h"

ChromiumDefaultSourceHandler::ChromiumDefaultSourceHandler() : reposnd("{}"), offest(0) {}

bool ChromiumDefaultSourceHandler::Open(CefRefPtr<CefRequest> request, bool &handle_request, CefRefPtr<CefCallback> callback) {
	CEF_REQUIRE_IO_THREAD();
	handle_request = true;
	return true;
}

void ChromiumDefaultSourceHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) {
	CEF_REQUIRE_IO_THREAD();
	response->SetMimeType("application/json");
	response->SetStatus(400);
	response_length = 2;
}

bool ChromiumDefaultSourceHandler::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback) {
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

void ChromiumDefaultSourceHandler::Cancel() {
	CEF_REQUIRE_IO_THREAD();
}