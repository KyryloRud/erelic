//
// Created by Kyrylo Rud on 05.05.2025.
//

#include <cstddef>

#include "address.hpp"
#include "device.hpp"

namespace erelic {
auto device::read(address absolute, address relative) const noexcept -> std::byte {
  return impl->read(absolute, relative);
}

auto device::write(address absolute, address relative, std::byte value) noexcept -> write_status {
  return impl->write(absolute, relative, value);
}
}; // namespace erelic
