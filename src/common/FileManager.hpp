#pragma once

#include "Protocol.h"
#include <boost/filesystem.hpp>

class FileManager {
public:
  FileManager() = delete;
  FileManager(const std::string &root);
  ~FileManager() {}

  protocol::ErrorCode getAbsPath(const std::string &file, std::string &absPath, bool checks = true) const;
  static bool isRegFile(const std::string &absPath);
  static bool isDirectory(const std::string &absPath);
  static void splitDirFile(const std::string &absPath, std::string *dir, std::string *file);

protected:
  bool setRoot(boost::filesystem::path root);
  bool isSafe(boost::filesystem::path path) const;

protected:
  boost::filesystem::path _root;
};
