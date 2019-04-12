#pragma once
#include <boost/filesystem.hpp>

class FileManager {
public:
  FileManager() = delete;
  FileManager(std::string root);
  ~FileManager() {}

  std::string getPath(std::string file) const;

protected:
  bool setRoot(std::string root);

protected:
  boost::filesystem::path _root;
};
