#pragma once

#include "Command.hpp"

class CmdEcho : public Command {
public:
  using Command::Command;
  ~CmdEcho() { std::cerr << "dtor CmdEcho" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;
};
