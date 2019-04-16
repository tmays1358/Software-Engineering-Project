#ifndef MANAGE_WINDOW
#define MANAGE_WINDOW

#include <ncurses.h>
#include <string>
class Manage_window
{
    public:
        Manage_window(int maxX, int maxY);
        bool get_input();
        void getwinput(WINDOW *win, std::string &str);
        void highlight_window(int selected);
        void show();
        std::string get_mute_username();
        bool get_delete_button();
    private:
        WINDOW *manage_win;
        WINDOW *delete_win;
        WINDOW *mute_win;
        WINDOW *ok_button;
        WINDOW *cancel_button;
        std::string mute_username;
        bool delete_button;
        std::string input_clear;
};

#endif