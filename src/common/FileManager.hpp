#pragma once
#include <boost/filesystem.hpp>

class FileManager {
public:
  FileManager() = delete;
  FileManager(std::string root);
  ~FileManager() {}

  bool getAbsPath(std::string file, std::string &absPath) const;

protected:
  bool setRoot(boost::filesystem::path root);
  bool isSafe(boost::filesystem::path path) const;

protected:
  boost::filesystem::path _root;
};
