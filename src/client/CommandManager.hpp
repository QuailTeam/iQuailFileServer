#pragma once

#include "Command.hpp"

class CommandManager : public Command {
public:
  using Command::Command;
  ~CommandManager() { std::cerr << "dtor CommandManager" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void entryPoint();
  void receiveFile();
  void end(protocol::ErrorCode e);
  void death(const std::string &, protocol::ErrorCode);
};
