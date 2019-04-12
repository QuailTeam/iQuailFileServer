#include "FileManager.hpp"

using namespace boost::filesystem;

FileManager::FileManager(std::string root) {
  if (!setRoot(root))
    throw std::runtime_error("FileManager initialization failed"); //TODO proper exception
}

bool FileManager::setRoot(std::string root) {
  _root = root;
  if (exists(_root) && is_directory(_root))
    return true;
  return false;
}
