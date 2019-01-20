#pragma once

#include "Network.hpp"
#include <boost/system/error_code.hpp>
#include <functional>

//
#include <iostream>
//

class Command : public std::enable_shared_from_this<Command> {
public:
  Command() = delete;
  Command(std::shared_ptr<Network> session) : _session(std::move(session)) {}
  virtual ~Command() { std::cerr << "dtor command" << std::endl; }

  virtual void start() = 0;

protected:
  template<typename Specialization, typename Method>
  inline std::function<void(std::string const &)> getAsCallback(Method m) {
    auto self = std::static_pointer_cast<Specialization>(shared_from_this());
    return std::bind(m, self, std::placeholders::_1);
  }


  std::shared_ptr<Network> _session;
};
