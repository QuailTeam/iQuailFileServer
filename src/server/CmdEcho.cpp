#include "CmdEcho.hpp"

void CmdEcho::start() {
  //_session->readString(getAsCallback(&CommandManager::receiveCommand));
  std::cerr << "ECHO" << std::endl; // SEND
}
