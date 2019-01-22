#include "CommandManager.hpp"
#include "CmdEcho.hpp"
#include "Protocol.h"
#include <unordered_map>

//
#include <iostream>
//

void CommandManager::start() {
  _session->readString(getAsCallback(&CommandManager::receiveCommand));
}

void CommandManager::receiveCommand(const std::string &s) {
  static const std::unordered_map<std::string, void (CommandManager::*)()>
      cmdMap = {
          {protocol::command::names[protocol::command::Exit],
           &CommandManager::closeConnection},
          {protocol::command::names[protocol::command::Echo],
           &CommandManager::startCommand<CmdEcho>},
      };
  auto cmd = cmdMap.find(s);
  if (cmd == cmdMap.end())
    sendBadCommand(s);
  else
    (*this.*(cmd->second))();
}

void CommandManager::closeConnection() {
  std::cerr << "Closing Connection" << std::endl; //SEND
}

void CommandManager::sendBadCommand(const std::string &cmd) {
  std::cerr << "Bad Command: " << cmd << std::endl; //SEND
  start();
}