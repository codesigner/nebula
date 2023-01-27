/* Copyright (c) 2023 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <bits/stringfwd.h>
#include <unordered_set>
#include <vector>

#include "common/memory/Allocator.h"

namespace nebula {

struct Step;
struct Tag;
struct Value;
struct List;

typedef typename std::basic_string<char, std::char_traits<char>, Allocator<char>> String;

typedef typename std::vector<String, Allocator<String>> StringVector;

typedef typename std::vector<Value, Allocator<Value>> ValueVector;

typedef typename std::unordered_map<String,
                                    Value,
                                    std::hash<String>,
                                    std::equal_to<String>,
                                    Allocator<std::pair<const String, Value>>>
    ValueMap;

typedef typename std::unordered_set<Value> ValueSet;

typedef typename std::vector<List, Allocator<List>> ListVector;

typedef typename std::vector<Tag, Allocator<Tag>> TagVector;

typedef typename std::vector<Step, Allocator<Step>> StepVector;

}  // namespace nebula

namespace std {
template <>
struct hash<nebula::String> {
  size_t operator()(const nebula::String& s) const noexcept {
    return std::_Hash_impl::hash(s.data(), s.length());
  }
};

}  // namespace std
