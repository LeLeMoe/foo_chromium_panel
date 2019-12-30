#include "../stdafx.h"

ChromiumSchemeHandlerFactory::ChromiumSchemeHandlerFactory() : scheme_factory_map() {
	this->register_scheme_factory();
}

CefRefPtr<CefResourceHandler> ChromiumSchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) {
	CEF_REQUIRE_IO_THREAD();
	CefPostData::ElementVector element_vector;
	if (request->GetPostData() == nullptr) {
		return new ChromiumDefaultSourceHandler;
	}
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
		} else if(value_object->GetType("cmd") != VTYPE_INT) {
			return new ChromiumDefaultSourceHandler;
		} else {
			auto cmd_code = value_object->GetValue("cmd")->GetInt();
			auto factory_ptr = *this->scheme_factory_map.query_ptr(cmd_code);
			if (factory_ptr != NULL) {
				return new ChromiumResourceHandler(factory_ptr, value_object);
			} else {
				return new ChromiumDefaultSourceHandler;
			}
		}
	}
}

void ChromiumSchemeHandlerFactory::register_scheme_factory() {
	// Play control
	this->scheme_factory_map.set(0x00000, &APIPlayControl::factory);
	this->scheme_factory_map.set(0x00001, &APIPlayControl::factory);
	this->scheme_factory_map.set(0x00002, &APIPlayControl::factory);
	this->scheme_factory_map.set(0x00003, &APIPlayControl::factory);
	this->scheme_factory_map.set(0x00004, &APIPlayControl::factory);
	this->scheme_factory_map.set(0x00005, &APIPlayControl::factory);
	this->scheme_factory_map.set(0x00006, &APIPlayControl::factory);
	this->scheme_factory_map.set(0x00007, &APIPlayControl::factory);
	this->scheme_factory_map.set(0x00008, &APIPlayControl::factory);
	// Volume control
	this->scheme_factory_map.set(0x00100, &APIVolumeControl::factory);
	this->scheme_factory_map.set(0x00101, &APIVolumeControl::factory);
	this->scheme_factory_map.set(0x00102, &APIVolumeControl::factory);
	this->scheme_factory_map.set(0x00103, &APIVolumeControl::factory);
	this->scheme_factory_map.set(0x00104, &APIVolumeControl::factory);
}