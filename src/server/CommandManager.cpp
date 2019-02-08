#include "CommandManager.hpp"
#include "CmdEcho.hpp"
#include "CmdEchoBin.hpp"
#include "Protocol.h"
#include <sstream>
#include <unordered_map>
#include <vector>

void CommandManager::start(const std::vector<std::string> & /*args*/) {
  entryPoint();
}

void CommandManager::entryPoint() {
  _session->readString(getAsCallback(&CommandManager::receiveCommand));
}

void CommandManager::receiveCommand(const std::string &s) {
  static const std::unordered_map<
      std::string, void (CommandManager::*)(const std::vector<std::string> &)>
      cmdMap = {
          {protocol::command::names[protocol::command::Exit],
           &CommandManager::closeConnection},
          {protocol::command::names[protocol::command::Echo],
           &CommandManager::startCommand<CmdEcho>},
          {protocol::command::names[protocol::command::EchoBin],
           &CommandManager::startCommand<CmdEchoBin>},
      };
  std::istringstream iss(s);
  std::string cmdName;
  iss >> cmdName;
  std::vector<std::string> cmdArgs(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
  auto cmdIt = cmdMap.find(cmdName);
  if (cmdIt == cmdMap.end())
    sendBadCommand(cmdName);
  else
    (*this.*(cmdIt->second))(cmdArgs);
}

void CommandManager::closeConnection(
    const std::vector<std::string> & /*args*/) {
  _session->writeString("Closing Connection");
}

void CommandManager::sendBadCommand(const std::string &cmd) {
  _session->writeString("Bad Command: " + cmd,
                        getAsCallback(&CommandManager::entryPoint));
}