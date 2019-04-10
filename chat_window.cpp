#include "chat_window.hpp"

//constructor
Chat_window::Chat_window(int maxX, int maxY){
	int sizeY = 3;
	int sizeX = 4 * maxX/5 -2;
	msg_win = newwin(sizeY, sizeX, maxY-3, maxX/5+2);
	box(msg_win, 0, 0);
	file_select_button = false;
	for(int i = 0; i < sizeX - 1; i++)
		input_clear.push_back(' ');

}
void Chat_window::get_input(){
	wmove(msg_win, 1, 1);
	wrefresh(msg_win);
	keypad(stdscr, true);	
	keypad(msg_win, true);
	getwinput(msg_win, user_msg);
	keypad(msg_win, false);
}

void Chat_window::getwinput(WINDOW *win, std::string &str){
	wmove(win, 1, str.size() + 1);
        wrefresh(win);
        int ch = ' ';
        while(ch != '\n'){
                ch = getch();
                if((ch == KEY_BACKSPACE || ch == KEY_DC) && str.size() > 0)
                        str.pop_back();
                else if(ch != '\n')
                        str.push_back(ch);
                mvwprintw(win, 1, 1, input_clear.c_str()); //clear input
                mvwprintw(win, 1, 1, str.c_str());
                show();
                wrefresh(win);
        }
}


//window control
void Chat_window::update(){
	return;
}
void Chat_window::show(){
	box(msg_win, 0, 0);
	refresh();
	wrefresh(msg_win);
	return;
}

//user functionality
void Chat_window::on_select_select(){
	return;
}
void Chat_window::on_enter_sent(){
	return;
}
void Chat_window::on_tab_enter(){
	return;
}
void Chat_window::set_user_msg(std::string str){
	user_msg = str;
	return;
}
std::string Chat_window::get_user_msg(){
	return user_msg;
}
