#include "manage_window.hpp"

Manage_window::Manage_window(int maxX, int maxY)
{
    int sizeX = maxX/2;
    int sizeY = maxY/2;
    manage_win = newwin(sizeY, sizeX, maxY/5, maxX/5);
	delete_win = derwin(manage_win, 3, 3, 4, 11);
	mute_win = derwin(manage_win, 3, sizeX-12, 7, 11);
    ok_button = derwin(manage_win, 3, 4, sizeY-5, sizeX/3);
	cancel_button = derwin(manage_win, 3, 8, sizeY-5, sizeX/3+10);

	for(int i = 0; i < sizeX-11; i++)
		input_clear.push_back(' ');
    
    mvwprintw(manage_win, 2, sizeX/3, "Join");
	mvwprintw(manage_win, 5, 1, "Log out:");
	mvwprintw(manage_win, 8, 1, "Mute user: ");
	mvwprintw(ok_button, 1, 1, "OK");
	mvwprintw(cancel_button, 1, 1, "CANCEL");
	box(manage_win, 0, 0);
	box(delete_win, 0, 0);
	box(mute_win, 0, 0);
	box(ok_button, 0, 0);
	box(cancel_button, 0, 0);
}

bool Manage_window::get_input()
{
    keypad(stdscr, true);
    int ch;
    int curr_window = 0;
    bool not_done = true;
    bool option = false;

    wmove(delete_win, 1, 1);
    wrefresh(delete_win);
    char buffer;
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
            if (curr_window > 3)
                    curr_window = 3;
            highlight_window(curr_window);
        }
        else if (ch == 10) //this means enter
        {
            switch(curr_window){
                case 0: //delete
                    if(delete_button){
                        mvwprintw(delete_win, 1, 1, " ");
                        wmove(delete_win, 1, 1);
                        wrefresh(delete_win);
                        delete_button = false;
                    }
                    else{
                        mvwprintw(delete_win, 1, 1, "*");
                        wmove(delete_win, 1, 1);
                        wrefresh(delete_win);
                        delete_button = true;
                    }
                    break;
                case 1: //passwword
                    getwinput(mute_win, mute_username);
                    break;
                case 2: // login
                    not_done = false;
                    option =  true;
                    break;
                case 3: // signup
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

void Manage_window::getwinput(WINDOW *win, std::string &str){
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

void Manage_window::show()
{
    box(manage_win, 0, 0);
	box(delete_win, 0, 0);
	box(mute_win, 0, 0);
	box(ok_button, 0, 0);
	box(cancel_button, 0, 0);

	refresh();
	wrefresh(cancel_button);
	wrefresh(mute_win);
	wrefresh(delete_win);
	wrefresh(ok_button);
	wrefresh(manage_win);
    return;
}

void Manage_window::highlight_window(int selected){
        switch(selected){
                case 0:
                        wmove(delete_win, 1, 1);
			            wrefresh(delete_win);
                        break;
                case 1:
                        wmove(mute_win, 1, 1);
			            wrefresh(mute_win);
                        break;
                case 2:
                        wmove(ok_button, 1,1);
                        wrefresh(ok_button);
                        break;
                case 3:
                        wmove(cancel_button, 1,1);
                        wrefresh(cancel_button);
                        break;
	}
}

std::string Manage_window::get_mute_username()
{
    return mute_username;
}
bool Manage_window::get_delete_button()
{
    return delete_button;
}