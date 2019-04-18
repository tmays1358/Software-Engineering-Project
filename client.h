#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "server.h"
#include <stdio.h>

class Client{
 public: 
	bool request_join_room(int room, int key);
	bool request_create_room();
	bool request_delete_room(int room_number);
	bool block_user(char *username);
	bool spell_check(char message);
	int change_room_view(int room_num);

private:
	char current_user;
	vector<char> list_block_user;
};
#endif
