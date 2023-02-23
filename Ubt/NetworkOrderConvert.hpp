#pragma once

#include <bit>
#include <array>
#include <concepts>
#include <algorithm>

template<std::integral T>
constexpr T byteswap(T value) noexcept {
  static_assert(std::has_unique_object_representations_v<T>, "T may not have padding bits");
  auto value_representation = std::bit_cast<std::array<std::byte, sizeof(T)>>(value);
  std::ranges::reverse(value_representation);
  return std::bit_cast<T>(value_representation);
}

template <typename T>
T ntoh(const T n) {
  if constexpr(std::endian::native == std::endian::little) {
    return byteswap(n);
  }
  else if constexpr(std::endian::native == std::endian::big) {
    return n;
  }

  return 0;
}

template <typename T>
T hton(const T n) {
  return ntoh(n);
}
