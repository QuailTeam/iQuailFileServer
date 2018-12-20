#pragma once

#include "Protocol.hpp"
#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session> {
public:
  Session(boost::asio::ip::tcp::socket socket);
  void start();

private:
  void doReadCommand();

  boost::asio::ip::tcp::socket _socket;
  std::array<char, sizeof(protocol::RawRequest)> _data;
};
