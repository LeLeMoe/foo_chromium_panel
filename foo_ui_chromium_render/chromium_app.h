#pragma once

class ChromiumApp : public CefApp, public CefRenderProcessHandler {
public:
	ChromiumApp() = default;

public:
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;
};