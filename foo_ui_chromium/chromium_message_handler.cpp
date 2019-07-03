#include "stdafx.h"
#include "chromium_message_handler.h"

bool ChromiumMessageHandler::OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id, const CefString& request, bool persistent, CefRefPtr<Callback> callback) {
	pfc::string result;
	// fb2k.play
	if (request.compare(FOO_UI_CEF_API_FB2K_PLAY) >= 0) {
		if (this->message_fb2k_play(request, result) == true) {
			callback->Success(result.c_str());
		} else {
			callback->Failure(FOO_UI_CEF_API_ERROR_NONE, result.c_str());
		}
		return true;
	// fb2k.pause
	} else if (request_native.contains(FOO_UI_CEF_API_FB2K_PAUSE) >= 0) {
		if (this->message_fb2k_pause(request, result) == true) {
			callback->Success(result.c_str());
		} else {
			callback->Failure(FOO_UI_CEF_API_ERROR_NONE, result.c_str());
		}
		return true;
	// fb2k.next
	} else if (request_native.contains(FOO_UI_CEF_API_FB2K_NEXT) >= 0) {
		if (this->message_fb2k_next(request, result) == true) {
			callback->Success(result.c_str());
		} else {
			callback->Failure(FOO_UI_CEF_API_ERROR_NONE, result.c_str());
		}
		return true;
	// fb2k.previous
	} else if (request_native.contains(FOO_UI_CEF_API_FB2K_PREVIOUS) >= 0) {
		if (this->message_fb2k_previous(request, result) == true) {
			callback->Success(result.c_str());
		} else {
			callback->Failure(FOO_UI_CEF_API_ERROR_NONE, result.c_str());
		}
		return true;
	}
	return false;
}

bool ChromiumMessageHandler::message_fb2k_play(const CefString &request, pfc::string &result) {
	standard_commands::main_play();
	return true;
}

bool ChromiumMessageHandler::message_fb2k_pause(const CefString &request, pfc::string &result) {
	standard_commands::main_pause();
	return true;
}

bool ChromiumMessageHandler::message_fb2k_next(const CefString &request, pfc::string &result) {
	standard_commands::main_next();
	return true;
}

bool ChromiumMessageHandler::message_fb2k_previous(const CefString &request, pfc::string &result) {
	standard_commands::main_previous();
	return true;
}