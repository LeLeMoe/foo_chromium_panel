#pragma once

class APIBase : public main_thread_callback {
public:
	APIBase(CefRefPtr<CefDictionaryValue> post_json, CefRefPtr<CefResourceReadCallback> callback, void* data_out, size_t *offest, int bytes_to_read, pfc::string8 *response);
	virtual ~APIBase() = default;

public:
	void callback_run() = 0;
	void finish();

protected:
	CefRefPtr<CefDictionaryValue> post_json;
	pfc::string8* response;

private:
	CefRefPtr<CefResourceReadCallback> callback;
	void* data_out;
	size_t* offest;
	int bytes_to_read;
};