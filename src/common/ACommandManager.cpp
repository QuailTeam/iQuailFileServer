#include "ACommandManager.hpp"
#include "Protocol.h"
#include <sstream>
#include <vector>

void ACommandManager::receiveCommand(const std::string &s, protocol::ErrorCode /*e*/) {
  std::istringstream iss(s);
  std::string cmdName;
  std::vector<std::string> cmdArgs;
  iss >> cmdName;

  auto cmdIt = _cmdMap.find(cmdName);
  if (cmdIt != _cmdMap.end()) {
    if (cmdIt->second.first) {
      cmdArgs = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>()};
    } else {
      std::string stringArgs;
      while (iss.peek() != EOF && iss.peek() == ' ')
        iss.ignore(1);
      std::getline(iss, stringArgs);
      cmdArgs.push_back(stringArgs);
    }
    (*this.*(cmdIt->second.second))(cmdArgs);
  } else {
    std::cerr << "bad command" << std::endl; //TODO handle
    entryPoint();
  }
}
