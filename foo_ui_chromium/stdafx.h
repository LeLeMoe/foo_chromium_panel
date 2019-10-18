#pragma once

// Sdk files
#include <helpers/foobar2000+atl.h>
#include <helpers/atl-misc.h>
#include <pfc/pfc.h>

// Windows
#include <WinUser.h>
#include <Windows.h>
#include <Shobjidl.h>

// Cef
#include <include/cef_app.h>
#include <include/cef_client.h>
#include <include/cef_browser.h>
#include <include/cef_life_span_handler.h>
#include <include/cef_request_handler.h>
#include <include/cef_browser_process_handler.h>
#include <include/internal/cef_types_wrappers.h>
#include <include/internal/cef_win.h>
#include <include/wrapper/cef_helpers.h>
#include <include/wrapper/cef_message_router.h>

// Project
#include "Resources/resource.h"
#include "Misc/config.h"
#include "Misc/message_object.h"
#include "Misc/helper.h"
#include "Misc/notify_icon.h"
#include "Chromium/chromium_client.h"
#include "Chromium/chromium_app.h"
#include "Misc/user_interface_chromium.h"
#include "Preferences/preference_main.h"
#include "Preferences/preference_private.h"
#include "Preferences/preference_notify_icon.h"