#include "CmdEcho.hpp"

void CmdEcho::start(const std::vector<std::string> &args) {
  std::string echo;
  for (auto arg : args)
    echo += arg + " ";
  _session->writeString(echo);
}
