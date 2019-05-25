#pragma once

#include "SCommand.hpp"

class CmdVersion : public SCommand {
public:
  using SCommand::SCommand;
  ~CmdVersion() { std::cerr << "dtor CmdVersion" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;
};
