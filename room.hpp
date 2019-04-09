#ifndef ROOM_HPP
#define ROOM_HPP
#include <string>
#include <iomanip>
#include "user.hpp"
#include <vector>
//#include <bool>
using namespace std;
class room : public user
{
	public:
		room();
		room(vector<user>, string rn, int ri, int k): room_name(rn), room_int(ri), key(k){};

		string get_room_name() const;
		int get_room_int() const;
		int get_key() const;

		void set_room_name(string);
		void set_room_int(int);
		void set_key(int);

		bool remove_user(user u);
		bool add_user(user u);
	private:
		vector<user> List;
		string room_name;
		int room_int;
		int key;
};
#endif

