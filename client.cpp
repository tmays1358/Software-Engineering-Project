#include "client.h"
#include <vector>

std::vector<int> list_of_rooms (10);
bool request_join_room(int room, int key)
{
	if(key == set_key(room))
        list_of_rooms.push_back(room);
        return true;
    else
        return false;

}

bool request_create_room()
{
	if (list_of_rooms.size() == list_of_rooms.max_size())
	    return false;
	else
	    list_of_rooms.push_back (1);
    
    return true;
}

bool request_delete_room(int room_num)
{
    if (list_of_rooms.size() == 0)
        return false;
    else
        list_of_rooms.pop_back(room_num);
        return true;
}

bool block_user(char *username)
{
	current_user = username;
	list_block_user.insert(current_user);

    return true;
}

bool logout();
{
	
    return 0;
}

bool send_message();
{
	
    return 0;
}

char* spell_check(char message);
{
	
    return line;
}

int change_room_view(int room_num)
{
	show(room_num);

    return 0;
}

/*int main()
{

    return 0;
}*/
