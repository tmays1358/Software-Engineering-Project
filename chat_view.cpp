#include "chat_view.hpp"

Chat_view::Chat_view(int maxX, int maxY){
	int sizeX = 4*maxX/5-1;
	int sizeY = maxY - 6;
	chat_view = newwin(sizeY, sizeX, 3, maxX/5+1);
	str_win = derwin(chat_view, sizeY-2, sizeX-2, 1, 1);
	box(chat_view, 0, 0);
	scrollok(str_win, true);
	scrollok(chat_view, true);
}

void Chat_view::new_msg(std::string str, int line){
	mvwprintw(str_win, line, 0, "%s", str.c_str());	
	show();
}

void Chat_view::show(){
	box(chat_view, 0, 0);
	refresh();
	wrefresh(str_win);
	wrefresh(chat_view);
}
