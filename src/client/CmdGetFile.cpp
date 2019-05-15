#include "CmdGetFile.hpp"

void CmdGetFile::start(const std::vector<std::string> &args) {
  if (args.size() < 1)
    return; //TODO handle
  std::string cmd = protocol::command::names[protocol::command::GetFile];
  cmd += " ";
  cmd += args[0];
  _session->writeString(cmd);
  //boost::filesystem::create_directories("/tmp/a/b/c");
  _session->readFile("a", getAsCallback(&CmdGetFile::end));
}

void CmdGetFile::end(protocol::ErrorCode e) {
  switch (e) {
  case protocol::ErrorCode::Success:
    std::cerr << "File successfully written" << std::endl;
    break;
  case protocol::ErrorCode::InvalidPath:
    std::cerr << "File not received: Invalid Path" << std::endl;
    break;
  case protocol::ErrorCode::IllegalPath:
    std::cerr << "File not received: Illegal Path" << std::endl;
    break;
  default:
    break;
  }
}