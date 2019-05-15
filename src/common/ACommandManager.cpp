#include "ACommandManager.hpp"
#include "Protocol.h"
#include <sstream>
#include <vector>

void ACommandManager::receiveCommand(const std::string &s, protocol::ErrorCode /*e*/) {
  std::istringstream iss(s);
  std::string cmdName;
  iss >> cmdName;
  std::vector<std::string> cmdArgs(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
  auto cmdIt = _cmdMap.find(cmdName);
  if (cmdIt != _cmdMap.end())
    (*this.*(cmdIt->second))(cmdArgs);
  else {
    std::cerr << "bad command" << std::endl; //TODO handle
    entryPoint();
  }
}
