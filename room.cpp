#include "room.hpp"

room::room()
{
	room_name = "Lobby";
	room_int = 0;
	key = 0;
}
string room::get_room_name() const
{
	return room_name;
}
int room::get_room_int() const
{
        return room_int;
}  
int room::get_key() const
{
        return key;
}

void room::set_room_name(string rn)
{
        room_name = rn;
}
void room::set_room_int(int ri)
{
        room_int = ri;
}
void room::set_key(int k)
{
        key = k;
}

bool room::remove_user(user u)
{
	for(int i=0; i < List.size(); i++){
		if(List[i].get_username() == u.get_username()){
			List.erase(List.begin()+i);
		}
	}
}

bool room::add_user(user u)
{
	int there = 0;
	for(int i=0; i < List.size(); i++){
                if(List[i].get_username() == u.get_username()){
                        List.push_back(u);
		}
        }

}
