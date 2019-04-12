#pragma once

#include "SCommand.hpp"

class CmdGetFile : public SCommand {
public:
  using SCommand::SCommand;
  ~CmdGetFile() { std::cerr << "dtor CmdGetFile" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;
};
