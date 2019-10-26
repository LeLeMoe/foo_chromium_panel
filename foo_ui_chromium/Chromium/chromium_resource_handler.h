#pragma once

class ChromiumResourceHandler : public CefResourceHandler {
public:
	using SchemeFactory = service_ptr_t<main_thread_callback>(*)(CefRefPtr<CefDictionaryValue>, CefRefPtr<CefResourceReadCallback>, void*, size_t*, int, pfc::string8*);

public:
	ChromiumResourceHandler(SchemeFactory factory, CefRefPtr<CefDictionaryValue> post_json);
	~ChromiumResourceHandler() = default;

public:
	bool Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) override;
	void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) override;
	bool Read(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefResourceReadCallback> callback) override;
	void Cancel() override;

private:
	size_t offest;
	pfc::string8 response;
	service_ptr_t<main_thread_callback> api_ins;
	SchemeFactory factory;
	CefRefPtr<CefDictionaryValue> post_json;
	IMPLEMENT_REFCOUNTING(ChromiumResourceHandler);
};