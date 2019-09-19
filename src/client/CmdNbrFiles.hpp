#pragma once

#include "Command.hpp"

class CmdNbrFiles : public Command {
public:
  using Command::Command;

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void receive(const std::string &s, protocol::ErrorCode e);
};
