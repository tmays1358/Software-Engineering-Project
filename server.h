#ifndef _SERVER_H_
#define _SERVER_H_
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include "chat_server.cpp"

class Server: protected chat_participant{
public:
	bool create_room();
	bool delete_room();
	std::string change_username(std::string username);
	bool create_user(std::string username, std::string password);
	bool check_user_credentials(std::string username_l, std::string password_l);

private:
	string last_time_on;
	std::map<std::string, std::string> list_of_users;
	std::vector<int> list_of_rooms(10);
};
#endif
