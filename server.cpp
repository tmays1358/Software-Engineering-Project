#include "server.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

string last_time_on;
std::map<std::string,std::string> list_of_users;
std::vector<int> list_of_rooms(10);

std::string change_username(std::string username){
std::string a = " _01"
std::string username1 = username + a;
return username1;
}

bool create_user(std::string username, std::string password)
{
//inherit two strings from when the user sign up//

string username = signup_win.get_username(),password = signup_win.get_password;
if (list_of_users[username] == NULL)
list_of_users.insert(pair<std::string, std::string>(username,password));
return true;
/*else
{
	string username1 = change_username(std::string username);
	std::cout << "Your username will be" << username1 << std::endl;
	list_of_users.insert(pair<std::string, std::string>(username1,password));
	return true;
}*/

return false;
}

bool check_user_credentials(std::string username_l, std::string password_l)
{
//inherit two strings from log in(sign in) page//
string username_l = login_window.get_username_input(),password_l = login_window.get_password_input();
if (list_of_users[username_l] != password_l)
{
return false;
//access denied// //reload sign in page//
}
return true;

}

bool create_room()
//add room button pressed//
int a = 1;
if (list_of_rooms.size() != list_of_rooms.max_size())
{
	list_of_rooms.insert(list_of_rooms.begin(), a);
	return true;
//create_room//
}
return false;
}

bool delete_room(int room_num, int key)
//delete room button pressed//
if(chat_participant.participants_.size() == 1)
{

	list_of_romms.erase (list_of_rooms.begin());
	//go to lobby chat room view//
	return true;
}
return false;
}

int main(){

return 0;
}
