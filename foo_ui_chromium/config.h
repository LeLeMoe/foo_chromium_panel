#pragma once

// Version
constexpr auto FOO_UI_CHROMIUM_NAME = "Chromium UI";
constexpr auto FOO_UI_CHROMIUM_VERSION = "0.9.0";
constexpr auto FOO_UI_CHROMIUM_FILENAME = "foo_ui_chromium.dll";

// GUID
#define GUID_USER_INTERFACE { 0x7fd0c17b, 0xa650, 0x4207, { 0xbf, 0x24, 0xb5, 0x7f, 0x9, 0xf0, 0x5, 0xd1 } }
#define GUID_PREFERENCE_MAIN { 0x85c28c2, 0xe0d3, 0x436e, { 0x86, 0xc0, 0xda, 0x8f, 0xb9, 0xf, 0x73, 0x87 } }

// Windows
constexpr auto FOO_UI_CHROMIUM_WINDOW_CLASS = L"98A1EF29-E327-4399-93AF-76BC7EE061D0";
constexpr auto FOO_UI_CHROMIUM_SUB_FILENAME = "foo_ui_chromium_render.exe";
constexpr auto FOO_UI_CHROMIUM_WINDOW_NAME = L"foobar2000";

// Text
constexpr auto FOO_UI_CHROMIUM_MSGBOX_TITLE = L"Chromium UI Error";
constexpr auto FOO_UI_CHROMIUM_MSGBOX_WINDOW_FAILED = L"Can't create window.";
constexpr auto FOO_UI_CHROMIUM_NSGBOX_CEF3_FAILED = L"Can't initialize cef3.";

// Message pipe
constexpr auto PIPE_MESSAGE_NAME = L"\\\\.\\pipe\\336DDD17-12C0-4892-BC9F-9703EE346796";
constexpr unsigned int PIPE_WAIT_TIME = 1000;