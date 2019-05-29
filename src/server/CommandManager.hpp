#pragma once

#include "ACommandManager.hpp"

class CommandManager : public ACommandManager {
public:
  using ACommandManager::ACommandManager;
  ~CommandManager() { std::cerr << "dtor CommandManager" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void entryPoint() final override;
  void receiveCommand(const std::string &s, protocol::ErrorCode);
  void closeConnection(const std::vector<std::string> &args) final override;
};
