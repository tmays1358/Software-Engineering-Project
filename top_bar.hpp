#ifndef TOP_BAR
#define TOP_BAR

#include <ncurses.h>
#include <string>

class Top_bar
{
    public:
        Top_bar(int maxX, int maxY, std::string usrname, std::string curr_rm);
        int get_input();
        void set_rm_name(std::string room_name);
        void highlight(int select);
        void show();
        void mvmenu();
    private:
        WINDOW *top_win;
        WINDOW *join;
        WINDOW *manage;
        WINDOW *leave;
        std::string username;
        std::string curr_room;
};


#endif