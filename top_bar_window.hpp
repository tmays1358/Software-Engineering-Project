#ifndef TOP_BAR_WINDOW
#define TOP_BAR_WINDOW

#include "about_tab_window.hpp"
#include "help_tab_window.hpp"
#include "setting_tab_window.hpp"
#include "profile_tab_window.hpp"

class Top_bar_window {
	public:
		Top_bar_window();
	private:
		Profile_tab_window profile_win;
		About_tab_window about_win;
		Help_tab_window help_win;
		Setting_tab_window setting_win;
};

#endif
