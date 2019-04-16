#include "room_window.hpp"

Room_window::Room_window(int maxX, int maxY)
{
    current_room_select = 0;
    int sizeX = maxX / 5 ;
    int sizeY = maxY - 3;
    room_win = newwin(sizeY, sizeX, 3, 0);
    std::string room;
    for (int i = 0; i < 10; i++)
    {
        room = "room " + std::to_string(i);
        mvwprintw(room_win, i + 1, 1, room.c_str());
    }
    box(room_win, 0, 0);
    scrollok(room_win, true);
}

void Room_window::get_input()
{
    keypad(stdscr, true);
    keypad(room_win, true);

    int ch;
    bool not_done = true;
    wmove(room_win, current_room_select + 1, 1);
    wrefresh(room_win);
    while (not_done)
    {
        ch = getch();
        if (ch == KEY_UP || ch == KEY_LEFT)
        {
            current_room_select--;
            if (current_room_select < 0)
                current_room_select = 0;
            wmove(room_win, current_room_select+1, 1);
            wrefresh(room_win);
        }
        else if (ch == KEY_DOWN || ch == KEY_RIGHT)
        {
            current_room_select++;
            if (current_room_select > 9)
                current_room_select = 9;
            wmove(room_win, current_room_select+1, 1);
            wrefresh(room_win);
        }
        else if (ch = 10) //this means enter
        {
            not_done = false;
		}
    }

    keypad(stdscr, false);
    keypad(room_win, false);
}

int Room_window::get_current_room_select()
{
    return current_room_select;
}

void Room_window::show()
{
    box(room_win, 0, 0);
    wrefresh(room_win);
    refresh();
    return;
}