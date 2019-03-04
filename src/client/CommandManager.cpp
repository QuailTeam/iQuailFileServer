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

void CommandManager::end() {
  std::cerr << "File successfully written" << std::endl;
  _session->writeString(protocol::command::names[protocol::command::Exit]);
}
