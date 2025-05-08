//
// Created by Kyrylo Rud on 05.05.2025.
//

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <ranges>
#include <span>

namespace erelic {
using address_raw = std::uint16_t;
using address_bytes = std::array<std::byte, sizeof(address_raw)>;

constexpr auto to_address_bytes(address_raw value) noexcept -> address_bytes {
  if constexpr (std::endian::native == std::endian::little) {
    return std::bit_cast<address_bytes>(std::byteswap(value));
  } else {
    return std::bit_cast<address_bytes>(value);
  }
}

constexpr auto to_address_raw(address_bytes value) noexcept -> address_raw {
  if constexpr (std::endian::native == std::endian::little) {
    return std::byteswap(std::bit_cast<address_raw>(value));
  } else {
    return std::bit_cast<address_raw>(value);
  }
}

constexpr auto to_address_bytes(std::span<const std::byte, sizeof(address_raw)> bytes) noexcept -> address_bytes {
  address_bytes arr;
  std::ranges::copy(bytes, arr.begin());
  return arr;
}

struct address {
  address_bytes bytes;
  address_raw raw;

  explicit constexpr address(address_raw value) : bytes{to_address_bytes(value)}, raw{value} {}
  explicit constexpr address(std::span<const std::byte, sizeof(address_raw)> bytes)
      : bytes{to_address_bytes(bytes)}, raw{to_address_raw(to_address_bytes(bytes))} {}

  [[nodiscard]] auto operator<=>(const address &addr) const noexcept -> std::strong_ordering;
  [[nodiscard]] auto operator==(const address &addr) const noexcept -> bool = default;
};

auto operator<<(std::ostream &os, const address &a) -> std::ostream &;

struct address_range {
  address from;
  address till;

  constexpr address_range(address from, address till) : from{std::min(from, till)}, till{std::max(from, till)} {}

  [[nodiscard]] auto contains(address addr) const noexcept -> bool;
  [[nodiscard]] auto overlaps(address_range other) const noexcept -> bool;
  [[nodiscard]] auto size() const noexcept -> size_t;
};

auto operator<<(std::ostream &os, const address_range &r) -> std::ostream &;
}; // namespace erelic
