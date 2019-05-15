#pragma once

#include "ACommandManager.hpp"

class CommandManager : public ACommandManager {
public:
  using ACommandManager::ACommandManager;
  ~CommandManager() { std::cerr << "dtor CommandManager" << std::endl; }

  void start(const std::vector<std::string> &args = {}) final override;

private:
  void entryPoint() final override;
  void closeConnection(const std::vector<std::string> &args) final override;
  void death(const std::string &, protocol::ErrorCode);
};
