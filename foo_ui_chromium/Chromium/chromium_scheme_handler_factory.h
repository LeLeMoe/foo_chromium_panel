#pragma once

class ChromiumSchemeHandlerFactory : public CefSchemeHandlerFactory {
public:
	ChromiumSchemeHandlerFactory();
	~ChromiumSchemeHandlerFactory() = default;

public:
	CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override;

public:
	using SchemeFactory = CefRefPtr<CefResourceHandler>(*)(CefRefPtr<CefDictionaryValue>);

private:
	void register_scheme_factory();

private:
	pfc::map_t<pfc::string8, SchemeFactory> scheme_factory_map;
	IMPLEMENT_REFCOUNTING(ChromiumSchemeHandlerFactory);
};