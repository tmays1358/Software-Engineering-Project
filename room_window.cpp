#include "room_window.hpp"

Room_window::Room_window(int maxX, int maxY)
{
    current_room_select = 0;
    int sizeX = maxX / 5 ;
    int sizeY = maxY - 3;
    room_win = newwin(sizeY, sizeX, 3, 0);
    rooms[0] = "Lobby";
    mvwprintw(room_win, 1, 1, rooms[0].c_str());
    box(room_win, 0, 0);
    scrollok(room_win, true);
}

void Room_window::add_room(std::string new_room, int position)
{
    if(position > 0 && position < 11) //testing if max capacity
    {
        rooms[position] = new_room;
        for (int i = 0; i < 11; i++)
        {
            mvwprintw(room_win, i + 1, 1, rooms[i].c_str());
        }
        show();
    }
}

std::string Room_window::get_current_room_name(int room_selection)
{
    return rooms[room_selection];
}

void Room_window::remove_room(int room_index)
{
    wclear(room_win);
    rooms[room_index] = " ";
    for (int i = 0; i < 11; i++)
    {
        mvwprintw(room_win, i + 1, 1, rooms[i].c_str());
    }
    show();
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
            if (current_room_select > 11-1)
                current_room_select = 11-1;
            wmove(room_win, current_room_select+1, 1);
            wrefresh(room_win);
        }
        else if (ch == 10) //this means enter
        {
            not_done = false;
		}
    }

    keypad(stdscr, false);
    keypad(room_win, false);
}
void Room_window::set_current_room_select(int room_select)
{
    current_room_select = room_select;
}
int Room_window::get_current_room_select()
{
    return current_room_select;
}
int Room_window::get_num_of_rooms()
{
    return 11;
}
void Room_window::show()
{
    for (int i = 0; i < 11; i++)
    {
        mvwprintw(room_win, i + 1, 1, rooms[i].c_str());
    }
    box(room_win, 0, 0);
    wmove(room_win, 1, 1);
    refresh();
    wrefresh(room_win);
    return;
}
void Room_window::mvmenu()
{
    wmove(room_win, 1, 1);
    show();
    return;
}