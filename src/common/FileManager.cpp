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

protocol::ErrorCode FileManager::getAbsPath(const std::string &file, std::string &absPath) const {
  path p(_root);
  p /= file;
  if (!exists(p))
    return protocol::ErrorCode::InvalidPath;
  p = canonical(p);
  if (!isSafe(p))
    return protocol::ErrorCode::IllegalPath;
  absPath = p.string();
  return protocol::ErrorCode::Success;
}

bool FileManager::isSafe(boost::filesystem::path path) const {
  path = canonical(path);
  auto a = std::mismatch(_root.begin(), _root.end(), path.begin());
  if (a.first->empty())
    return true;
  return false;
}

bool FileManager::isRegFile(const std::string &absPath) const {
  return is_regular_file(path(absPath));
}

bool FileManager::isDirectory(const std::string &absPath) const {
  return is_directory(path(absPath));
}
