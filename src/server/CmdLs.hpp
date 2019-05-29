#pragma once

#include "SCommand.hpp"

class CmdLs : public SCommand {
public:
  using SCommand::SCommand;
  ~CmdLs() { std::cerr << "dtor CmdLs" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;
};
