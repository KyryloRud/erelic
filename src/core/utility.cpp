//
// Created by Kyrylo Rud on 07.05.2025.
//

#include "utility.hpp"

#include <iomanip>

namespace erelic {
auto operator<<(std::ostream &os, std::byte byte) -> std::ostream & {
  auto flags = os.flags();
  auto fill = os.fill();

  os << std::hex;
  os << std::showbase;
  os << std::internal;
  os << std::setw(4);
  os << std::setfill('0');
  os << static_cast<int>(byte);

  os.flags(flags);
  os.fill(fill);

  return os;
}
}; // namespace erelic
