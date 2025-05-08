//
// Created by Kyrylo Rud on 05.05.2025.
//

#include "address.hpp"

#include <format>
#include <iterator>

#include "utility.hpp"

namespace erelic {
auto address::operator<=>(const address &addr) const noexcept -> std::strong_ordering { return raw <=> addr.raw; }

auto operator<<(std::ostream &os, const address &a) -> std::ostream & {
  std::format_to(std::ostreambuf_iterator(os), "ADDR(0x{:04X})", a.raw);
  return os;
}

auto address_range::contains(address addr) const noexcept -> bool { return from <= addr && addr <= till; }

auto address_range::overlaps(address_range other) const noexcept -> bool {
  return from <= other.till && other.from <= till;
}

auto address_range::size() const noexcept -> size_t { return till.raw - from.raw + 1; }

auto operator<<(std::ostream &os, const address_range &r) -> std::ostream & {
  os << "RANGE(";
  std::format_to(std::ostreambuf_iterator(os), "0x{:04X}", r.from.raw);
  os << "...";
  std::format_to(std::ostreambuf_iterator(os), "0x{:04X}", r.till.raw);
  os << ")";
  return os;
}
}; // namespace erelic
