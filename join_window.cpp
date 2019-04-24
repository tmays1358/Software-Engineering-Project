#include "join_window.hpp"

Join_window::Join_window(int maxX, int maxY)
{
    int sizeX = maxX/2;
    int sizeY = maxY/2;
    join_win = newwin(sizeY, sizeX, maxY/5, maxX/5);
	room_win = derwin(join_win, 3, sizeX-12, 4, 11);
	key_win = derwin(join_win, 3, sizeX-12, 7, 11);
    room_num = derwin(join_win, 3, sizeX-12, 10, 11);
    ok_button = derwin(join_win, 3, 4, sizeY-5, sizeX/3);
	cancel_button = derwin(join_win, 3, 8, sizeY-5, sizeX/3+10);

	for(int i = 0; i < sizeX-11; i++)
		input_clear.push_back(' ');
    
    mvwprintw(join_win, 2, sizeX/3, "Join");
	mvwprintw(join_win, 5, 1, "Room name:");
	mvwprintw(join_win, 8, 1, "Key: ");
    mvwprintw(join_win, 11, 1, "Room #: ");
	mvwprintw(ok_button, 1, 1, "OK");
	mvwprintw(cancel_button, 1, 1, "CANCEL");
    box(room_num, 0 ,0);
	box(join_win, 0, 0);
	box(room_win, 0, 0);
	box(key_win, 0, 0);
	box(ok_button, 0, 0);
	box(cancel_button, 0, 0);
}

bool Join_window::get_input()
{
    keypad(stdscr, true);
    int ch;
    int curr_window = 0;
    bool not_done = true;
    bool option = false;

    wmove(room_win, 1, 1);
    wrefresh(room_win);
    while(not_done)
    {
		ch = getch();
		if(ch == KEY_UP || ch == KEY_LEFT){
            curr_window--; 
            if(curr_window < 0) 
                    curr_window = 0;
            highlight_window (curr_window);
        }
        else if(ch == KEY_DOWN || ch == KEY_RIGHT)
        {
            curr_window++;
            if (curr_window > 4)
                    curr_window = 4;
            highlight_window(curr_window);
        }
		else if (ch == 10) //this means enter
        {
                switch(curr_window){
                    case 0: //room name
                        getwinput(room_win, room_str);
                        break;
                    case 1: //key
                        getwinput(key_win, key_str);
                        break;
                    case 2: //room number
                        getwinput(room_num, room_num_str);
                        break;
                    case 3: // ok
                        not_done = false;
                        option =  true;
                        break;
                    case 4: // cancel
                        not_done = false;
                        option = false;
                        break;
                    default:
                        break;
			}
		}
    }
    keypad(stdscr, false);
    return option;
}

void Join_window::getwinput(WINDOW *win, std::string &str){
        wmove(win, 1, str.size() + 1);
        wrefresh(win);
        int ch = ' ';
        while(ch != '\n'){
                ch = getch();

                if((ch == KEY_BACKSPACE || ch == KEY_DC) && str.size() > 0)
                        str.pop_back();
                else if(ch != '\n')
                        str.push_back(ch);
                mvwprintw(win, 1, 1, input_clear.c_str()); //clear input
                mvwprintw(win, 1, 1, str.c_str());
                show();
		wrefresh(win);
        }
}
void Join_window::highlight_window(int selected){
        switch(selected){
                case 0:
                        wmove(room_win, 1, 1);
			            wrefresh(room_win);
                        break;
                case 1:
                        wmove(key_win, 1,1);
			            wrefresh(key_win);
                        break;
                case 2:
                        wmove(room_num, 1, 1);
                        wrefresh(room_num);
                        break;
                case 3:
                        wmove(ok_button, 1,1);
                        wrefresh(ok_button);
                        break;
                case 4:
                        wmove(cancel_button, 1,1);
                        wrefresh(cancel_button);
                        break;
	}
}
void Join_window::show()
{
    box(room_num, 0 , 0);
    box(join_win, 0, 0);
	box(room_win, 0, 0);
	box(key_win, 0, 0);
	box(ok_button, 0, 0);
	box(cancel_button, 0, 0);

	refresh();
    wrefresh(room_num);
	wrefresh(cancel_button);
	wrefresh(room_win);
	wrefresh(key_win);
	wrefresh(ok_button);
	wrefresh(join_win);
    return;
}

std::string Join_window::get_room_str()
{
    return room_str;
}
std::string Join_window::get_key_str()
{
    return key_str;
}
std::string Join_window::get_room_num_str()
{
    return room_num_str;
}