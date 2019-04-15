#include "signup_win.hpp"

Signup_win::Signup_win(int maxY, int maxX){
	int sizeY = maxY/2;
        int sizeX = maxX/2;

        signup = newwin(sizeY, sizeX, maxY/5, maxX/5);
        name_window = derwin (signup,3, sizeX-12, 4, 11);
        email_window = derwin (signup, 3, sizeX-12, 7, 11);
        username_window = derwin (signup, 3, sizeX-12, 10, 11);
        password_window = derwin (signup, 3, sizeX-12, 13, 11);
	ok_button = derwin (signup, 3, 4, sizeY-5, sizeX/3);
	cancel_button = derwin (signup, 3, 8, sizeY-5, sizeX/3+6);
			
	mvwprintw(signup, 2, sizeX/3, "SIGN UP");
	mvwprintw(signup, 5, 1, "Full name:");
	mvwprintw(signup, 8, 1, "Email:");
	mvwprintw(signup, 11, 1, "Username:");
	mvwprintw(signup, 14, 1, "Password:");
	mvwprintw(ok_button, 1, 1, "OK");
	mvwprintw(cancel_button, 1, 1, "CANCEL");
	for(int i = 0; i < sizeX-11; i++)
		input_clear.push_back(' ');
        	
	box(signup, 0, 0);
        box(name_window, 0, 0);
        box(email_window, 0, 0);
        box(username_window, 0, 0);
        box(password_window, 0,0);
	box(ok_button, 0, 0);
	box(cancel_button, 0, 0);
}
void Signup_win::show()
{
	box(signup, 0, 0);
        box(name_window, 0, 0);
        box(email_window, 0, 0);
        box(username_window, 0, 0);
        box(password_window, 0,0);
        box(ok_button, 0, 0);
        box(cancel_button, 0, 0);

	refresh();
	wrefresh(name_window);
	wrefresh(email_window);
	wrefresh(username_window);
	wrefresh(password_window);
	wrefresh(ok_button);
	wrefresh(cancel_button);
	wrefresh(signup);	
}
bool Signup_win::get_input()
{
	keypad(stdscr, true);
	keypad(signup, true);
	keypad(name_window, true);
	keypad(email_window, true);
	keypad(username_window, true);
	keypad(password_window, true);
			
	int ch;
	int curr_window = 0;
	bool not_done = true;
	bool option = false;
	wmove(name_window, 1,1);
	wrefresh(name_window);
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
			if (curr_window > 5)
				curr_window = 5;
			highlight_window(curr_window);	
				
		}
		else if (ch = 10) //this means enter
		{
			switch(curr_window){
				case 0: //name
					getwinput(name_window, name);
					break;
				case 1: //email
					getwinput(email_window, email);
					break;
				case 2: // username
					getwinput(username_window, username);
					break;
				case 3: //password
					getwinput(password_window, password);
					break;
				case 4: // ok 
					not_done = false;
					option = true;
					break;
				case 5: //cancel 
					not_done = false;
					option = false;
					break;
				default:
					break;	
			}
		}

	}
	keypad(stdscr, false);
        keypad(signup, false);
        keypad(name_window, false);
        keypad(email_window, false);
        keypad(username_window, false);
        keypad(password_window, false);
	return option;
}
		
void Signup_win::getwinput(WINDOW *win, std::string &str){
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
                show(); //needed to keep boxes in shape
		wrefresh(win);
        }	
}
		
void Signup_win::highlight_window(int selected){
	switch(selected){
		case 0:
			wmove(name_window, 1,1);
			wrefresh(name_window);
			break;
		case 1:
			wmove(email_window, 1,1);
			wrefresh(email_window);
			break;
		case 2:
			wmove(username_window, 1,1);
			wrefresh(username_window);
			break;
		case 3:
			wmove(password_window, 1,1);
			wrefresh(password_window);
			break;
		case 4:
			wmove(ok_button, 1,1);
			wrefresh(ok_button);
			break;
		case 5:
			wmove(cancel_button, 1,1);
			wrefresh(cancel_button);
			break;
	}
}

std::string Signup_win::get_name(){
	return name;
}
std::string Signup_win::get_email(){
	return email;
}
std::string Signup_win::get_username(){
	return username;
}
std::string Signup_win::get_password(){
	return password;
}
void Signup_win::on_ok_select(){
	return;
}
void Signup_win::on_cancel_select(){
	return;
}
