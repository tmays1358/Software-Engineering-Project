#ifndef SIGNUP_WIN
#define SIGNUP_WIN

#include <ncurses.h>
#include <string>
class Signup_win {
	public:
		Signup_win(int maxY, int maxX);
		void show();
		bool get_input();
		void getwinput(WINDOW *win, std::string &str);
		void highlight_window(int selected);
		std::string get_name();
		std::string get_email();
		std::string get_username();
		std::string get_password();
		void on_ok_select();
		void on_cancel_select();
	private:
		std::string input_clear;
                std::string name;
                std::string email;
		std::string username;
                std::string password;
                WINDOW *signup;
                WINDOW *name_window;
                WINDOW *email_window;
                WINDOW *username_window;
		WINDOW *password_window;
                WINDOW *ok_button;
                WINDOW *cancel_button;

};

#endif
