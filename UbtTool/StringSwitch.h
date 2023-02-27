#pragma once

#include <cstdint>
#include <string>

namespace {
  constexpr uint8_t MAX_LEN = 9;
  constexpr uint64_t N_HASH = static_cast<uint64_t>(-1);

  constexpr uint64_t raise128to(const uint8_t power) {
    return 1ULL << 7 * power;
  }

  constexpr bool strIsCorrect(const char* const str) {
    return (static_cast<signed char>(*str) > 0) ? strIsCorrect(str + 1) : (*str ? false : true);
  }

  constexpr uint8_t strLen(const char* const str) {
    return *str ? (1 + strLen(str + 1)) : 0;
  }

  constexpr uint64_t strHash(const char* str, const uint8_t current_len) {
    return *str ? (raise128to(current_len - 1) * static_cast<uint8_t>(*str) + strHash(str + 1, current_len - 1)) : 0;
  }
}

constexpr uint64_t strHashSwitch(const char* str) {
  return (strIsCorrect(str) && (strLen(str) <= MAX_LEN)) ? strHash(str, strLen(str)) : N_HASH;
}

inline uint64_t strHashSwitch(const std::string& str) {
  return (strIsCorrect(str.c_str()) && (str.length() <= MAX_LEN)) ? strHash(str.c_str(), static_cast<uint8_t>(str.length())) : N_HASH;
}
