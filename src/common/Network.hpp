#pragma once

#include <boost/asio.hpp>
#include <string>

//
#include <iostream>
//

class Network : public std::enable_shared_from_this<Network> {
public:
  using Socket = boost::asio::ip::tcp::socket;

  Network(Socket socket) : _socket(std::move(socket)) {}
  ~Network() { std::cerr << "dtor network" << std::endl; }

  void readString(std::function<void(const std::string &)> callback = nullptr);
  void writeString(const std::string &s,
                   std::function<void()> callback = nullptr);
  // void writeBinary();
  // void readBinary();

private:
  void handleError(const std::string &functionName,
                   const boost::system::error_code &ec) const;

  Socket _socket;
  boost::asio::streambuf _strBuff;
};
