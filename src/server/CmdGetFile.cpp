#include "CmdGetFile.hpp"

void CmdGetFile::start(const std::vector<std::string> &args) {
  if (args.empty())
    return;
  std::string file = _fileMgr->getPath(args[0]); //TODO handle error
  _session->writeFile(file);
}
