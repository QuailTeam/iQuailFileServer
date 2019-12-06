#include "PatchManager.hpp"
extern "C" {
  #include "libidiff.h"
}

// TODO tmp
#include <iostream>

using namespace boost::filesystem;

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
        computeDelta(fileInV.c_str(), elem.path().c_str(), fileInP.c_str());
      } else {
        //create non-patched version of file (simple copy)
        std::cout << "  New non-patched file: " << relPath.string() << std::endl;
        copy_file(elem.path(), fileInP);
      }
    }
  }

  std::cout << "Generation performed successfully" << std::endl;
  return true;
  //computeDelta("", "", "");

  /*
  * Algorithm for patch creation
  * 
  * for each version v (!= last)
  *   create v_last patch dir p
  *   for each file f in last
  *     if f is also in v:
  *       create patch f in p
  *     else:
  *       copy f as f in p
  * 
  * 
  * Algorithm for patch management:
  * 
  * Can we consider a patched version like a normal version ?
  * Seems like a YES:
  * - dir in same location
  * - client set version on the desired patch
  * - download files as usual (just need reconstruction client side):
  *   get_current_verion
  *   if not None:
  *     send 'VERSION SET <old>'
  *   for each file in solution:
  *     download file
  *     get_old_file_version
  *     if not None:
  *       decompress (in tmp then replace downloaded file by the decomp)
  *       
  * 
  * 
  * 
  * Do we replace the version dir by its patch ?
  * Yes: no dir concatenation:
  * - No need to download anterior version, only the last one
  * - Client just send its current version and patch is automatically applied
  * - This can be done using VERSION SET <old_version>
  * No:
  * - compress compression on restart
  * - original files are deleted
  * - can select older version from client
  * - have to reconstruct the compression name on client side
  * 
  */
}