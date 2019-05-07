#include "CommandManager.hpp"
#include "Protocol.h"

void CommandManager::start(const std::vector<std::string> & /*args*/) {
  entryPoint();
}

void CommandManager::entryPoint() {
  std::string cmd = protocol::command::names[protocol::command::GetFile];
  std::string input;
  std::cout << "Which file do you want to get from the server ?\n";
  std::cin >> input;
  cmd += " " + input;
  _session->writeString(cmd, getAsCallback(&CommandManager::receiveFile));
}

void CommandManager::receiveFile() {
  std::string input;
  std::cout << "How do you want to name this file ?\n";
  std::cin >> input;
  _session->readFile(input, getAsCallback(&CommandManager::end));
}

void CommandManager::end(protocol::ErrorCode e) {
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
  _session->writeString(protocol::command::names[protocol::command::Exit]);
  _session->readString(getAsCallback(&CommandManager::death));
}

void CommandManager::death(const std::string &s, protocol::ErrorCode /*e*/) {
  std::cerr << s << std::endl;
}
