#pragma once

extern cfg_string cfg_main_url;

class PreferenceMain : public CDialogImpl<PreferenceMain>, public preferences_page_instance {
public:
	PreferenceMain(preferences_page_callback::ptr callback);
	~PreferenceMain() = default;

public:
	t_uint32 get_state() override;
	void apply() override;
	void reset() override;

public:
	enum { IDD = IDD_PREFERENCE_MAIN };

	BEGIN_MSG_MAP(PreferenceMain)
		MSG_WM_INITDIALOG(on_init_dialog)
		COMMAND_HANDLER_EX(IDC_BUTTON_URL, BN_CLICKED, on_url_button_clicked)
		COMMAND_HANDLER_EX(IDC_EDIT_URL, EN_CHANGE, on_url_edit_changed)
		MSG_WM_DESTROY(on_destory)
	END_MSG_MAP()

public:
	void on_changed();
	bool on_init_dialog(CWindow, LPARAM);
	void on_url_button_clicked(UINT wNotifyCode, int wID, HWND hWndCtl);
	void on_url_edit_changed(UINT wNotifyCode, int wID, HWND hWndCtl);
	bool on_destory();

private:
	const preferences_page_callback::ptr callback_function;
	HFONT title_font_large;
	bool has_changed;
};

class PreferenceMainImpl : public preferences_page_impl<PreferenceMain> {
public:
	const char* get_name() override;
	GUID get_guid() override;
	GUID get_parent_guid() override;
};