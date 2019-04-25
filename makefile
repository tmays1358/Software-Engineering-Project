CXX=g++

CXXFLAGS=-Wall -g -std=c++11

#change this CPPFLAG TO MATCH your library location
#for best results move asio-1.12.2 to home folder
CPPFLAGS=-I/home/`whoami`/asio-1.12.2/include

all:chat_client chat_server sorted_words

#sort words for easy indexing
sorted_words: words.txt
	cat words.txt | sort >> sorted_words.txt

#test the successful compilation of object files
object_files: chat_window.o  signup_win.o login_window.o chat_view.o room_window.o top_bar.o join_window.o manage_window.o

#client and server
chat_client.o: chat_client.cpp chat_message.hpp
chat_server.o: chat_server.cpp chat_message.hpp

#**************VIEW GOES HERE**********************************
login_window.o: login_window.cpp login_window.hpp
	${CXX} -c login_window.cpp login_window.hpp -lncurses
signup_win.o: signup_win.cpp signup_win.hpp
	${CXX} -c signup_win.cpp signup_win.hpp -lncurses
chat_window.o: chat_window.cpp chat_window.hpp
	${CXX} -c chat_window.cpp chat_window.hpp -lncurses
chat_view.o: chat_view.cpp chat_view.hpp
	${CXX} -c chat_view.cpp chat_view.hpp -lncurses
room_window.o: room_window.cpp room_window.hpp
	${CXX} -c room_window.cpp room_window.hpp -lncurses
top_bar.o: top_bar.cpp top_bar.hpp
	${CXX} -c top_bar.cpp top_bar.hpp -lncurses
join_window.o: join_window.cpp join_window.hpp
	${CXX} -c join_window.cpp join_window.hpp -lncurses
manage_window.o: manage_window.cpp manage_window.hpp
	${CXX} -c manage_window.cpp manage_window.hpp -lncurses

#*************final exec goes here*****************************
chat_client: chat_client.o login_window.o signup_win.o chat_view.o chat_window.o room_window.o top_bar.o join_window.o manage_window.o
	${CXX} -o chat_client chat_client.o login_window.o signup_win.o  chat_view.o chat_window.o room_window.o top_bar.o -lpthread join_window.o manage_window.o -lncurses
chat_server: chat_server.o
	${CXX} -o chat_server chat_server.o -lpthread

clean:
	-rm -f chat_server chat_client chat_window *.o *.gch sorted_words.txt
