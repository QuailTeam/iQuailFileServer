#pragma once

#include <boost/asio.hpp>
#include <string>
#include <fstream>

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

  void readFile(const std::string &path,
                std::function<void()> callback = nullptr);
  void writeFile(const std::string &path,
                 std::function<void()> callback = nullptr);

private:

  bool initReadFile(const std::string &path);
  bool initWriteFile(const std::string &path);

  void writeSize(std::size_t size, boost::system::error_code &ec);
  std::size_t readSize(boost::system::error_code &ec);

  void handleError(const std::string &functionName,
                   const boost::system::error_code &ec) const;

  Socket _socket;

  // String temporary attributes
  boost::asio::streambuf _strBuff;

  // File temporary attributes
  enum { BufferLength = 32768 };
  std::array<char, BufferLength> _fileBuff;
  std::streamsize _fileSize;
  std::fstream _file;
};
