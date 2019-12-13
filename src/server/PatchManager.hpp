#pragma once

#include "SFileManager.hpp"

class PatchManager : public SFileManager {
public:
  using SFileManager::SFileManager;
  PatchManager(const std::string &root, const std::string &lastVersion, size_t maxMem);
  ~PatchManager() {}

  bool createPatchDirs();

private:
  size_t _maxMem;
};