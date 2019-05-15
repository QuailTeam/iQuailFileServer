#include "Server.hpp"
#include "CommandManager.hpp"
#include "Network.hpp"
#include "SFileManager.hpp"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_service &ioService, short port, std::string root)
    : _acceptor(ioService, tcp::endpoint(tcp::v4(), port)), _socket(ioService),
      _root(root) {
  doAccept();
}

void Server::doAccept() {
  _acceptor.async_accept(_socket, [this](boost::system::error_code ec) {
    if (!ec) {
      std::make_shared<CommandManager>(
          std::make_shared<Network>(std::move(_socket)),
          std::static_pointer_cast<FileManager>(
              std::make_shared<SFileManager>(_root)))
          ->start();
    }
    doAccept();
  });
}