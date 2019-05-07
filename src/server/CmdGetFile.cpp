#include "CmdGetFile.hpp"

void CmdGetFile::start(const std::vector<std::string> &args) {
  if (args.empty())
    return;
  std::string file; 
  if (!_fileMgr->getAbsPath(args[0], file))
    return; //TODO handle unsafe path
  _session->writeFile(file);
}
