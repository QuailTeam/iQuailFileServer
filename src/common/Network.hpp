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

  void readString(std::function<void(std::string const &)> callback);
  // void writeString(std::string const &s, std::function<void()> callback);
  // void writeBinary();
  // void readBinary();

private:
  void handleError(std::string const &functionName,
                   boost::system::error_code const &ec) const;

  Socket _socket;
  boost::asio::streambuf _strBuff;
};
