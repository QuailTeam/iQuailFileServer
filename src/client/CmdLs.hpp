#pragma once

#include "Command.hpp"

class CmdLs : public Command {
public:
  using Command::Command;

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void receive(const std::vector<std::string> &strs, protocol::ErrorCode e);
};
