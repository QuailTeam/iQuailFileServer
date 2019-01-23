#include "Network.hpp"

void Network::readString(std::function<void(const std::string &)> callback) {
  auto self = shared_from_this();
  async_read_until(
      _socket, _strBuff, "\n",
      [self, callback](boost::system::error_code ec, size_t bytes) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        if (callback)
          callback(
              std::string((std::istreambuf_iterator<char>(&self->_strBuff)),
                          std::istreambuf_iterator<char>())
                  .substr(0, bytes - 1));
      });
}

void Network::writeString(const std::string &s,
                          std::function<void()> callback) {
  auto self = shared_from_this();
  std::string sLF(s + '\n');
  boost::asio::async_write(
      _socket, boost::asio::buffer(sLF.c_str(), sLF.size()),
      [self, callback](boost::system::error_code ec, size_t /*length*/) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        if (callback)
          callback();
      });
}

void Network::handleError(const std::string &functionName,
                          const boost::system::error_code &ec) const {
  // TODO log
  std::cerr << "Error: " << ec << " " << ec.message() << " in " << functionName
            << std::endl;
}
