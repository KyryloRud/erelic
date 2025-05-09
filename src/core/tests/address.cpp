//
// Created by Kyrylo Rud on 07.05.2025.
//

#include <compare>
#include <cstddef>
#include <gtest/gtest.h>

#include "address.hpp"

using namespace erelic;

TEST(address, construct_from_address_raw) {
  const auto raw = address_raw{0xABCD};
  const auto addr = address{raw};

  EXPECT_EQ(addr.raw, raw);
  EXPECT_EQ(addr.bytes[0], std::byte{0xAB});
  EXPECT_EQ(addr.bytes[1], std::byte{0xCD});
}

TEST(address, construct_from_address_byte) {
  const auto addr = address{0xABCD};

  EXPECT_EQ(addr.raw, 0xABCD);
  EXPECT_EQ(addr.bytes[0], std::byte{0xAB});
  EXPECT_EQ(addr.bytes[1], std::byte{0xCD});
}

TEST(address, construct_from_bytes) {
  const auto bytes = address_bytes{std::byte{0x12}, std::byte{0x34}};
  const auto addr = address{bytes};

  EXPECT_EQ(addr.bytes, bytes);
  EXPECT_EQ(addr.raw, 0x1234);
}

TEST(address, compare_equal_addresses) {
  const auto a = address{0x102};
  const auto b = address{0x102};

  EXPECT_EQ((a <=> b), std::partial_ordering::equivalent);
}

TEST(address, compare_less_addresses) {
  const auto a = address{0x1};
  const auto b = address{0x2};

  EXPECT_EQ((a <=> b), std::partial_ordering::less);
}

TEST(address, compare_greater_addresses) {
  const auto a = address{0xFF};
  const auto b = address{0xAA};

  EXPECT_EQ((a <=> b), std::partial_ordering::greater);
}

TEST(address, relational_operators) {
  const auto low = address{0x1};
  const auto same = address{0x1};
  const auto high = address{0x2};

  EXPECT_TRUE(low < high);
  EXPECT_FALSE(low > high);
  EXPECT_TRUE(low <= high);
  EXPECT_FALSE(low >= high);
  EXPECT_FALSE(low == high);
  EXPECT_TRUE(low != high);

  EXPECT_TRUE(low == same);
  EXPECT_FALSE(low != same);
  EXPECT_TRUE(low <= same);
  EXPECT_TRUE(low >= same);
}

TEST(address_range, contains_single_value_range) {
  auto addr = address{0x10};
  auto range = address_range{addr, addr};

  EXPECT_TRUE(range.contains(addr));
  EXPECT_FALSE(range.contains(address{0x0F}));
  EXPECT_FALSE(range.contains(address{0x11}));
}

TEST(address_range, contains_value_inside_and_outside) {
  auto range = address_range{address{0x10}, address{0x20}};

  EXPECT_TRUE(range.contains(address{0x10}));
  EXPECT_TRUE(range.contains(address{0x15}));
  EXPECT_TRUE(range.contains(address{0x20}));
  EXPECT_FALSE(range.contains(address{0x0F}));
  EXPECT_FALSE(range.contains(address{0x21}));
}

TEST(address_range, overlaps_disjoint_low_and_high) {
  auto a = address_range{address{0x10}, address{0x20}};
  auto b = address_range{address{0x00}, address{0x0F}};
  auto c = address_range{address{0x21}, address{0x30}};

  EXPECT_FALSE(a.overlaps(b));
  EXPECT_FALSE(a.overlaps(c));
  EXPECT_FALSE(b.overlaps(a));
  EXPECT_FALSE(c.overlaps(a));
}

TEST(address_range, overlaps_edge_touching) {
  auto a = address_range{address{0x10}, address{0x20}};
  auto b = address_range{address{0x20}, address{0x30}};

  EXPECT_TRUE(a.overlaps(b));
  EXPECT_TRUE(b.overlaps(a));
}

TEST(address_range, overlaps_partial_and_full) {
  auto full = address_range{address{0x10}, address{0x30}};
  auto part = address_range{address{0x20}, address{0x40}};

  EXPECT_TRUE(full.overlaps(part));
  EXPECT_TRUE(part.overlaps(full));

  auto inside = address_range{address{0x15}, address{0x25}};
  EXPECT_TRUE(full.overlaps(inside));
  EXPECT_TRUE(inside.overlaps(full));
}

TEST(address_range, size_single_and_multiple) {
  auto single = address_range{address{0x10}, address{0x10}};
  auto multi = address_range{address{0x10}, address{0x20}};

  EXPECT_EQ(single.size(), static_cast<size_t>(1));
  EXPECT_EQ(multi.size(), static_cast<size_t>(0x20 - 0x10 + 1));
}

TEST(address_range, swap_from_and_till_if_needed) {
  auto low = address{0x10};
  auto high = address{0x20};

  auto range1 = address_range{low, high};
  EXPECT_EQ(range1.from, low);
  EXPECT_EQ(range1.till, high);

  auto range2 = address_range{high, low};
  EXPECT_EQ(range2.from, low);
  EXPECT_EQ(range2.till, high);
}
