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

using asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

int maxX, maxY;
Chat_view *chat_view;
int line_number = 1;

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
            std::cout << user_msg;
            chat_view->new_msg(user_msg, line_number);
            line_number++;
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
    while(!selected_login) {
      Login_window login_win = Login_window(maxY, maxX);
      login_win.show();
      selected_login = login_win.get_input();
      erase();
      refresh();
      if(!selected_login) { //signup_selected
        Signup_win signup = Signup_win(maxY, maxX);
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
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(argv[1], argv[2]);
    chat_client c(io_context, endpoints);

    std::thread t([&io_context](){ io_context.run(); });

    char line[chat_message::max_body_length + 1];
    Chat_window chat_win = Chat_window(maxX, maxY); //used to get message
    chat_win.show();
    
    Room_window room_win = Room_window(maxX, maxY); //room windows
    room_win.show();
    room_win.get_input();

    while (1)
    {
      chat_win.get_input();
      strcpy(line, chat_win.get_user_msg().c_str());
      chat_message msg;
	    //implementing spell check (not complete therefore commented out)
	    //line = client.(&spell_check(line));
      msg.body_length(std::strlen(line));
      std::memcpy(msg.body(), line, msg.body_length());
      msg.encode_header();
      c.write(msg);
    }

    c.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
