#ifndef _SERVER_H_
#define _SERVER_H_

class Server{
public:
	void update_message_log(char message);
	int create_room(int key);
	int delete_room(int room_num, int key);
	bool create_user(std::string username, std::string password);
	bool check_user_credentials(std::string username_l, std::string password_l);

private:
	string last_time_on;
	std::map<std::string, std::string> list_of_users;
	std::vector<int> list_of_rooms;
};
#endif
