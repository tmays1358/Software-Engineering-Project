#ifndef SIGNUP_WINDOW
#define SIGNUP_WINDOW

#include <string>

class Signup_window
{
    public:
        Signup_window();
        void show();
        void update();
        void on_signup_select();
        void on_cancel_select();
    private:
        std::string name;
        std::string email;
        std::string username;
        std::string password;
};

#endif
