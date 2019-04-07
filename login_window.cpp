#include "login_window.hpp"

Login_window::Login_window(int maxY, int maxX)
{
	int sizeY = maxY/2;
	int sizeX = maxX/2;
	
	login = newwin(sizeY, sizeX, maxY/4, maxX/4);
	username_window = derwin(login, 3, sizeX-12, 4, 11);
	password_window = derwin(login, 3, sizeX-12, 7, 11);
	login_button = derwin(login, 3, 7, sizeY-5, sizeX/3);
	signup_button = derwin(login, 3, 9, sizeY-5, sizeX/3+10);

	mvwprintw(login, 2, sizeX/3, "SuperChat Login");
	mvwprintw(login, 5, 1, "Username:");
	mvwprintw(login, 8, 1, "Password:");
	mvwprintw(login_button, 1, 1, "Login");
	mvwprintw(signup_button, 1, 1, "Sign up");
	
	for(int i = 0; i < sizeX-11; i++)
		input_clear.push_back(' ');
	box(login, 0, 0);
	box(username_window, 0, 0);
	box(password_window, 0, 0);
	box(login_button, 0, 0);
	box(signup_button, 0, 0);
}

void Login_window::show()
{
	box(login, 0, 0);
        box(username_window, 0, 0);
        box(password_window, 0, 0);
        box(login_button, 0, 0);
        box(signup_button, 0, 0);

	refresh();
	wrefresh(username_window);
	wrefresh(password_window);
	wrefresh(login_button);
	wrefresh(signup_button);
	wrefresh(login);
	return;
}

void Login_window::update()
{

	return;
}
void Login_window::get_input(){
	keypad(stdscr, true);
	keypad(login, true);
	keypad(username_window, true);
	keypad(password_window, true);
	keypad(login_button, true);
	keypad(signup_button, true);

	int ch;
	int curr_window = 0;
	bool not_done = true;

	wmove(username_window, 1, 1);
	wrefresh(username_window);
	
	while(not_done){
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
		else if (ch = 10) //this means enter
                {
                        switch(curr_window){
                                case 0: //username
                                        getwinput(username_window, username_input);
                                        break;
                                case 1: //passwword
                                        getwinput(password_window, password_input);
                                        break;
                                case 2: // login
                                        not_done = false;
                                        break;
                                case 3: // signup
                                        not_done = false;
                                        break;
                                default:
                                        break;
			}
		curr_window++;
		}	
	}

	keypad(stdscr, false);
        keypad(login, false);
        keypad(username_window, false);
        keypad(password_window, false);
        keypad(login_button, false);
        keypad(signup_button, false);

}
void Login_window::getwinput(WINDOW *win, std::string &str){
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
void Login_window::highlight_window(int selected){
        switch(selected){
                case 0:
                        wmove(username_window, 1,1);
			wrefresh(username_window);
                        break;
                case 1:
                        wmove(password_window, 1,1);
			wrefresh(password_window);
                        break;
                case 2:
                        wmove(login_button, 1,1);
                        wrefresh(login_button);
                        break;
                case 3:
                        wmove(signup_button, 1,1);
                        wrefresh(signup_button);
                        break;
	}
}
std::string Login_window::get_username_input(){
	return username_input;
}
std::string Login_window::get_password_input(){
	return password_input;
}
void Login_window::on_login_select()
{
    return;
}

void Login_window::on_signup_select()
{
    return;
}
