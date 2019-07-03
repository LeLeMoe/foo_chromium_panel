#pragma once

class ChromiumMessageHandler : public CefMessageRouterBrowserSide::Handler {
public:
	ChromiumMessageHandler() = default;
	~ChromiumMessageHandler() = default;

public:
	virtual bool OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id, const CefString& request, bool persistent, CefRefPtr<Callback> callback) override;

private:
	bool message_fb2k_play(const CefString &request, pfc::string &result);
	bool message_fb2k_pause(const CefString &request, pfc::string &result);
	bool message_fb2k_next(const CefString &request, pfc::string &result);
	bool message_fb2k_previous(const CefString &request, pfc::string &result);
};