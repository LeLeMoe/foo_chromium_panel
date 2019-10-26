#pragma once

class ChromiumDefaultSourceHandler : public CefResourceHandler {
public:
	ChromiumDefaultSourceHandler();
	~ChromiumDefaultSourceHandler() = default;

public:
	bool Open(CefRefPtr<CefRequest> request, bool &handle_request, CefRefPtr<CefCallback> callback) override;
	void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) override;
	bool ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback) override;
	void Cancel() override;

private:

	pfc::string8 response;
	size_t offest;
	IMPLEMENT_REFCOUNTING(ChromiumDefaultSourceHandler);
};