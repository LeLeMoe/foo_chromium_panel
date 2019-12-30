#pragma once

// Plugin information
constexpr auto FOO_UI_CHROMIUM_NAME = "Chromium UI";
constexpr auto FOO_UI_CHROMIUM_VERSION = "0.9.0";
constexpr auto FOO_UI_CHROMIUM_FILENAME = "foo_ui_chromium.dll";

// Prefernece main window
#define FOO_UI_CHROMIUM_GUID_USER_INTERFACE { 0x7fd0c17b, 0xa650, 0x4207, { 0xbf, 0x24, 0xb5, 0x7f, 0x9, 0xf0, 0x5, 0xd1 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_PRIVATE_WINDOW_X { 0x4a2272f6, 0x7909, 0x49e3, { 0xaa, 0xe6, 0x86, 0x25, 0x90, 0x48, 0xad, 0x84 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_PRIVATE_WINDOW_Y { 0x33b318dd, 0xed02, 0x4174, { 0xb4, 0x91, 0x58, 0xfe, 0x81, 0x57, 0xc3, 0xa2 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_PRIVATE_WINDOW_WIDTH { 0x1b4a1b34, 0x5efc, 0x47ac, { 0xa9, 0x6f, 0xdc, 0x96, 0xdb, 0xdd, 0xd2, 0xd0 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_PRIVATE_WINDOW_HEIGHT { 0xdb4fdf05, 0x5476, 0x4f70, { 0x8a, 0xce, 0x14, 0xd9, 0x9d, 0xbc, 0x8d, 0x57 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_PRIVATE_WINDOW_MAX { 0x20c1d649, 0x801c, 0x48ba, { 0x80, 0x1e, 0x91, 0xa1, 0xa7, 0x4d, 0xeb, 0xc7 } }
constexpr auto FOO_UI_CHROMIUM_WINDOW_CLASS = L"98A1EF29-E327-4399-93AF-76BC7EE061D0";
constexpr auto FOO_UI_CHROMIUM_WINDOW_NAME = L"foobar2000";

// Preference Main
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_MAIN { 0x85c28c2, 0xe0d3, 0x436e, { 0x86, 0xc0, 0xda, 0x8f, 0xb9, 0xf, 0x73, 0x87 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_MAIN_URL { 0x95e88f64, 0x8f05, 0x409c, { 0x80, 0xf7, 0x8d, 0x49, 0xa4, 0xaf, 0x33, 0xb5 } }

// Prefernece notify icon
#define FOO_UI_CHROMIUM_GUID_NOTIFY_ICON { 0x94f692a7, 0xc171, 0x45a3, { 0x8d, 0xdf, 0x61, 0x75, 0x8b, 0x9, 0xf7, 0xdc } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON { 0x71de79ba, 0x978, 0x493e, { 0x91, 0xac, 0xba, 0xce, 0xb3, 0x27, 0xf4, 0xb } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON_USE_CUSTOM_ICON { 0x25d33996, 0x9244, 0x4d8c, { 0xa0, 0xa5, 0xa3, 0xb3, 0x7a, 0x64, 0x70, 0xb2 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON_CUSTOM_ICON_URL { 0x5a722a4d, 0xb788, 0x4b76, { 0xbb, 0x37, 0xb2, 0xf2, 0x7f, 0x73, 0x3, 0x36 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON_AL_SHOW_ICON { 0xff7e8547, 0x1588, 0x4d57, { 0x98, 0xfb, 0xfa, 0x57, 0xba, 0x57, 0x58, 0xd5 } }
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_NOTIFY_ICON_MIN_TO_ICON { 0xb219208b, 0x1bf9, 0x4ae4, { 0xa5, 0x25, 0xfd, 0x46, 0x41, 0xa6, 0x9c, 0x73 } }
constexpr auto FOO_UI_CHROMIUM_MENU_PREFERENCE = 0x03;
constexpr auto FOO_UI_CHROMIUM_MENU_OPEN = 0x02;
constexpr auto FOO_UI_CHROMIUM_MENU_EXIT = 0x01;
constexpr auto FOO_UI_CHROMIUM_MSG_ICONBAR = 0x2A00;
constexpr auto FOO_UI_CHROMIUM_PREFERNECE_NOTIFY_ICON_NAME = "Notify Icon";

// Preference developer
#define FOO_UI_CHROMIUM_GUID_PREFERENCE_DEVELOPER_LOG { 0x32a333f5, 0xdcd3, 0x4826, { 0xab, 0x9d, 0xef, 0x45, 0xbc, 0x2f, 0xf0, 0xfd } }

// Render
constexpr auto FOO_UI_CHROMIUM_SUB_FILENAME = "foo_ui_chromium_render.exe";

// Cef API
constexpr auto FOO_UI_CHROMIUM_API_POST_ADDRESS = "2B2BE8EB-336D-4E5B-9BA3-000D7BC6B097";