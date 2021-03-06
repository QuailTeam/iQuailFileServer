#pragma once

#include "Command.hpp"

class CmdVersion : public Command {
public:
  using Command::Command;

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void handleString(const std::string &s, protocol::ErrorCode e);
  void handleStrings(const std::vector<std::string> &strs, protocol::ErrorCode e);
  void handleError(protocol::ErrorCode e);
};
