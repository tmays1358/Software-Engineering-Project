CXX=g++

CXXFLAGS=-Wall -g -std=c++11

#change this CPPFLAG TO MATCH your library location
#for best results move asio-1.12.2 to home folder
CPPFLAGS=-I/home/`whoami`/asio-1.12.2/include

all:chat_client chat_server

#test the successful compilation of object files
object_files: chat_window.o  signup_win.o login_window.o chat_view.o room_window.o top_bar.o join_window.o

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
#*************MODEL goes here**********************************
server.o:signup_win.h login_win.h server.h server.cpp
	${CXX} -c server.cpp server.h
client.o: rooms.h client.h client.cpp
	${CXX} -c client.cpp client.h

#*************View goes here bottom stuff**********************
View.o: chat_message.hpp view.hpp view.cpp
	${CXX} -c view.cpp view.hpp
user.o: user.hpp user.cpp
	${CXX} -c user.hpp user.cpp
message.o: message.hpp user.hpp message.cpp
	${CXX} -c message.hpp message.cpp
room.o: room.hpp room.cpp user.hpp
	${CXX} -c room.hpp room.cpp
	
#*************CONTROLLER goes here*****************************
Controller.o: controller.hpp controller.cpp view.hpp chat_message.hpp
	${CXX} -c controller.cpp controller.hpp

#*************final exec goes here*****************************
chat_client: chat_client.o login_window.o signup_win.o chat_view.o chat_window.o room_window.o top_bar.o join_window.o
	${CXX} -o chat_client chat_client.o login_window.o signup_win.o  chat_view.o chat_window.o room_window.o top_bar.o -lpthread join_window.o -lncurses
chat_server: chat_server.o
	${CXX} -o chat_server chat_server.o -lpthread

clean:
	-rm -f chat_server chat_client chat_window *.o *.gch
