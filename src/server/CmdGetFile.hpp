#pragma once

#include "Command.hpp"

class CmdGetFile : public Command {
public:
  using Command::Command;
  ~CmdGetFile() { std::cerr << "dtor CmdGetFile" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;
};
