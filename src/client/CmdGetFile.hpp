#pragma once

#include "Command.hpp"

class CmdGetFile : public Command {
public:
  using Command::Command;

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void end(protocol::ErrorCode e);
};
