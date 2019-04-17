#include "top_bar.hpp"

Top_bar::Top_bar(int maxX, int maxY, std::string uname, std::string curr_rm)
{
    int sizeX = maxX-1;
    int sizeY = 3;
    username = uname;
    curr_room = curr_rm;
    top_win = newwin(sizeY, sizeX, 0, 0);
    leave = derwin(top_win, 3, 5, 0, sizeX-6);
    manage = derwin(top_win, 3, 9, 0, sizeX-15);
    join = derwin(top_win, 3, 7, 0, sizeX-23);
    mvwprintw(top_win,  1, 1, username.c_str());
    mvwprintw(top_win, 1, username.length() + 1, " | ");
    mvwprintw(top_win, 1, username.length() + 4, curr_room.c_str());
    mvwprintw(leave, 1, 0, "Leave");
    mvwprintw(manage, 1, 0, "Manage | ");
    mvwprintw(join, 1, 0, "Join | ");    
    box(top_win, 0, 0);
}

int Top_bar::get_input()
{
    keypad(stdscr, true);

    int curr_window = 0;
    bool not_done = true;
    int ch;
    wmove(join, 1, 0);
    wrefresh(join);
    while(not_done)
    {
		ch = getch();
		if(ch == KEY_UP || ch == KEY_LEFT){
            curr_window--; 
            if(curr_window < 0) 
                    curr_window = 0;
            highlight(curr_window);
        }
        else if(ch == KEY_DOWN || ch == KEY_RIGHT)
        {
            curr_window++;
            if (curr_window > 2)
                    curr_window = 2;
            highlight(curr_window);
        }
		else if (ch = 10) //this means enter
        {
            not_done = false;
        }
    }
    keypad(stdscr, false);
    return curr_window;
}
void Top_bar::highlight(int select){
    switch(select)
    {
        case 0:
            wmove(join, 1, 0);
            wrefresh(join);
            break;
        case 1:
            wmove(manage, 1, 0);
            wrefresh(manage);
            break;
        case 2:
            wmove(leave, 1, 0);
            wrefresh(leave);
            break;
    }
}

void Top_bar::set_rm_name(std::string room_name)
{
    curr_room = room_name;
    mvwprintw(top_win, 1, username.length() + 4, "                         ");
    mvwprintw(top_win, 1, username.length() + 4, curr_room.c_str());
    show();    
}

void Top_bar::show()
{
    box(top_win, 0, 0);
    refresh();
    wrefresh(top_win);
    wrefresh(join);
    wrefresh(manage);
    wrefresh(leave);
}

void Top_bar::mvmenu()
{
    show();
    wmove(top_win, 1, 1);
    refresh();
    wrefresh(top_win);
}