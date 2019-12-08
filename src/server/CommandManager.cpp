#include "CommandManager.hpp"
#include "CmdGetFile.hpp"
#include "CmdVersion.hpp"
#include "CmdLs.hpp"
#include "CmdNbrFiles.hpp"
#include "Protocol.h"
#include <sstream>
#include <unordered_map>
#include <vector>

void CommandManager::start(const std::vector<std::string> & /*args*/) {
  _cmdMap[protocol::command::names[protocol::command::Exit]] = {false, &ACommandManager::closeConnection};
  _cmdMap[protocol::command::names[protocol::command::GetFile]] = {false, &CommandManager::startCommand<CmdGetFile>};
  _cmdMap[protocol::command::names[protocol::command::Version]] = {true, &CommandManager::startCommand<CmdVersion>};
  _cmdMap[protocol::command::names[protocol::command::Ls]] = {false, &CommandManager::startCommand<CmdLs>};
  _cmdMap[protocol::command::names[protocol::command::NbrFiles]] = {false, &CommandManager::startCommand<CmdNbrFiles>};
  entryPoint();
}

void CommandManager::entryPoint() {
  _session->readString(getAsCallback(&ACommandManager::receiveCommand));
}

void CommandManager::closeConnection(
    const std::vector<std::string> & /*args*/) {
  _session->writeString("Closing Connection");
}
