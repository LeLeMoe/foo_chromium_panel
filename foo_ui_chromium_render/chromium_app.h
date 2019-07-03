#pragma once

class ChromiumApp : public CefApp, public CefRenderProcessHandler {
public:
	ChromiumApp() = default;

public:
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;
	virtual void OnWebKitInitialized() override;
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
	virtual void OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;

private:
	void register_extension();

private:
	CefRefPtr<CefMessageRouterRendererSide> message_router;
	IMPLEMENT_REFCOUNTING(ChromiumApp);
};