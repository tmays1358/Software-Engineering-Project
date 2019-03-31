#ifndef CHAT_WIN
#define CHAT_WIN
#include <string>

class Chat_window{
	public:
		Chat_window();
		void update();
		void show();
		void on_select_select();
		void on_enter_sent();
		void on_tab_enter();
	private:
		bool file_select_button;
		std::string user_msg;
};
#endif
