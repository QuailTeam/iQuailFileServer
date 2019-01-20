#include "Network.hpp"
#include <memory>

#include <iostream>

void Network::readString(std::function<void(std::string const &)> callback) {
  auto self = shared_from_this();
  async_read_until(
      _socket, _strBuff, "\n",
      [self, callback](boost::system::error_code ec, size_t /*bytes*/) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        callback(std::string((std::istreambuf_iterator<char>(&self->_strBuff)),
                             std::istreambuf_iterator<char>()));
      });
}

void Network::handleError(std::string const &functionName,
                          boost::system::error_code const &ec) const {
  // TODO log
  std::cerr << "Error: " << ec << " " << ec.message() << " in " << functionName
            << std::endl;
}
