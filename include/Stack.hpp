// Copyright 2020 Slava-100 <svat.strel.2001@gmail.com>

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_

#include <memory>
#include <utility>

#include "StackImpl.hpp"

template <typename T>
class Stack {
 public:
  Stack() : _impl(new StackImpl<T>()) {}

  Stack(const Stack &) = delete;

  Stack(Stack &&other) noexcept : _impl(std::move(other._impl)) {}

  Stack &operator=(const Stack &) = delete;

  Stack &operator=(Stack &&other) noexcept {
    if (this == &other) return *this;
    _impl = std::move(other._impl);
    return *this;
  }

  ~Stack() = default;

  void push(const T &value) { _impl->push(value); }

  void push(T &&value) { _impl->push(std::move(value)); }

  template <typename... args_t>
  void emplace(args_t &&...args) {
    _impl->emplace(std::forward<args_t>(args)...);
  }

  T pop() { return _impl->pop(); }

  bool empty() const { return _impl->empty(); }

  std::size_t size() const { return _impl->size(); }

 private:
  std::unique_ptr<StackImpl<T>> _impl;
};

#endif  // INCLUDE_STACK_HPP_
