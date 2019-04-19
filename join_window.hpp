#ifndef JOIN_WINDOW
#define JOIN_WINDOW

#include <ncurses.h>
#include <string>

class Join_window
{
    public:
        Join_window(int maxX, int maxY);
        bool get_input();
        void getwinput(WINDOW *win, std::string &str);
        void show();
        void highlight_window(int selected);
        std::string get_room_str();
        std::string get_key_str();
        std::string get_room_num_str();
    private:
        WINDOW *join_win;
        WINDOW *room_win;
        WINDOW *key_win;
        WINDOW *room_num;
        WINDOW *ok_button;
        WINDOW *cancel_button;
        std::string room_num_str;
        std::string room_str;
        std::string key_str;
        std::string input_clear;
};

#endif
