#include "CmdLs.hpp"

void CmdLs::start(const std::vector<std::string> &args) {
  if (args.empty()) {
    _session->writeError(protocol::ErrorCode::BadParameter);
    return;
  }
  std::string dir;
  protocol::ErrorCode e = _fileMgr->getAbsPath(args[0], dir);
  if (e != protocol::ErrorCode::Success)
    _session->writeError(e);

  std::vector<std::string> content;
  e = _fileMgr->listDirectory(dir, content);
  if (e != protocol::ErrorCode::Success)
    _session->writeError(e);
  for (const auto& entry : content)
    _session->writeString(entry);
  _session->writeError(protocol::ErrorCode::EndStrList);
}
