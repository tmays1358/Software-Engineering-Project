#ifndef ROOM_WINDOW
#define ROOM_WINDOW

#include <ncurses.h>
#include <string>
#include <vector>

class Room_window
{
    public:
        Room_window(int maxX, int maxY);
        void get_input();
        void add_room(std::string new_room);
        void remove_room(int room_index);
        int get_current_room_select();
        void set_current_room_select(int room_select);
        std::string get_current_room_name(int room_selection);
        void show();
        void mvmenu();
    private:
        int current_room_select;
        WINDOW *room_win;
        std::vector<std::string> rooms;
};

#endif
