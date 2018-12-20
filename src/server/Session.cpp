#include "Session.hpp"
#include <iostream>

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket) : _socket(std::move(socket)) {}

void Session::start() { doReadCommand(); }

void Session::doReadCommand() {
  auto self(shared_from_this());
  boost::asio::async_read(
      _socket, boost::asio::buffer(_data),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          protocol::RawRequest request;
          memcpy(&request, _data.data(), length);
          std::cout << static_cast<uint32_t>(request.cmd) << std::endl;
          if (request.extraSize) {
            char *extraData = new char[request.extraSize + 1]();
            boost::asio::async_read(
                _socket, boost::asio::buffer(extraData, request.extraSize),
                [this, self, extraData](boost::system::error_code ec, std::size_t length) {
                  if (!ec) {
                    std::cout << extraData << std::endl;
                  }
                  delete[] extraData;
                });
          } else
            doReadCommand();
        }
      });
}