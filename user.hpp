#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

class user
{
	public:
		user();
		user(string un, string fn, string e, string pw): username(un), full_name(fn), email(e), password(pw){};
		string get_username() const;
		string get_full_name() const;
		string get_email() const;
		string get_password() const;
		void set_username(string);
		void set_full_name(string);
		void set_email(string);
		void set_password(string);

		void modify_username(string);
		void modify_email(string);
		void modify_password(string);
	protected:
		string username;
		string full_name;
		string email;
		string password;
};
#endif

