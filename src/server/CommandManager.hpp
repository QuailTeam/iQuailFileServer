#pragma once

#include "SCommand.hpp"

class CommandManager : public SCommand {
public:
  using SCommand::SCommand;
  ~CommandManager() { std::cerr << "dtor CommandManager" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void entryPoint();
  void receiveCommand(const std::string &s, protocol::ErrorCode);
  void closeConnection(const std::vector<std::string> &args = {});
  void sendBadCommand(const std::string &cmd);

  template <class CmdClass>
  void startCommand(const std::vector<std::string> &args) {
    std::make_shared<CmdClass>(_session, _fileMgr,
                               getAsCallback(&CommandManager::entryPoint))
        ->start(args);
  }
};
