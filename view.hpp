#ifndef VIEW
#define VIEW

#include "chat_window.hpp"
#include "top_bar_window.hpp"
#include "room_window.hpp"
#include "info_top_window.hpp"
#include "chat_window.hpp"
#include "server.hpp"
#include "client.hpp"
#include "controller.hpp"
#include "login_window.hpp"
#include "signup_window.hpp"

class View
{
    public:
        View();
        void show(int win);
        void update();
        void on_window_select(int current_window_num);
        void init();
    private:
        Chat_window chat_win;
        Top_bar_window top_win;
        Room_window room_win;
        Info_top_window info_top_win;
        int current_window_selected;
        Server server_reference;
        Client client_reference;
        Login_window login_win;
        Signup_window signup_win;
};

#endif
