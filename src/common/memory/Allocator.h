/* Copyright (c) 2023 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include "common/memory/Memory.h"

template <class T>
class Allocator {
 public:
  typedef T value_type;
  typedef std::true_type propagate_on_container_move_assignment;

  constexpr Allocator() noexcept {}

  constexpr Allocator(const Allocator&) noexcept {}

  template <class U>
  constexpr Allocator(const Allocator<U>&) noexcept {}

  ~Allocator() noexcept {}

  T* FOLLY_NONNULL allocate(std::size_t n) {
    nebula::memory::trackMemory(n);
    return reinterpret_cast<T*>(nebula::memory::newImpl(n));
  }

  void deallocate(T* FOLLY_NONNULL p, std::size_t /*n*/) noexcept {
    nebula::memory::untrackMemory(p);
    nebula::memory::deleteImpl(p);
  }

  friend bool operator==(const Allocator&, const Allocator&) {
    return true;
  }

  friend bool operator!=(const Allocator&, const Allocator&) {
    return false;
  }
};
