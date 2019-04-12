#pragma once

#include "FileManager.hpp"

class SFileManager : public FileManager {
public:
  SFileManager(std::string root);

  bool setVersion(std::string version);
  std::string getVersion() const;
  void getVersionNames(std::vector<std::string> &names) const;

private:
  void initVersions();

private:
  std::map<std::string, boost::filesystem::path> _versions;
};
