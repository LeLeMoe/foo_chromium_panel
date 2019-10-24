#pragma once

class APIPlayControl : public APIBase {
public:
	APIPlayControl(CefRefPtr<CefDictionaryValue> json);
	virtual ~APIPlayControl() = default;

public:
	bool Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) override;


public:
	static CefRefPtr<CefResourceHandler> api_factory(CefRefPtr<CefDictionaryValue> json);

private:
	class MainThreadCallbackPlay : public main_thread_callback {
	public:
		void callback_run() override;
	};
	class MainThreadCallbackPause : public main_thread_callback {
	public:
		void callback_run() override;
	};
	class MainThreadCallbackPlayOrPause : public main_thread_callback {
	public:
		void callback_run() override;
	};
	class MainThreadCallbackStop : public main_thread_callback {
	public:
		void callback_run() override;
	};
	class MainThreadCallbackNext : public main_thread_callback {
	public:
		void callback_run() override;
	};
	class MainThreadCallbackPrevious : public main_thread_callback {
	public:
		void callback_run() override;
	};

private:
	IMPLEMENT_REFCOUNTING(APIPlayControl);
};