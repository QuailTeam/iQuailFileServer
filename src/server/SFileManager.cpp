#include "SFileManager.hpp"

using namespace boost::filesystem;

SFileManager::SFileManager(std::string root) : FileManager(root) {
  initVersions();
  if (_versions.empty())
    throw std::runtime_error("No version directory"); // TODO proper exception
  _root = _versions.begin()->second;
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
  _root = v->second;
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
