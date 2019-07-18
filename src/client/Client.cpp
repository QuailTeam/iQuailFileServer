#include "Client.hpp"
#include "CommandManager.hpp"

//
#include <iostream>
//

Client::Client(IoService &t_ioService, TcpResolverIterator t_endpointIterator,
std::string dl_path)
    : m_ioService(t_ioService), _socket(t_ioService),
      m_endpointIterator(t_endpointIterator), _dl_path(dl_path) {
  doConnect();
}

void Client::doConnect() {
  boost::asio::async_connect(
      _socket, m_endpointIterator,
      [this](boost::system::error_code ec, TcpResolverIterator) {
        if (!ec) {
          std::make_shared<CommandManager>(
              std::make_shared<Network>(std::move(_socket)),
              std::make_shared<FileManager>(_dl_path))
              ->start();
        } else {
          std::cerr << "Couldn't connect to host. Please run server "
                       "or check network connection.\n";
        }
      });
}
