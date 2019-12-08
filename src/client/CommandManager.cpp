#include "CommandManager.hpp"
#include "Protocol.h"
#include "CmdGetFile.hpp"
#include "CmdVersion.hpp"
#include "CmdLs.hpp"
#include "CmdNbrFiles.hpp"

void CommandManager::start(const std::vector<std::string> & /*args*/) {
  _cmdMap[protocol::command::names[protocol::command::Exit]] = {false, &ACommandManager::closeConnection};
  _cmdMap[protocol::command::names[protocol::command::GetFile]] = {false, &CommandManager::startCommand<CmdGetFile>};
  _cmdMap[protocol::command::names[protocol::command::Version]] = {true, &CommandManager::startCommand<CmdVersion>};
  _cmdMap[protocol::command::names[protocol::command::Ls]] = {false, &CommandManager::startCommand<CmdLs>};
  _cmdMap[protocol::command::names[protocol::command::NbrFiles]] = {false, &CommandManager::startCommand<CmdNbrFiles>};
  entryPoint();
}

void CommandManager::entryPoint() {  
  std::string input;
  std::cout << "> ";
  std::getline(std::cin, input);
  if(!std::cin)
    input = "EXIT";
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
