#pragma once

#include "SCommand.hpp"

class CmdNbrFiles : public SCommand {
public:
  using SCommand::SCommand;
  ~CmdNbrFiles() { std::cerr << "dtor CmdNbrFiles" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;
};
