#include "Network.hpp"

void Network::readString(std::function<void(const std::string &, protocol::ErrorCode)> callback) {
  boost::system::error_code ec;
  protocol::ErrorCode e = static_cast<protocol::ErrorCode>(readSize(ec));
  if (ec) {
    handleError(__FUNCTION__, ec);
    return;
  }
  if (e != protocol::ErrorCode::Success) {
    if (callback)
      callback("", e);
    return;
  }
  auto self = shared_from_this();
  async_read_until(
      _socket, _readBuff, "\n",
      [self, callback](boost::system::error_code ec, size_t bytes) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        std::string s(boost::asio::buffers_begin(self->_readBuff.data()),
        boost::asio::buffers_begin(self->_readBuff.data()) + (bytes - 1));
        self->_readBuff.consume(bytes);
        if (callback)
          callback(s, protocol::ErrorCode::Success);
      });
}

void Network::readStrings(std::function<void(const std::vector<std::string> &, protocol::ErrorCode)> callback) {
  _strsCallback = callback;
  _strs.clear();
  this->readString(std::bind(&Network::stringReceiver, this, std::placeholders::_1, std::placeholders::_2));
}

void Network::stringReceiver(const std::string &s, protocol::ErrorCode e) {
  if (e == protocol::ErrorCode::EndStrList) {
    if (_strsCallback)
      _strsCallback(_strs, protocol::ErrorCode::Success);
    _strsCallback = nullptr;
  } else if (e == protocol::ErrorCode::Success) {
    _strs.emplace_back(s);
    this->readString(std::bind(&Network::stringReceiver, this, std::placeholders::_1, std::placeholders::_2));
  } else {
    _strs.clear();
    if (_strsCallback)
      _strsCallback(_strs, e);
    _strsCallback = nullptr;
  }
}

void Network::writeString(const std::string &s,
                          std::function<void()> callback) {
  boost::system::error_code ec;
  writeSize(protocol::ErrorCode::Success, ec);
  if (ec) {
    handleError(__FUNCTION__, ec);
    return;
  }
  auto self = shared_from_this();
  std::string sLF(s + '\n');
  boost::asio::async_write(
      _socket, boost::asio::buffer(sLF.c_str(), sLF.size()),
      [self, callback](boost::system::error_code ec, size_t /*s*/) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        if (callback)
          callback();
      });
}

void Network::readBinary(
    std::function<void(std::shared_ptr<std::vector<char>>)> callback) {
  boost::system::error_code ec;
  std::size_t totalSize = readSize(ec);
  if (ec) {
    handleError(__FUNCTION__, ec);
    return;
  }
  std::shared_ptr<std::vector<char>> binaryData =
      std::make_shared<std::vector<char>>(totalSize);
  auto self = shared_from_this();
  boost::asio::async_read(
      _socket, boost::asio::buffer(binaryData->data(), totalSize),
      [self, binaryData, callback](boost::system::error_code ec, size_t /*s*/) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        if (callback)
          callback(std::move(binaryData));
      });
}

void Network::writeBinary(std::shared_ptr<std::vector<char>> b,
                          std::function<void()> callback) {
  boost::system::error_code ec;
  writeSize(b->size(), ec);
  if (ec) {
    handleError(__FUNCTION__, ec);
    return;
  }
  auto self = shared_from_this();
  boost::asio::async_write(
      _socket, boost::asio::buffer(*b.get()),
      [self, b, callback](boost::system::error_code ec, size_t /*s*/) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        if (callback)
          callback();
      });
}

void Network::readFile(const std::string &path,
                       std::function<void(protocol::ErrorCode)> callback) {
  boost::system::error_code ec;
  protocol::ErrorCode e = static_cast<protocol::ErrorCode>(readSize(ec));
  if (ec) {
    handleError(__FUNCTION__, ec);
    return;
  }
  if (e != protocol::ErrorCode::Success) {
    if (callback)
      callback(e);
    return;
  }

  if (!initReadFile(path))
    return;
  auto self = shared_from_this();
  _socket.async_read_some(
      boost::asio::buffer(_fileBuff.data(), _fileBuff.size()),
      [self, callback](boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        if (bytesTransferred > 0) {
          self->_file.write(
              self->_fileBuff.data(),
              static_cast<std::streamsize>(bytesTransferred)); // TODO check
          if (self->_file.tellp() >= self->_fileSize) {
            self->_file.close();
            if (callback)
              callback(protocol::ErrorCode::Success);
            return;
          }
        }
        self->readFile("", callback);
      });
}

