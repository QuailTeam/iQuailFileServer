#include "CmdGetFile.hpp"

void CmdGetFile::start(const std::vector<std::string> &args) {
  if (args.empty())
    return;
  std::string file; 
  protocol::ErrorCode e = _fileMgr->getAbsPath(args[0], file);
  if (e != protocol::ErrorCode::Success)
    _session->writeError(e);
  else if (!_fileMgr->isRegFile(file))
    _session->writeError(protocol::ErrorCode::InvalidPath);
  else
    _session->writeFile(file);
}
