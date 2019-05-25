#include "CmdVersion.hpp"

void CmdVersion::start(const std::vector<std::string> &args) {
  if (args.size() < 1)
    return; //TODO handle
  std::string cmd = protocol::command::names[protocol::command::Version];
  cmd += " " + args[0];
  if (args[0] == "SET" && args.size() > 1) {
    cmd += " " + args[1];
    _session->writeString(cmd);
    _session->readError(getAsCallback(&CmdVersion::handleError));
  }
  else if (args[0] == "GET" || args[0] == "LIST") {
    _session->writeString(cmd);
    _session->readString(getAsCallback(&CmdVersion::handleString));
  }
  else
    std::cerr << "Bad parameter" << std::endl;
}

void CmdVersion::handleString(const std::string &s, protocol::ErrorCode /*e*/) {
  std::cout << "Version result:" << std::endl;
  std::cout << s << std::endl;
}

void CmdVersion::handleError(protocol::ErrorCode e) {
  if (e == protocol::ErrorCode::Success)
    std::cout << "Version has been set" << std::endl;
  else
    std::cerr << "Invalid command" << std::endl;
}