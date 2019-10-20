#include "PatchManager.hpp"
extern "C" {
  #include "libidiff.h"
}

// TODO tmp
#include <iostream>

bool PatchManager::createPatchDirs() {
  std::cout << "generating patches" << std::endl;
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