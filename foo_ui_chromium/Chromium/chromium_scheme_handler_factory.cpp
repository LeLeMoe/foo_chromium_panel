#include "../stdafx.h"

ChromiumSchemeHandlerFactory::ChromiumSchemeHandlerFactory() : scheme_factory_map() {
	this->register_scheme_factory();
}

CefRefPtr<CefResourceHandler> ChromiumSchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) {
	CEF_REQUIRE_IO_THREAD();
	CefPostData::ElementVector element_vector;
	request->GetPostData()->GetElements(element_vector);
	auto bytes_num = element_vector[0]->GetBytesCount();
	auto bytes = new char[bytes_num + 1];
	bytes[bytes_num] = '\0';
	element_vector[0]->GetBytes(bytes_num, bytes);
	auto value = CefParseJSON(bytes, JSON_PARSER_ALLOW_TRAILING_COMMAS);
	delete[] bytes;
	if (value == NULL) {
		return new ChromiumDefaultSourceHandler;
	} else if (value->GetType() != VTYPE_DICTIONARY) {
		return new ChromiumDefaultSourceHandler;
	} else {
		auto value_object = value->GetDictionary();
		if (value_object->HasKey("cmd") == false) {
			return new ChromiumDefaultSourceHandler;
		} else if(value_object->GetType("cmd") != VTYPE_STRING) {
			return new ChromiumDefaultSourceHandler;
		} else {
			auto cmd_string = value_object->GetValue("cmd")->GetString().ToString();
			auto factory_ptr = *this->scheme_factory_map.query_ptr(pfc::string8(cmd_string.c_str()));
			if (factory_ptr != NULL) {
				return factory_ptr(value_object);
			} else {
				return new ChromiumDefaultSourceHandler;
			}
		}
	}
}

void ChromiumSchemeHandlerFactory::register_scheme_factory() {
	// Play control
	this->scheme_factory_map.set(pfc::string8("fb2k.play_control.play"), &APIPlayControl::api_factory);
	this->scheme_factory_map.set(pfc::string8("fb2k.play_control.pause"), &APIPlayControl::api_factory);
	this->scheme_factory_map.set(pfc::string8("fb2k.play_control.play_or_pause"), &APIPlayControl::api_factory);
	this->scheme_factory_map.set(pfc::string8("fb2k.play_control.stop"), &APIPlayControl::api_factory);
	this->scheme_factory_map.set(pfc::string8("fb2k.play_control.next"), &APIPlayControl::api_factory);
	this->scheme_factory_map.set(pfc::string8("fb2k.play_control.previous"), &APIPlayControl::api_factory);
}