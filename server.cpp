#include "server.h"
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
else
{
	string username1 = change_username(std::string username);
	std::cout << "Your username will be" << username1 << std::endl;
	list_of_users.insert(pair<std::string, std::string>(username1,password));
}

return 0;
}

bool check_user_credentials(std::string username_l, std::string password_l)
{
//inherit two strings from log in(sign in) page//
string username_l = login_window.get_username_input(),password_l = login_window.get_password_input();
if (list_of_users[username_l] != password_l)
//access denied// //reload sign in page//
else
{	//access granted// 
	//load new window//
}

return 0;

}

int create_room(int room_num)
//add room button pressed//
//inherit room num//
char x;
if (std::find(list_of_rooms.begin(), list_of_rooms.end(), room_num) != list_of_rooms.end() )
{
	std::cout << "Room already present. Do you want to join that room?[Y/N] " <<std::endl;
	std::cin >> char x;
	if(x == 'Y')
	//join_room//
	else{
	 std::cout << "Type in a new room number: " <<std::endl;
	std::cin >> int new_num;
	int create_room(int new_num);
}
else
{
	list_of_rooms.insert(list_of_rooms.begin(), room_num);
	//create_room//
}

return 0;
}

int delete_room(int room_num, int key)
//delete room button pressed//
if(std::find(list_of_rooms.begin(), list_of_rooms.end(), room_num != list_of_rooms.end())
{

	list_of_romms.erase (std::distance(list_of_rooms.begin(), room_num);
	//go to lobby chat room view//
}
else
	std::cout << "Incorrecr Credentials";

return 0;
}

int main(){

return 0;
}
