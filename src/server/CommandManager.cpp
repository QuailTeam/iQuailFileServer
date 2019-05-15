#include "CommandManager.hpp"
#include "CmdGetFile.hpp"
#include "Protocol.h"
#include <sstream>
#include <unordered_map>
#include <vector>

void CommandManager::start(const std::vector<std::string> & /*args*/) {
  _cmdMap[protocol::command::names[protocol::command::Exit]] = &ACommandManager::closeConnection;
  _cmdMap[protocol::command::names[protocol::command::GetFile]] = &CommandManager::startCommand<CmdGetFile>;
  entryPoint();
}

void CommandManager::entryPoint() {
  _session->readString(getAsCallback(&ACommandManager::receiveCommand));
}

void CommandManager::closeConnection(
    const std::vector<std::string> & /*args*/) {
  _session->writeString("Closing Connection");
}
/*
void CommandManager::sendBadCommand(const std::string &cmd) {
  _session->writeString("Bad Command: " + cmd,
                        getAsCallback(&CommandManager::entryPoint));
}*/
