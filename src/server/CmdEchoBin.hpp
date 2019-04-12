#pragma once

#include "SCommand.hpp"

class CmdEchoBin : public SCommand {
public:
  using SCommand::SCommand;
  ~CmdEchoBin() { std::cerr << "dtor CmdEchoBin" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void readInputAsBin(std::shared_ptr<std::vector<char>> input);
};
