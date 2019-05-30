#pragma once

#include <boost/asio.hpp>

class Server {
public:
  Server(boost::asio::io_service &ioService, short port,
  const std::string &root, const std::string &lastVersion);

private:
  void doAccept();

  boost::asio::ip::tcp::acceptor _acceptor;
  boost::asio::ip::tcp::socket _socket;
  std::string _root;
  std::string _lastVersion;
};
