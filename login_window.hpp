#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include <string>

class Login_window
{
    public:
        Login_window();
        void show();
        void update();
        void on_login_select();
        void on_signup_select();
    private:
        std::string username_input;
        std::string password_input;
};

#endif
