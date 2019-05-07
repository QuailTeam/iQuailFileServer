#include "FileManager.hpp"

using namespace boost::filesystem;

FileManager::FileManager(std::string root) {
  if (!setRoot(root))
    throw std::runtime_error(
        "FileManager initialization failed"); // TODO proper exception
}

bool FileManager::setRoot(path root) {
  if (!exists(root) || !is_directory(root))
    return false;
  _root = canonical(root);
  return true;
}

bool FileManager::getAbsPath(std::string file, std::string &absPath) const {
  path p(_root);
  p /= file;
  if (!exists(p))
    return false;
  p = canonical(p);
  if (!isSafe(p))
    return false;
  absPath = p.string();
  return true;
}

bool FileManager::isSafe(boost::filesystem::path path) const {
  path = canonical(path);
  auto a = std::mismatch(_root.begin(), _root.end(), path.begin());
  if (a.first->empty())
    return true;
  return false;
}