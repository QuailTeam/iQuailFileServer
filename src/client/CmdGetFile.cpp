#include "CmdGetFile.hpp"

void CmdGetFile::start(const std::vector<std::string> &args) {
  if (args.size() < 1)
    return; //TODO handle
  std::string cmd = protocol::command::names[protocol::command::GetFile];
  cmd += " ";
  cmd += args[0];
  std::string absPathFile, absPathDir;
  _fileMgr->getAbsPath(args[0], absPathFile, false);
  _fileMgr->splitDirFile(absPathFile, &absPathDir, nullptr);
  if (!_fileMgr->isDirectory(absPathDir) && !boost::filesystem::create_directories(absPathDir)) {
    std::cerr << "File not received: cannot create dir list" << std::endl;
    return;
  }
  _session->writeString(cmd);
  _session->readFile(absPathFile, getAsCallback(&CmdGetFile::end));
}

void CmdGetFile::end(protocol::ErrorCode e) {
  //TODO rm directories on failure
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