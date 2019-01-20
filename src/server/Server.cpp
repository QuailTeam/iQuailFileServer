#include "Server.hpp"
#include "CommandManager.hpp"
#include "Network.hpp"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_service &ioService, short port)
    : _acceptor(ioService, tcp::endpoint(tcp::v4(), port)), _socket(ioService) {
  doAccept();
}

void Server::doAccept() {
  _acceptor.async_accept(_socket, [this](boost::system::error_code ec) {
    if (!ec) {
      std::make_shared<CommandManager>(
          std::make_shared<Network>(std::move(_socket)))
          ->start();
    }
    doAccept();
  });
}