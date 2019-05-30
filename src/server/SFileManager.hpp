#pragma once

#include "FileManager.hpp"

class SFileManager : public FileManager {
public:
  SFileManager(const std::string &root, const std::string &lastVersion);

  bool setVersion(const std::string &version);
  std::string getVersion() const;
  void getVersionNames(std::vector<std::string> &names) const;
  protocol::ErrorCode listDirectory(const std::string &absDir, std::vector<std::string> &list) const;

private:
  void initVersions();
  std::string genLsEntry(const boost::filesystem::directory_entry &e) const;

private:
  std::string _lastVersion;
  std::map<std::string, boost::filesystem::path> _versions;
};
