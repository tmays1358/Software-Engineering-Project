#ifndef ROOM_WINDOW
#define ROOM_WINDOW

#include <ncurses.h>
#include <string>

class Room_window
{
    public:
        Room_window(int maxX, int maxY);
        void get_input();
        int get_current_room_select();
        void show();
    private:
        int current_room_select;
        WINDOW *room_win;
};

#endif
