#pragma once

#include "Command.hpp"

class CmdVersion : public Command {
public:
  using Command::Command;
  ~CmdVersion() { std::cerr << "dtor CmdVersion" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void handleString(const std::string &s, protocol::ErrorCode e);
  void handleError(protocol::ErrorCode e);
};
