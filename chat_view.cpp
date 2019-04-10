#include "chat_view.hpp"

Chat_view::Chat_view(int maxX, int maxY){
	int sizeX = 4*maxX/5 - 2;
	int sizeY = maxY - 9;
	chat_view = newwin(sizeY, sizeX, 6, maxX/5+2);
	box(chat_view, 0, 0);
	scrollok(chat_view, true);
}

void Chat_view::new_msg(std::string str, int line){
	mvwprintw(chat_view, line, 1, "%s", str.c_str());
	show();
}

void Chat_view::show(){
	box(chat_view, 0, 0);
	refresh();
	wrefresh(chat_view);
}
