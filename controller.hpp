#include "view.hpp"

class Controller{
	public:
		Controller(Client& c, Server& s, View& v) : client(c), server(s), view(v) {};
		void cli();
		void execute_cmd(int);
	private:
		View& view;
		Client& client;
		Server& server;
};
