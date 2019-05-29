#pragma once

#include "FileManager.hpp"

class SFileManager : public FileManager {
public:
  SFileManager(std::string root);

  bool setVersion(std::string version);
  std::string getVersion() const;
  void getVersionNames(std::vector<std::string> &names) const;
  protocol::ErrorCode listDirectory(const std::string &absDir, std::vector<std::string> &list) const;

private:
  void initVersions();
  std::string genLsEntry(const boost::filesystem::directory_entry &e) const;

private:
  std::map<std::string, boost::filesystem::path> _versions;
};
