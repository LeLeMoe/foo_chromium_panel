#include "../stdafx.h"

APIBase::APIBase(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response) :
	post_json(post_json), callback(callback), response(response), data_out(data_out), offest(offest), bytes_to_read(bytes_to_read) {}

void APIBase::finish() {
	int bytes_read = 0;
	int transfer_size = min(this->bytes_to_read, static_cast<int>(this->response->get_length()));
	memcpy(data_out, this->response->c_str(), transfer_size);
	*this->offest += transfer_size;
	this->callback->Continue(transfer_size);
}