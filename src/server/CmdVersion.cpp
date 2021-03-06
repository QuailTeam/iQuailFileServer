#include "CmdVersion.hpp"

void CmdVersion::start(const std::vector<std::string> &args) {
  if (args.empty()) {
    _session->writeError(protocol::ErrorCode::BadParameter);
    return;
  }
  if (args[0] == "GET")
    _session->writeString(_fileMgr->getVersion());
  else if (args[0] == "LIST") {
    std::vector<std::string> versions;
    _fileMgr->getVersionNames(versions);
    for (const auto& version : versions)
      _session->writeString(version);
    _session->writeError(protocol::ErrorCode::EndStrList);

  }
  else if (args[0] == "SET" && args.size() > 1) {    
    protocol::ErrorCode e = _fileMgr->setVersion(args[1]) ?
    protocol::ErrorCode::Success : protocol::ErrorCode::BadParameter;
    _session->writeError(e);
  }
  else
    _session->writeError(protocol::ErrorCode::BadParameter);
}
