#pragma once

#include "Command.hpp"

class CommandManager : public Command {
public:
  using Command::Command;
  ~CommandManager() { std::cerr << "dtor CommandManager" << std::endl; }

  void start() final override;

private:
  void receiveCommand(const std::string &s);
  void closeConnection();
  void sendBadCommand(const std::string &cmd);

  template <class CmdClass> void startCommand() {
    std::make_shared<CmdClass>(_session, getAsCallback(&CommandManager::start))
        ->start();
  }
};
