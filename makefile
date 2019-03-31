CXX=g++

CXXFLAGS=-Wall -g -std=c++11

#change this CPPFLAG TO MATCH your library location
#for best results move asio-1.12.2 to home folder
CPPFLAGS=-I/home/`whoami`/asio-1.12.2/include

all:chat_client chat_server

#test the successful compilation of object files
object_files: chat_window.o about_tab_window.o help_tab_window.o setting_tab_window.o profile_tab_window.o

#client and server
chat_client.o: chat_client.cpp chat_message.hpp
chat_server.o: chat_server.cpp chat_message.hpp

#**************VIEW GOES HERE**********************************
chat_window.o: chat_window.cpp chat_window.hpp
	${CXX} -c chat_window.cpp chat_window.hpp
about_tab_window.o: about_tab_window.cpp about_tab_window.hpp
	${CXX} -c about_tab_window.cpp about_tab_window.hpp
help_tab_window.o: help_tab_window.cpp help_tab_window.hpp
	${CXX} -c help_tab_window.cpp help_tab_window.hpp
setting_tab_window.o: setting_tab_window.cpp setting_tab_window.hpp
	${CXX} -c setting_tab_window.cpp setting_tab_window.hpp
profile_tab_window.o: profile_tab_window.cpp profile_tab_window.hpp
	${CXX} -c profile_tab_window.cpp profile_tab_window.hpp

#*************MODEL goes here**********************************


#*************CONTROLLER goes here*****************************


#*************final exec goes here*****************************
chat_client: chat_client.o
	${CXX} -o chat_client chat_client.o -lpthread -lncurses
chat_server: chat_server.o
	${CXX} -o chat_server chat_server.o -lpthread

clean:
	-rm -f chat_server chat_client chat_window *.o *.gch
