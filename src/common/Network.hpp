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

  void readBinary(std::function<void(std::shared_ptr<std::vector<char>>)>
                      callback = nullptr);
  void writeBinary(std::shared_ptr<std::vector<char>> b,
                   std::function<void()> callback = nullptr);
  // void readFile(std::function<void()> callback = nullptr);
  // void writeFile(const std::string &filePath,
  //                std::function<void()> callback = nullptr);

private:
  void writeSize(std::size_t size, boost::system::error_code &ec);
  std::size_t readSize(boost::system::error_code &ec);

  void handleError(const std::string &functionName,
                   const boost::system::error_code &ec) const;

  Socket _socket;
  boost::asio::streambuf _strBuff;
  enum { BufferLength = 40960 };
  std::array<char, BufferLength> _buff;
};
