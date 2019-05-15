#include "CommandManager.hpp"
#include "Protocol.h"
#include "CmdGetFile.hpp"

void CommandManager::start(const std::vector<std::string> & /*args*/) {
  _cmdMap[protocol::command::names[protocol::command::Exit]] = &ACommandManager::closeConnection;
  _cmdMap[protocol::command::names[protocol::command::GetFile]] = &CommandManager::startCommand<CmdGetFile>;
  entryPoint();
}

void CommandManager::entryPoint() {  
  std::string input;
  std::cout << "?> ";
  std::getline(std::cin, input);
  receiveCommand(input);
}

void CommandManager::closeConnection(
    const std::vector<std::string> & /*args*/) {
  _session->writeString(protocol::command::names[protocol::command::Exit]);
  _session->readString(getAsCallback(&CommandManager::death));
}

void CommandManager::death(const std::string &s, protocol::ErrorCode /*e*/) {
  std::cerr << s << std::endl;
}