bool Network::initReadFile(const std::string &path) {

  if (_file.is_open())
    return true;

  boost::system::error_code ec;
  _fileSize = static_cast<std::streamsize>(readSize(ec));
  if (ec) {
    handleError(__FUNCTION__, ec);
    return false;
  }
  if (!_fileSize)
    return false;

  _file.open(path,
             std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
  if (_file.fail()) {
    // TODO report fail
    return false;
  }
  return true;
}

void Network::writeFile(const std::string &path,
                        std::function<void()> callback) {
  boost::system::error_code ec;
  writeSize(protocol::ErrorCode::Success, ec);
  if (ec) {
    handleError(__FUNCTION__, ec);
    return;
  }
  if (!initWriteFile(path)) {
    boost::system::error_code ec;
    writeSize(
        0,
        ec); // TODO reconsider, is this still usefull with new error system ?
    return;
  }
  _file.read(_fileBuff.data(), _fileBuff.size()); // TODO check
  auto self = shared_from_this();
  boost::asio::async_write(
      _socket, boost::asio::buffer(_fileBuff.data(), _file.gcount()),
      [self, callback](boost::system::error_code ec, size_t /*s*/) {
        if (ec) {
          self->handleError(__FUNCTION__, ec);
          return;
        }
        if (self->_file.eof()) {
          self->_file.close();
          if (callback)
            callback();
          return;
        }
        self->writeFile("", callback);
      });
}

bool Network::initWriteFile(const std::string &path) {
  if (_file.is_open())
    return true;

  _file.open(path,
             std::ofstream::in | std::ofstream::binary | std::ofstream::ate);
  if (_file.fail()) {
    // TODO report fail
    return false;
  }

  _file.seekg(0, _file.end);
  _fileSize = _file.tellg();
  _file.seekg(0, _file.beg);

  boost::system::error_code ec;
  writeSize(static_cast<size_t>(_fileSize), ec);
  if (ec) {
    handleError(__FUNCTION__, ec);
    return false;
  }
  return true;
}

void Network::writeSize(std::size_t size, boost::system::error_code &ec) {
  boost::asio::write(_socket, boost::asio::buffer(&size, sizeof(std::size_t)),
                     ec); // TODO make async
}

std::size_t Network::readSize(boost::system::error_code &ec) {
  std::size_t size;
  size_t toReceive = sizeof(size) - std::min(sizeof(size), _readBuff.size());
  boost::asio::read(_socket, _readBuff, boost::asio::transfer_exactly(toReceive), ec); // TODO make async
  if (ec) {
    handleError(__FUNCTION__, ec);
    return 0; //TODO true error handling
  }
  std::copy_n(boost::asio::buffers_begin(_readBuff.data()), sizeof(size), &size);
  _readBuff.consume(sizeof(size));
  return size;
}

void Network::readError(std::function<void(protocol::ErrorCode)> callback) {
  boost::system::error_code ec;
  protocol::ErrorCode e = static_cast<protocol::ErrorCode>(readSize(ec));
  if (ec) {
    handleError(__FUNCTION__, ec);
    return;
  }
  if (callback)
    callback(e);
}

void Network::writeError(protocol::ErrorCode e, std::function<void()> callback) {
  boost::system::error_code ec;
  writeSize(e, ec);
  if (ec) {
    handleError(__FUNCTION__, ec);
    return;
  }
  if (callback)
    callback();
}

void Network::handleError(const std::string &functionName,
                          const boost::system::error_code &ec) const {
  // TODO log
  std::cerr << "Error: " << ec << " " << ec.message() << " in " << functionName
            << std::endl;
}
