#include <iostream>
#include <errno.h>
#include <cstring>
#include "PatchManager.hpp"
extern "C" {
  #include "libidiff.h"
}

using namespace boost::filesystem;

PatchManager::PatchManager(const std::string &root, const std::string &lastVersion, size_t maxMem)
  : SFileManager(root, lastVersion, true), _maxMem(maxMem * 1000000) {
}

bool PatchManager::createPatchDirs() {
  std::cout << "Generating patches:" << std::endl;
  path lastVDir(_versionsDir);
  lastVDir /= _lastVersion;
  for (const auto &v : _versions) {
    if (v.first == _lastVersion)
      continue;
    path patchDir(_versionsDir);
    patchDir /= getPatchName(v.first);
    if (exists(patchDir)) {
      if (is_directory(patchDir))
        continue;
      else
        return false;
    }
    if (!boost::filesystem::create_directories(patchDir))
      return false;
    std::cout << "New patch directory: " << getPatchName(v.first) << std::endl;
    path vDir(_versionsDir);
    vDir /= v.first;
    for (auto &&elem : recursive_directory_iterator(lastVDir)) {
      if (elem.status().type() != regular_file)
        continue;
      path relPath = relative(elem.path(), lastVDir);
      path fileInV(vDir);
      fileInV /= relPath;
      path fileInP(patchDir);
      fileInP /= relPath;
      boost::filesystem::create_directories(fileInP.parent_path());
      if (exists(fileInV)) {
        if (!is_regular_file(fileInV)) {
          std::cerr << "file to dir transition not implemented yet" << std::endl;
          return false;
        }
        //create patch file
        std::cout << "  New patched file: " << relPath.string() << std::endl;
        if (computeDelta(fileInV.c_str(), elem.path().c_str(), fileInP.c_str(), 3221225472) != 0) {
          std::cerr << "Error: computeDelta() failed: " << strerror(errno) << std::endl;
          return false;
        }
      } else {
        //create non-patched version of file (simple copy)
        std::cout << "  New non-patched file: " << relPath.string() << std::endl;
        copy_file(elem.path(), fileInP);
      }
    }
  }
  std::cout << "Generation performed successfully" << std::endl;
  return true;
}
