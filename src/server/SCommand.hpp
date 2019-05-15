#pragma once

#include "Command.hpp"
#include "SFileManager.hpp"

class SCommand : public Command {
public:
  SCommand() = delete;
  SCommand(std::shared_ptr<Network> session,
           std::shared_ptr<FileManager> fileMgr,
           std::function<void()> exitCallback = nullptr)
      : Command(std::move(session), fileMgr, exitCallback),
        _fileMgr(std::move(std::static_pointer_cast<SFileManager>(fileMgr))) {}

protected:
  std::shared_ptr<SFileManager> _fileMgr;
};
