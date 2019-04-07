#include "user.hpp"

user::user()
{
	username = "Gary87";
	full_name = "Gary Snail";
	email = "email@uta.edu";
	password = "12345";
}

string user::get_username() const
{
	return username;
}

string user::get_full_name() const
{
        return full_name;
}
string user::get_email() const
{
        return email;
}

string user::get_password() const
{
        return password;
}



void user::set_username(string us)
{
        username = us;
}

void user::set_full_name(string fn)
{
        full_name = fn;
}

void user::set_email(string e)
{
        email = e;
}

void user::set_password(string pw)
{
        password = pw;
}

void user::modify_username(string nus)
{
	user::set_username(nus);
}

void user::modify_email(string ne)
{
	user::set_username(ne);
}
void user::modify_password(string npw)
{
	user::set_username(npw);
}

