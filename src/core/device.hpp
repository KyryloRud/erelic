//
// Created by Kyrylo Rud on 05.05.2025.
//

#pragma once

#include <concepts>
#include <memory>
#include <ostream>

#include "address.hpp"

namespace erelic {
enum class write_status {
  WRITTEN,
  FAILED,
  IGNORED,
};

template <typename T>
concept io_device = requires(const T dev, address a, address r) {
  { dev.read(a, r) } noexcept -> std::same_as<std::byte>;
} && requires(T dev, address a, address r, std::byte v) {
  { dev.write(a, r, v) } noexcept -> std::same_as<write_status>;
};

class device {
public:
  template <io_device T>
  explicit device(T &&impl);

  template <io_device T>
  explicit device(std::shared_ptr<T> ptr);

  [[nodiscard]] auto read(address absolute, address relative) const noexcept -> std::byte;
  [[nodiscard]] auto write(address absolute, address relative, std::byte value) noexcept -> write_status;

private:
  struct idevice {
    virtual ~idevice() = default;
    virtual auto read(address, address) const noexcept -> std::byte = 0;
    virtual auto write(address, address, std::byte) noexcept -> write_status = 0;
  };

  template <typename T>
  struct model : idevice {
    T impl;

    explicit model(T i) : impl(std::move(i)) {}

    auto read(address a, address r) const noexcept -> std::byte override { return impl.read(a, r); }
    auto write(address a, address r, std::byte v) noexcept -> write_status override { return impl.write(a, r, v); }
  };

private:
  std::shared_ptr<idevice> impl;
};

template <io_device T>
device::device(T &&impl) : impl{std::make_shared<model<std::decay_t<T>>>(std::forward<T>(impl))} {}

template <io_device T>
device::device(std::shared_ptr<T> ptr) : impl{ptr} {}
}; // namespace erelic
