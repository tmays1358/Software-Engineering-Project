#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include <ncurses.h> 
#include <string>

class Login_window
{
    public:
        Login_window(int maxX, int maxY);
        void show();
        void update();
        void get_input();
	void getwinput(WINDOW *win, std::string &str);
	void highlight_window(int selected);
	std::string get_username_input();
	std::string get_password_input();
	void on_login_select();
        void on_signup_select();
    private:
	WINDOW *login;
	WINDOW *username_window;
	WINDOW *password_window;
	WINDOW *login_button;
	WINDOW *signup_button;
        std::string username_input;
        std::string password_input;
	std::string input_clear;
};

#endif
