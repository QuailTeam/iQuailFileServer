#pragma once

#include <boost/asio.hpp>

class Client {
public:
  using IoService = boost::asio::io_service;
  using TcpResolver = boost::asio::ip::tcp::resolver;
  using TcpResolverIterator = TcpResolver::iterator;
  using TcpSocket = boost::asio::ip::tcp::socket;

  Client(IoService &t_ioService, TcpResolverIterator t_endpointIterator,
  std::string dl_path);

private:
  void doConnect();

  TcpResolver m_ioService;
  TcpSocket _socket;
  TcpResolverIterator m_endpointIterator;
  std::string _dl_path;
};
