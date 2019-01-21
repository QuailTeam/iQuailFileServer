#include "CommandManager.hpp"

//
#include <iostream>
//

void CommandManager::start() {
  _session->readString(getAsCallback(&CommandManager::receiveCommand));
}

void CommandManager::receiveCommand(std::string const &cmd) {
  std::cout << "received: " << cmd << std::endl;
}