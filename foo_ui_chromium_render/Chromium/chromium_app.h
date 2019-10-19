#pragma once

class ChromiumApp : public CefApp, public CefRenderProcessHandler {
public:
	ChromiumApp() = default;
	~ChromiumApp() = default;

public:
	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;
	void OnWebKitInitialized() override;

private:
	IMPLEMENT_REFCOUNTING(ChromiumApp);
};