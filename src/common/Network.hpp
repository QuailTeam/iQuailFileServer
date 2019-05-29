#pragma once

#include "Protocol.h"
#include <boost/asio.hpp>
#include <fstream>
#include <string>

//
#include <iostream>
//

class Network : public std::enable_shared_from_this<Network> {
public:
  using Socket = boost::asio::ip::tcp::socket;

  Network(Socket socket) : _socket(std::move(socket)) {}
  ~Network() { std::cerr << "dtor network" << std::endl; }

  void readString(std::function<void(const std::string &, protocol::ErrorCode)> callback = nullptr);
  void readStrings(std::function<void(const std::vector<std::string> &, protocol::ErrorCode)> callback = nullptr);
  void writeString(const std::string &s,
                   std::function<void()> callback = nullptr);

  void readBinary(std::function<void(std::shared_ptr<std::vector<char>>)>
                      callback = nullptr); // deprecated, need to read error code and get odd_buff
  void writeBinary(std::shared_ptr<std::vector<char>> b,
                   std::function<void()> callback = nullptr); // deprecated, need to write error code and get odd_buff

  void readFile(const std::string &path,
                std::function<void(protocol::ErrorCode)> callback = nullptr);
  void writeFile(const std::string &path,
                 std::function<void()> callback = nullptr);

  void readError(std::function<void(protocol::ErrorCode)> callback = nullptr);
  void writeError(protocol::ErrorCode, std::function<void()> callback = nullptr);

private:
  bool initReadFile(const std::string &path);
  bool initWriteFile(const std::string &path);

  void stringReceiver(const std::string &, protocol::ErrorCode);

  void writeSize(std::size_t size, boost::system::error_code &ec);
  std::size_t readSize(boost::system::error_code &ec);

  void handleError(const std::string &functionName,
                   const boost::system::error_code &ec) const;

  Socket _socket;

  // Read buff
  boost::asio::streambuf _readBuff;

  // File temporary attributes
  enum { BufferLength = 32768 };
  std::array<char, BufferLength> _fileBuff;
  std::streamsize _fileSize;
  std::fstream _file;

  // Strings temporary attributes
  std::function<void(const std::vector<std::string> &, protocol::ErrorCode)> _strsCallback;
  std::vector<std::string> _strs;
};
