#pragma once

#include "Protocol.h"
#include <boost/filesystem.hpp>

class FileManager {
public:
  FileManager() = delete;
  FileManager(const std::string &root);
  ~FileManager() {}

  protocol::ErrorCode getAbsPath(const std::string &file, std::string &absPath, bool checks = true) const;
  bool isRegFile(const std::string &absPath) const;
  bool isDirectory(const std::string &absPath) const;
  void splitDirFile(const std::string &absPath, std::string *dir, std::string *file) const;

protected:
  bool setRoot(boost::filesystem::path root);
  bool isSafe(boost::filesystem::path path) const;

protected:
  boost::filesystem::path _root;
};
