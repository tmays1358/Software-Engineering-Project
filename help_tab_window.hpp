#ifndef HELP_TAB_WINDOW
#define HELP_TAB_WINDOW
#include <string>
#include <vector>

class Help_tab_window{
	public:
		Help_tab_window();
		void show();
		void update();
		void on_ok_select();
	private:
		std::vector<std::string> list_of_commands;
};

#endif
