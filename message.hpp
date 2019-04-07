#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <string>
#include <iomanip>
#include <iostream>
#include "user.hpp"
//need to include the user.hpp when its done
using namespace std;

class message : public user
{
	public:
		message();
		message(string mc, string ts, string as, int mt): message_content(mc), time_stamp(ts), author_stamp(as), message_type(mt){};
		string get_message_content() const;
		string get_time_stamp() const;
		string get_author_stamp() const;
		int get_message_type() const;
		void set_message_content(string);
		void set_time_stamp(string);
		void set_author_stamp();
		void set_message_type(int);
	private:
		int message_type;
		string message_content;
		string time_stamp;
		string author_stamp;
};
#endif
