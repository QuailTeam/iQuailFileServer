#include "CmdNbrFiles.hpp"

void CmdNbrFiles::start(const std::vector<std::string> &args) {
  (void)args;
  std::string dir;
  int nbrFiles = _fileMgr->getNbrFiles();
  _session->writeString(std::to_string(nbrFiles));
}
