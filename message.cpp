#include "message.hpp"
//skeleton still
message::message()
{
	message_content = "no content";
	time_stamp = "A random Time";
	author_stamp = "Gary87";
	message_type = 1;
}

int message::get_message_type() const
{
	return message_type;
}

string message::get_time_stamp() const
{
        return time_stamp;
}

string message::get_author_stamp() const
{
        return author_stamp;
}

string message::get_message_content() const
{
        return message_content;
}


void message::set_message_type(int mt)
{
        message_type = mt;
}

void message::set_time_stamp(string ts)
{
        time_stamp = ts;
}

void message::set_author_stamp()
{
       author_stamp = user::get_username();
}

void message::set_message_content(string mc)
{
        message_content = mc;
}

