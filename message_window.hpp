#ifndef MESSAGE_WINDOW
#define MESSAGE_WINDOW

#include <string>

class Message_window
{
    public:
        Message_window();
        void on_ok_select();
        void on_cancel_select();
        void show();
        void update();
    private:
        string mute_user_name;
        bool delete_server_option;
};

#endif
