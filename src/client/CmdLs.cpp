#include "CmdLs.hpp"

void CmdLs::start(const std::vector<std::string> &args) {
  if (args.size() < 1)
    return; //TODO handle
  std::string cmd = protocol::command::names[protocol::command::Ls];
  cmd += " " + args[0];
  _session->writeString(cmd);
  _session->readStrings(getAsCallback(&CmdLs::receive));
}

void CmdLs::receive(const std::vector<std::string> &strs, protocol::ErrorCode e) {
  if (e != protocol::ErrorCode::Success) {
    std::cerr << "LS failed" << std::endl;
    return;
  }
  std::cout << "Directory content:" << std::endl;
  for (const auto &s : strs)
    std::cout << s << std::endl;
}
