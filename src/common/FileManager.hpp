#pragma once
#include <boost/filesystem.hpp>

class FileManager {
public:
  FileManager() = delete;
  FileManager(std::string root);
  ~FileManager() {}

  bool setRoot(std::string root);

private:
  boost::filesystem::path _root;
};
