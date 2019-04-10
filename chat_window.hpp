#ifndef CHAT_WIN
#define CHAT_WIN
#include <ncurses.h>
#include <string>

class Chat_window{
	public:
		Chat_window(int maxX, int maxY);
		void get_input();
		void getwinput(WINDOW *win, std::string &str);
		void update();
		void show();
		void on_select_select();
		void on_enter_sent();
		void on_tab_enter();
		void set_user_msg(std::string str);
		std::string get_user_msg();
	private:
		WINDOW *msg_win;
		bool file_select_button;
		std::string user_msg;
		std::string input_clear;
};
#endif
