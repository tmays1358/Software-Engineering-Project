#ifndef SETTINGS_TAB_WINDOW
#define SETTINGS_TAB_WINDOW

#include <string>

class Setting_tab_window {
	public:
		Setting_tab_window();
		void on_ok_select();
		void on_cancel_select();
	private:
		std::string user_name_input;
		std::string email_input;
		std::string password_input;
};

#endif
