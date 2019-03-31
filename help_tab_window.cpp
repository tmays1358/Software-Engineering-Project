#include "help_tab_window.hpp"

//constructor
Help_tab_window::Help_tab_window(){
	for(int i = 0; i < 10; i++){
		std::string cmd = "cmd ";
		list_of_commands.push_back(cmd + std::to_string(i));
	}
}

//window manager
void Help_tab_window::show(){
	return;
}
void Help_tab_window::update(){
	return;
}

//user input
void Help_tab_window::on_ok_select(){
	return;
}
