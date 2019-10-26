#pragma once

class APIPlayControl : public APIBase {
public:
	APIPlayControl(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response);
	virtual ~APIPlayControl() = default;

public:
	void callback_run();

public:
	static service_ptr_t<main_thread_callback> factory(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t* offest, int bytes_to_read, pfc::string8* response);
};