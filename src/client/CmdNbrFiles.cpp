#include "CmdNbrFiles.hpp"

void CmdNbrFiles::start(const std::vector<std::string> &args) {
  (void)args;
  std::string cmd = protocol::command::names[protocol::command::NbrFiles];
  _session->writeString(cmd);
  _session->readString(getAsCallback(&CmdNbrFiles::receive));
}

void CmdNbrFiles::receive(const std::string &s, protocol::ErrorCode e) {
  if (e != protocol::ErrorCode::Success) {
    std::cerr << "NbrFiles failed" << std::endl;
    return;
  }
  std::cout << s << std::endl;
}
