#pragma once

#include "Command.hpp"
#include <unordered_map>
#include <utility>

class ACommandManager : public Command {
public:
  using Command::Command;

  void receiveCommand(const std::string &s,
                      protocol::ErrorCode = protocol::ErrorCode::Success);
  virtual void closeConnection(const std::vector<std::string> &args) = 0;

protected:
  virtual void entryPoint() = 0;
  template <class CmdClass>
  void startCommand(const std::vector<std::string> &args) {
    std::make_shared<CmdClass>(_session, _fileMgr,
                               getAsCallback(&ACommandManager::entryPoint))
        ->start(args);
  }

protected:
  typedef void (ACommandManager::*Callback)(const std::vector<std::string> &);
  std::unordered_map<std::string, std::pair<bool, Callback> > _cmdMap; //bool defines if we split arguments
};
