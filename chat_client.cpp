//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include "asio.hpp"
#include "chat_message.hpp"
#include "login_window.hpp"
#include "signup_win.hpp"
#include "chat_view.hpp"
#include "chat_window.hpp"
#include "room_window.hpp"
#include "top_bar.hpp"
#include "join_window.hpp"
#include "manage_window.hpp"
using asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;
std::string room_ids[10] =  { "9000", "9001", "9002", "9003", "9004", "9005", "9006", "9007", "9008", "9009"};

int maxX, maxY;
Chat_view *chat_view;
Room_window *room_win;
Chat_window *chat_win;
Top_bar *top_win;

std::vector<std::string> muted_users;

int line_number = 0;

class chat_client
{
public:
  chat_client(asio::io_context& io_context,
      const tcp::resolver::results_type& endpoints)
    : io_context_(io_context),
      socket_(io_context)
  {
    do_connect(endpoints);
  }
  void write(const chat_message& msg)
  {
    asio::post(io_context_,
        [this, msg]()
        {
          bool write_in_progress = !write_msgs_.empty();
          write_msgs_.push_back(msg);
          if (!write_in_progress)
          {
            do_write();
          }
        });
  }

  void close()
  {
    asio::post(io_context_, [this]() { socket_.close(); });
  }

private:
  void do_connect(const tcp::resolver::results_type& endpoints)
  {
    asio::async_connect(socket_, endpoints,
        [this](std::error_code ec, tcp::endpoint)
        {
          if (!ec)
          {
            do_read_header();
          }
        });
  }

  void do_read_header()
  {
    asio::async_read(socket_,
        asio::buffer(read_msg_.data(), chat_message::header_length),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec && read_msg_.decode_header())
          {
            do_read_body();
          }
          else
          {
            socket_.close();
          }
        });
  }

  void do_read_body()
  {
    asio::async_read(socket_,
        asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            std::string user_msg;
            user_msg.assign(read_msg_.body(), read_msg_.body_length());
            //get user name from user_msg
            std::string user_name_str = user_msg.substr(0, user_msg.find(":"));
            //check if user is in muted users
            bool valid_show = true;
            for(unsigned int i = 0; i < muted_users.size(); i++)
            {
              if(user_name_str == muted_users[i])
              {
                valid_show = false;
              }
            }
            if(valid_show){
              chat_view->new_msg(user_msg, line_number);
              line_number++;
            }
            do_read_header();
          }
          else
          {
            socket_.close();
          }
        });
  }

  void do_write()
  {
    asio::async_write(socket_,
        asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            socket_.close();
          }
        });
  }

private:
  asio::io_context& io_context_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

