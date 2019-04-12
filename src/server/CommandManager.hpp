#pragma once

#include "Command.hpp"

class CommandManager : public Command {
public:
  using Command::Command;
  ~CommandManager() { std::cerr << "dtor CommandManager" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void entryPoint();
  void receiveCommand(const std::string &s);
  void closeConnection(const std::vector<std::string> &args = {});
  void sendBadCommand(const std::string &cmd);

  template <class CmdClass>
  void startCommand(const std::vector<std::string> &args) {
    std::make_shared<CmdClass>(_session, _fileMgr,
                               getAsCallback(&CommandManager::entryPoint))
        ->start(args);
  }
};
