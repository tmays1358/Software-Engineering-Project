#include "top_bar_window.hpp"

Top_bar_window::Top_bar_window(){
	profile_win = new Profile_tab_window::Profile_tab_window();
	about_win = new About_tab_window::About_tab_window();
	help_win = new Help_tab_window::Help_tab_window();
	setting_win = new Setting_tab_window::Setting_tab_window();
}
