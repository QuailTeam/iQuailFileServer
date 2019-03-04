#include "CommandManager.hpp"
#include "Protocol.h"

void CommandManager::start(const std::vector<std::string> & /*args*/) {
  entryPoint();
}

void CommandManager::entryPoint() {
  std::string cmd = protocol::command::names[protocol::command::GetFile];
  cmd += " ./iQuailServer";
  _session->writeString(cmd, getAsCallback(&CommandManager::receiveFile));
}

void CommandManager::receiveFile() {
  _session->readFile("LeBonFichier", getAsCallback(&CommandManager::end));
}

void CommandManager::end() {
  std::cerr << "File successfully written" << std::endl;
  _session->writeString(protocol::command::names[protocol::command::Exit]);
}
