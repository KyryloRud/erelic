//
// Created by Kyrylo Rud on 09.05.2025.
//

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <random>
#include <string>
#include <utility>

#include "address.hpp"
#include "device.hpp"

using namespace erelic;

namespace {
struct io_device_mock {
  std::byte read_ret{0};
  address_access write_ret{address_access::WRITTEN};

  explicit io_device_mock(std::byte r = std::byte{0}, address_access w = address_access::WRITTEN) noexcept
      : read_ret(r), write_ret(w) {}

  [[nodiscard]] auto read(address /*unused*/, address /*unused*/) const noexcept -> std::byte { return read_ret; }
  [[nodiscard]] auto write(address /*unused*/, address /*unused*/, std::byte /*unused*/) const noexcept
    -> address_access {
    return write_ret;
  }
};

static_assert(std::constructible_from<device, io_device_mock &>);
static_assert(std::constructible_from<device, io_device_mock>);

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
struct move_only_device {
  move_only_device() = default;
  ~move_only_device() = default;
  move_only_device(move_only_device &&) = default;
  move_only_device(const move_only_device &) = delete;

  [[nodiscard]] static auto read(address /*unused*/, address /*unused*/) noexcept -> std::byte {
    return std::byte{0xAA};
  }
  [[nodiscard]] static auto write(address /*unused*/, address /*unused*/, std::byte /*unused*/) noexcept
    -> address_access {
    return address_access::FAILED;
  }
};

static_assert(std::constructible_from<device, move_only_device>);

template <std::size_t N>
struct buffer_device {
  std::array<std::byte, N> buf;

  explicit buffer_device(std::array<std::byte, N> b) noexcept : buf(std::move(b)) {}

  [[nodiscard]] auto read(address a, address /*unused*/) const noexcept -> std::byte { return buf[a.raw]; }
  [[nodiscard]] auto write(address /*unused*/, address /*unused*/, std::byte /*unused*/) noexcept -> address_access {
    return address_access::IGNORED;
  }
};
}; // namespace

TEST(device, read_returns_value_from_impl) {
  auto mock = io_device_mock{std::byte{0x42}};
  auto dev = device{mock};
  auto abs = address{0x1000};
  auto rel = address{0x0001};
  EXPECT_EQ(dev.read(abs, rel), std::byte{0x42});
}

TEST(device, write_returns_address_access_from_impl) {
  auto mock_fail = io_device_mock{std::byte{0}, address_access::FAILED};
  auto dev_fail = device{mock_fail};
  EXPECT_EQ(dev_fail.write(address{0x1234}, address{0x0004}, std::byte{0x7F}), address_access::FAILED);

  auto mock_ok = io_device_mock{};
  auto dev_ok = device{mock_ok};
  EXPECT_EQ(dev_ok.write(address{0xABCD}, address{0x00AB}, std::byte{0x01}), address_access::WRITTEN);
}

TEST(device, copy_preserves_behavior) {
  auto mock = io_device_mock{std::byte{0xAB}, address_access::WRITTEN};
  auto dev1 = device{mock};
  auto dev2 = dev1;

  auto a1 = address{0x0011};
  auto r1 = address{0x0022};
  EXPECT_EQ(dev2.read(a1, r1), std::byte{0xAB});
  EXPECT_EQ(dev2.write(a1, r1, std::byte{0xEE}), address_access::WRITTEN);
  EXPECT_EQ(dev1.read(a1, r1), std::byte{0xAB});
}

TEST(device, read_with_edge_addresses) {
  auto mock = io_device_mock{std::byte{0x10}};
  auto dev = device{mock};

  EXPECT_EQ(dev.read(address{0x0000}, address{0x0000}), std::byte{0x10});
  EXPECT_EQ(dev.read(address{0x0000}, address{0xFFFF}), std::byte{0x10});
  EXPECT_EQ(dev.read(address{0xFFFF}, address{0x0000}), std::byte{0x10});
  EXPECT_EQ(dev.read(address{0xFFFF}, address{0xFFFF}), std::byte{0x10});
}

TEST(device, write_with_edge_addresses) {
  auto mock = io_device_mock{};
  auto dev = device{mock};

  EXPECT_EQ(dev.write(address{0x0000}, address{0x0000}, std::byte{0x08}), address_access::WRITTEN);
  EXPECT_EQ(dev.write(address{0x0000}, address{0xFFFF}, std::byte{0x08}), address_access::WRITTEN);
  EXPECT_EQ(dev.write(address{0xFFFF}, address{0x0000}, std::byte{0x08}), address_access::WRITTEN);
  EXPECT_EQ(dev.write(address{0xFFFF}, address{0xFFFF}, std::byte{0x08}), address_access::WRITTEN);
}

TEST(device, read_is_const_and_noexcept) {
  auto mock = io_device_mock{std::byte{0x99}};
  auto const dev = device{mock};
  EXPECT_NO_THROW((void)dev.read(address{0}, address{0}));
}

TEST(device, write_is_noexcept) {
  auto mock = io_device_mock{};
  auto dev = device{mock};
  EXPECT_NO_THROW((void)dev.write(address{0}, address{0}, std::byte{0xFF}));
}

TEST(device, supports_move_only_impl) {
  auto mod = move_only_device{};
  auto dev = device{std::move(mod)};
  EXPECT_EQ(dev.read(address{0}, address{0}), std::byte{0xAA});
  EXPECT_EQ(dev.write(address{0}, address{0}, std::byte{0}), address_access::FAILED);
}

namespace {
consteval auto make_max_memory_buf() {
  constexpr auto max_addressable_memory_size = 0x1'0000;
  auto data = std::array<std::byte, max_addressable_memory_size>{};
  auto counter = std::uint8_t{0};
  std::ranges::generate(data, [&counter]() { return std::byte{counter++}; });
  return data;
}
}; // namespace

TEST(device, random_access_buffer_returns_correct_values) {
  constexpr auto data = make_max_memory_buf();

  auto rng = std::mt19937_64{std::random_device{}()};
  auto shuffled = data;
  std::shuffle(shuffled.begin(), shuffled.end(), rng);

  auto dev = device{buffer_device<std::size(data)>{shuffled}};

  auto addrs = std::array<uint16_t, std::size(data)>{};
  std::ranges::iota(addrs, 0U);
  std::shuffle(addrs.begin(), addrs.end(), rng);

  for (auto addr : addrs) {
    SCOPED_TRACE("addr=" + std::to_string(addr));
    EXPECT_EQ(dev.read(address{addr}, address{0}), shuffled[addr]);
  }
}
