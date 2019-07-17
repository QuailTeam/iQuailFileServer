#include "CommandManager.hpp"
#include "Protocol.h"
#include "CmdGetFile.hpp"
#include "CmdVersion.hpp"
#include "CmdLs.hpp"

void CommandManager::start(const std::vector<std::string> & /*args*/) {
  _cmdMap[protocol::command::names[protocol::command::Exit]] = &ACommandManager::closeConnection;
  _cmdMap[protocol::command::names[protocol::command::GetFile]] = &CommandManager::startCommand<CmdGetFile>;
  _cmdMap[protocol::command::names[protocol::command::Version]] = &CommandManager::startCommand<CmdVersion>;
  _cmdMap[protocol::command::names[protocol::command::Ls]] = &CommandManager::startCommand<CmdLs>;
  entryPoint();
}

void CommandManager::entryPoint() {  
  std::string input;
  std::cout << "> ";
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
