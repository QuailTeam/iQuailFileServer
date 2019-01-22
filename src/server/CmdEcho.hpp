#pragma once

#include "Command.hpp"

class CmdEcho : public Command {
public:
  CmdEcho(std::shared_ptr<Network> session, std::function<void()> f)
      : Command(std::move(session)), _callback(f) {}
  ~CmdEcho() {
    _callback();
    std::cerr << "dtor CmdEcho" << std::endl;
  }

  void start() final override;

private:
  std::function<void()> _callback;
};
