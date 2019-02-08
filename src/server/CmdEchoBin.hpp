#pragma once

#include "Command.hpp"

class CmdEchoBin : public Command {
public:
  using Command::Command;
  ~CmdEchoBin() { std::cerr << "dtor CmdEchoBin" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void readInputAsBin(std::shared_ptr<std::vector<char>> input);
};
