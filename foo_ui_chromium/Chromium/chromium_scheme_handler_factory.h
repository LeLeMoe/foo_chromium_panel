#pragma once

class ChromiumSchemeHandlerFactory : public CefSchemeHandlerFactory {
public:
	ChromiumSchemeHandlerFactory();
	~ChromiumSchemeHandlerFactory() = default;

public:
	CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override;

public:
	using SchemeFactory = service_ptr_t<main_thread_callback>(*)(CefRefPtr<CefDictionaryValue>, CefRefPtr<CefResourceReadCallback>, void*, size_t*, int, pfc::string8*);

private:
	void register_scheme_factory();

private:
	pfc::map_t<int, SchemeFactory> scheme_factory_map;
	IMPLEMENT_REFCOUNTING(ChromiumSchemeHandlerFactory);
};