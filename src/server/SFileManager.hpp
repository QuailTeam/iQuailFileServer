#pragma once

#include "FileManager.hpp"
#include <map>

class SFileManager : public FileManager {
public:
  SFileManager(const std::string &root, const std::string &lastVersion, bool ignorePatch = false);
  virtual ~SFileManager() {}

  bool setVersion(const std::string &version);
  std::string getVersion() const;
  void getVersionNames(std::vector<std::string> &names) const;
  protocol::ErrorCode listDirectory(const std::string &absDir, std::vector<std::string> &list) const;
  int getNbrFiles() const;
  std::string getLastVersion() const;
  std::string getPatchName(const std::string &oldVersion) const;

private:
  void initVersions(bool ignorePatch);
  std::string genLsEntry(const boost::filesystem::directory_entry &e) const;
  std::string getPacthConcatStr() const;

protected:
  boost::filesystem::path _versionsDir;
  std::string _lastVersion;
  std::map<std::string, boost::filesystem::path> _versions;
};
