#include "SFileManager.hpp"

using namespace boost::filesystem;

SFileManager::SFileManager(std::string root) : FileManager(root) {
  initVersions();
  if (_versions.empty())
    throw std::runtime_error("No version directory"); // TODO proper exception
  setRoot(_versions.begin()->second);
}

void SFileManager::initVersions() {
  for (auto &&x : directory_iterator(_root)) //TODO condjump
    if (is_directory(x.path()))
      _versions.emplace(x.path().filename().c_str(), x.path());
}

bool SFileManager::setVersion(std::string version) {
  auto v = _versions.find(version);
  if (v == _versions.end())
    return false;
  setRoot(v->second);
  return true;
}

std::string SFileManager::getVersion() const {
  return _root.filename().c_str();
}

void SFileManager::getVersionNames(std::vector<std::string> &names) const {
  names.reserve(_versions.size());
  for (const auto &v : _versions)
    names.emplace_back(v.first);
}

std::string SFileManager::genLsEntry(const boost::filesystem::directory_entry &e) const {
  std::string entry;
  switch (e.status().type()) {
    case directory_file:
      entry += "d ";
      entry += "0 ";
      entry += e.path().filename().c_str();
    break;
    case regular_file:
      entry += "- ";
      entry += std::to_string(file_size(e.path())) + " ";
      entry += e.path().filename().c_str();
    break;
    default:
    break;
  }
  return entry;
}

protocol::ErrorCode SFileManager::listDirectory(const std::string &absDir, std::vector<std::string> &list) const {
  if (!isDirectory(absDir))
    return protocol::ErrorCode::Success; // TODO implement ls on file
  path d(absDir);
  for (auto &&elem : directory_iterator(d)) {
    std::string entry = genLsEntry(elem);
    if (!entry.empty())
      list.emplace_back(entry);
  }
  return protocol::ErrorCode::Success;
}
