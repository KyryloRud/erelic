//
// Created by Kyrylo Rud on 07.05.2025.
//

#include "utility.hpp"

#include <format>

namespace std {
auto operator<<(std::ostream &os, std::byte byte) -> std::ostream & {
  std::format_to(std::ostreambuf_iterator(os), "0x{:02X}", std::to_integer<unsigned>(byte));
  return os;
}
}; // namespace std
