#include "server.h"

std::string change_username(std::string username){
std::string a = " _01"
std::string username1 = username + a;
return username1;
}

bool create_user(std::string username, std::string password)
{
//inherit two strings from when the user sign up//

if (list_of_users[username] == NULL){
list_of_users.insert(pair<std::string, std::string>(username,password));
return true;}

return false;
}

bool check_user_credentials(std::string username_l, std::string password_l)
{
//inherit two strings from log in(sign in) page//
if (list_of_users[username_l] != password_l)
{
return false;
//access denied// //reload sign in page//
}
return true;

}

bool create_room(){
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

bool delete_room(int room_num, int key){
//delete room button pressed//
if(chat_participant::participants_.size() == 1)
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
