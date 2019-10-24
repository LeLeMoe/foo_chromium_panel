#pragma once

class APIBase : public CefResourceHandler {
public:
	APIBase(CefRefPtr<CefDictionaryValue> json);
	virtual ~APIBase() = default;

public:
	void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) override;
	bool ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback) override;
	void Cancel() override;

protected:
	pfc::string8 reposnd;
	CefRefPtr<CefDictionaryValue> json_request;
	int status_code;

private:
	size_t offest;
};