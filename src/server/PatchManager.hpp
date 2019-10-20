#pragma once

#include "SFileManager.hpp"

class PatchManager : public SFileManager {
public:
  using SFileManager::SFileManager;
  ~PatchManager() {}

  bool createPatchDirs();

private:
};