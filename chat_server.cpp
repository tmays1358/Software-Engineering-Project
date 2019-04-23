//
// chat_server.cpp
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
#include <list>
#include <memory>
#include <set>
#include <utility>
#include "asio.hpp"
#include "chat_message.hpp"
#include <fstream>
using asio::ip::tcp;

//----------------------------------------------------------------------

typedef std::deque<chat_message> chat_message_queue;
std::string rf_names[11] = {"lobby.txt", "room1.txt", "room2.txt", "room2.txt", "room3.txt", "room4.txt", "room5.txt", "room6.txt", "room7.txt", "room8.txt", "room9.txt"};
std::ofstream file;
std::vector<std::vector<chat_message>> message_logs;
int index_files = 0;
//----------------------------------------------------------------------

class chat_participant
{
public:
  virtual ~chat_participant() {}
  virtual void deliver(const chat_message& msg) = 0;
};

typedef std::shared_ptr<chat_participant> chat_participant_ptr;

//----------------------------------------------------------------------

class chat_room
{
public:
  void join(chat_participant_ptr participant)
  {
    //when a new person connects we need to load the previous messages to catch them up to speed
    participants_.insert(participant);
    std::ifstream ifs;
    ifs.open(rf_names[index].c_str());
    std::string str;
    while(std::getline(ifs, str))
    {
      chat_message user_msg;
      user_msg.body_length(str.size());
      std::memcpy(user_msg.body(), str.c_str(), user_msg.body_length());
      user_msg.encode_header();
      message_logs[index].push_back(user_msg);
    }
    for (auto msg: message_logs[index])
      participant->deliver(msg);
  }

  void leave(chat_participant_ptr participant)
  {
    participants_.erase(participant);
    //check if not lobby and if no participants
    if (index != 0 && participants_.size() == 0) //check if we can delete
    {
      message_logs[index].clear();
      file.open(rf_names[index].c_str(), std::ofstream::trunc);
      file.close(); //clears chat essentially making it new
    }
  }

  void deliver(const chat_message& msg)
  {
    //std::cout << "room " << index << " has " << participants_.size() << " participants" << std::endl;    
    chat_message user_msg;
    std::string str = obfuscutate_msg(msg);
    user_msg.body_length(str.size());
    std::memcpy(user_msg.body(), str.c_str(), msg.body_length());
    user_msg.encode_header();
    file.open(rf_names[index].c_str(),std::fstream::app);
    std::string s_msg;
    s_msg.assign(user_msg.body(), user_msg.body_length());
    file << s_msg << '\n';
    file.close();
    recent_msgs_.push_back(user_msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

    for (auto participant: participants_)
    {
      //were the server sends messages to the client
      participant->deliver(user_msg);
    }
  }
  std::string obfuscutate_msg(chat_message msg)
  {   
    std::string new_msg;
    new_msg.assign(msg.body(), msg.body_length());
    for(unsigned int i = 0; i < new_msg.size(); i++)
    {
      new_msg[i] = new_msg[i] + key;
    }
    return new_msg;
  }
private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;
  int index = index_files++;
  int key = index_files - 1;
};

//----------------------------------------------------------------------

class chat_session
  : public chat_participant,
    public std::enable_shared_from_this<chat_session>
{
public:
  chat_session(tcp::socket socket, chat_room& room)
    : socket_(std::move(socket)),
      room_(room)
  {
  }

  void start()
  {
    room_.join(shared_from_this());
    do_read_header();
  }

  void deliver(const chat_message& msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      do_write();
    }
  }

private:
  void do_read_header()
  {
    auto self(shared_from_this());
    asio::async_read(socket_,
        asio::buffer(read_msg_.data(), chat_message::header_length),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec && read_msg_.decode_header())
          {
            do_read_body();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_read_body()
  {
    auto self(shared_from_this());
    asio::async_read(socket_,
        asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            room_.deliver(read_msg_);
            do_read_header();
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  void do_write()
  {
    auto self(shared_from_this());
    asio::async_write(socket_,
        asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            /*
              save input here
            */
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }

  tcp::socket socket_;
  chat_room& room_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
  std::vector<chat_message> message_transcript;
};

//----------------------------------------------------------------------

class chat_server
{
public:
  chat_server(asio::io_context& io_context,
      const tcp::endpoint& endpoint)
    : acceptor_(io_context, endpoint)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](std::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<chat_session>(std::move(socket), room_)->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  chat_room room_;
};

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try
  {
    if (argc < 2)
    {
      std::cerr << "Usage: chat_server <port> [<port> ...]\n";
      return 1;
    }
    
    char response;
    std::cout << "Clean start? ";
    std::cin >> response;
    if(response == 'y')
    {
      for(int index = 0; index < 11; index++)
      {
        file.open(rf_names[index].c_str(), std::ofstream::trunc);
        file.close();
      }
    }
    asio::io_context io_context;

    std::list<chat_server> servers;
    for (int i = 0; i < 11; ++i)
    {
      int port = atoi(argv[1]);
      std::vector<chat_message> logs;
      message_logs.push_back(logs);
      tcp::endpoint endpoint(tcp::v4(), port + i); //to create more rooms simply change argument value
      servers.emplace_back(io_context, endpoint);
    }

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
