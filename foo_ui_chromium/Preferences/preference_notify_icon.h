#pragma once

extern cfg_bool cfg_use_custom_icon;
extern cfg_string cfg_custom_icon_url;
extern cfg_bool cfg_al_show_icon;
extern cfg_bool cfg_min_to_icon;

class PreferenceNotifyIcon : public CDialogImpl<PreferenceNotifyIcon>, public preferences_page_instance {
public:
	PreferenceNotifyIcon(preferences_page_callback::ptr callback);
	~PreferenceNotifyIcon() = default;

public:
	t_uint32 get_state() override;
	void apply() override;
	void reset() override;

public:
	enum { IDD = IDD_PREFERENCE_NOTIFY_ICON };

	BEGIN_MSG_MAP(PreferenceTaskbar)
		MSG_WM_INITDIALOG(on_init_dialog)
		COMMAND_HANDLER_EX(IDC_CHECK_AL_SHOW_ICO, BN_CLICKED, on_check_clicked)
		COMMAND_HANDLER_EX(IDC_CHECK_MIN_TO_ICO, BN_CLICKED, on_check_clicked)
		COMMAND_HANDLER_EX(IDC_CHECK_EN_CUS_ICO, BN_CLICKED, on_cus_icon_check_clicked)
		COMMAND_HANDLER_EX(IDC_BUTTON_EN_CUS_ICO, BN_CLICKED, on_icon_button_clicked)
		MSG_WM_DESTROY(on_destory)
	END_MSG_MAP()

public:
	void on_changed();
	void on_check_clicked(UINT wNotifyCode, int wID, HWND hWndCtl);
	bool on_init_dialog(CWindow, LPARAM);
	void on_cus_icon_check_clicked(UINT wNotifyCode, int wID, HWND hWndCtl);
	void on_icon_button_clicked(UINT wNotifyCode, int wID, HWND hWndCtl);
	bool on_destory();

private:
	bool has_changed;
	HFONT title_font_large;
	preferences_page_callback::ptr callback_function;
};

class PreferenceTaskbarImpl : public preferences_page_impl<PreferenceNotifyIcon> {
public:
	const char* get_name() override;
	GUID get_guid() override;
	GUID get_parent_guid() override;
};