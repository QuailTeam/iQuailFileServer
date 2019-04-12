#pragma once

#include "SCommand.hpp"

class CmdEcho : public SCommand {
public:
  using SCommand::SCommand;
  ~CmdEcho() { std::cerr << "dtor CmdEcho" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;
};
