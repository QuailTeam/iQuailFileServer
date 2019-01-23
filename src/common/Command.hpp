#pragma once

#include "Network.hpp"
#include <functional>

// Creation of a custom placeholder to use in variadic templates.
template <int N> struct CustomPlaceholder { static CustomPlaceholder ph; };
template <int N> CustomPlaceholder<N> CustomPlaceholder<N>::ph;
// Template specialization of is_placeholder to register our custom PH
namespace std {
template <int N>
struct is_placeholder<::CustomPlaceholder<N>> : std::integral_constant<int, N> {
};
} // namespace std

class Command : public std::enable_shared_from_this<Command> {
public:
  Command() = delete;
  Command(std::shared_ptr<Network> session,
          std::function<void()> exitCallback = nullptr)
      : _session(std::move(session)), _exitCallback(exitCallback) {}
  virtual ~Command() {
    if (_exitCallback)
      _exitCallback();
  }

  virtual void start(const std::vector<std::string> &args = {}) = 0;

protected:
  template <typename ReturnType, class Class, class... Args>
  inline std::function<ReturnType(Args...)>
  getAsCallback(ReturnType (Class::*method)(Args...)) {
    return getAsCallback(
        std::function<ReturnType(std::shared_ptr<Class>, Args...)>(method),
        std::make_integer_sequence<int, sizeof...(Args)>());
  }

private:
  template <typename ReturnType, class Class, class... Args, int... Indices>
  inline std::function<ReturnType(Args...)> getAsCallback(
      std::function<ReturnType(std::shared_ptr<Class>, Args...)> method,
      std::integer_sequence<int, Indices...> /*seq*/) {
    auto self = std::static_pointer_cast<Class>(shared_from_this());
    return std::bind(method, self, CustomPlaceholder<Indices + 1>::ph...);
  }

protected:
  std::shared_ptr<Network> _session;

private:
  std::function<void()> _exitCallback;
};
