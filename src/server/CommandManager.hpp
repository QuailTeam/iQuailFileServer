#pragma once

#include "Command.hpp"

class CommandManager : public Command {
public:
  using Command::Command;

  void start();

private:
  void receiveCommand(std::string const &cmd);
};
