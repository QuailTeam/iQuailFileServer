#pragma once

#include "Command.hpp"

class CmdEcho : public Command {
public:
  using Command::Command;

  void start() {}
};