int select_window(int curr_win);
void highlight(int curr_win);


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }
    initscr();
    noecho();
    cbreak();

    getmaxyx(stdscr, maxY, maxX);
    
    //login window starts
    bool selected_login = false;
    Login_window login_win = Login_window(maxY, maxX);
    Signup_win signup = Signup_win(maxY, maxX);
        
    while(!selected_login) {
      login_win.show();
      selected_login = login_win.get_input();
      erase();
      refresh();
      if(!selected_login) { //signup_selected
        signup.show();
        bool ok_select = signup.get_input();
        if(ok_select) {
          //logic for adding user here
        }
        erase(); 
        refresh();
      } else {
        //need to check user credentials server
      } 
    } 
    //intial login/signup ends
    chat_view = new Chat_view(maxX, maxY);
    chat_view->show();
    chat_win = new Chat_window(maxX, maxY); //used to get message
    chat_win->show();
    room_win = new Room_window(maxX, maxY); //room windows
    room_win->show();
    top_win = new Top_bar(maxX, maxY, login_win.get_username_input(), room_win->get_current_room_name(room_win->get_current_room_select()));
    top_win->show();
    
    asio::io_context *io_context = new asio::io_context();

    tcp::resolver *resolver = new tcp::resolver(*io_context);
    auto endpoints = resolver->resolve(argv[1], argv[2]);
    chat_client *c = new chat_client(*io_context, endpoints);

    std::thread *t = new std::thread([&io_context](){ io_context->run(); });
    char line[chat_message::max_body_length + 1];
    room_win->get_input();
    int current_window = 0; 
    while (1)
    {
      current_window = select_window(current_window);
      if(current_window == 0) //top bar window
      {
        int option = top_win->get_input();
        if (option == 0) //join room selected
        {
          Join_window join_win = Join_window(maxX, maxY);
          join_win.show();
          bool ok_selected = join_win.get_input();
          if(ok_selected){
            
            //add to room if correct key
            /*
              join room request logic goes here using 
              join_win.get_room_str();
              join_win.get_key_str();
            */
            room_win->add_room(join_win.get_room_str());
          }

          //clears windows and repaints it
          erase();
          room_win->show();
          top_win->show();
          chat_view->show();
          chat_win->show();
          
        }
        else if(option == 1) //manage
        {
          Manage_window manage_win = Manage_window(maxX, maxY);
          manage_win.show();
          bool ok_selected = manage_win.get_input();
          if(ok_selected)
          {
            std::string username_to_mute = manage_win.get_mute_username();
            if(username_to_mute != "") //check if we need to change user
            {
              bool in_muted = false;
              unsigned int index_delete = 0;
              for(unsigned int i = 0; i < muted_users.size(); i++){ //check if user is muted users
                if(muted_users[i] == username_to_mute){
                  in_muted = true;
                  index_delete = i;
                }
              }

              if(!in_muted)
                muted_users.push_back(username_to_mute);
              else //delete user
              {
                std::vector<std::string> new_muted_users;
                for(unsigned int i = 0; i < muted_users.size(); i++) //shring array of users
                {
                  if(i != index_delete)
                  {
                    new_muted_users.push_back(muted_users[i]);
                  }
                }
                //swap
                muted_users = new_muted_users;
              }
            }
            /*
              delete room 
              this will be a request
               manage_win.get_delete_button();
            */
           
          }
          erase();
          room_win->show();
          top_win->show();
          chat_view->show();
          chat_win->show();
        }
        else if(option == 2) // leave
        {
          /*
            logic to leave the current room
          */
          if(room_win->get_current_room_select() != 0){ //cant leave looby
            room_win->remove_room(room_win->get_current_room_select());
            room_win->show();
            room_win->set_current_room_select(0);
            top_win->set_rm_name(room_win->get_current_room_name(room_win->get_current_room_select()));
            top_win->show();
            chat_view->show();
            chat_win->show();
          }
        }
      }
      else if(current_window == 1) //choose room
      {
        int old_room = room_win->get_current_room_select();
        room_win->get_input();
        int new_room = room_win->get_current_room_select();
        if(new_room != old_room) { //swap rooms if change in rooms
          chat_view->clear_win();
          line_number = 0;
          top_win->set_rm_name(room_win->get_current_room_name(new_room));
          /*
            logic to switch rooms most likely we need to switch sockets
          */
          t->detach();
          delete t;
          delete resolver;
          delete io_context;
          delete c; 
          io_context = new asio::io_context();
          resolver = new tcp::resolver(*io_context);
          auto endpoints = resolver->resolve(argv[1], room_ids[new_room].c_str());
          c = new chat_client(*io_context, endpoints);
          t = new std::thread([&io_context](){ io_context->run(); });

        }
      }
      else if(current_window == 2){ //message box
        chat_win->get_input();
        std::string usr_msg = login_win.get_username_input() + ": " + chat_win->get_user_msg();
        strcpy(line, usr_msg.c_str());
        chat_message msg;
        //implementing spell check (not complete therefore commented out)
        //line = client.(&spell_check(line));
        msg.body_length(std::strlen(line));
        std::memcpy(msg.body(), line, msg.body_length());
        msg.encode_header();
        c->write(msg);
      }
    }

    c->close();
    t->join();
  } 
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}


void highlight(int curr_win)
{
  switch(curr_win){
    case 0:
      top_win->mvmenu();
      break;
    case 1:
      room_win->mvmenu();
      break;
    case 2:
      chat_win->mvmenu();
      break;
  }
}
/*
  this function is used for selecting windows such as message box, rooms and other administrative tasks
  join room needs to be added still
*/
int select_window(int curr_win) 
{
  keypad(stdscr, true);
  int selected = curr_win;
  bool not_done = true;
  int ch;
  while(not_done)
  {
    ch = getch();
    if (ch == KEY_UP || ch == KEY_LEFT)
    {
      selected--;
      if (selected < 0)
          selected = 0;
      highlight(selected);
    }
    else if (ch == KEY_DOWN || ch == KEY_RIGHT)
    {
      selected++;
      if (selected > 2)
          selected = 2;
      highlight(selected);
    }
    else if (ch == 10) //this means enter
    {
      not_done = false;
		}
  }
  keypad(stdscr, false);
  return selected;
}