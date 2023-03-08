#pragma once

#include "NetworkOrderConvert.hpp"

namespace ubt {
  template <std::integral T>
  void Document::loadNumber(T& number, std::istream& input) {
    if(input.read(reinterpret_cast<char*>(&number), sizeof(number)).gcount() != sizeof(number)) {
      throw std::underflow_error("read not enough bytes");
    }
    number = ntoh(number);
  }

  template <std::integral T>
  void Document::saveNumber(const T& number, std::ostream& output) {
    const T n = hton(number);
    output.write(reinterpret_cast<const char*>(&n), sizeof(n));
  }
}
