//
// Created by Kyrylo Rud on 07.05.2025.
//

#pragma once

#include <cstddef>
#include <ostream>

namespace erelic {
auto operator<<(std::ostream &os, std::byte byte) -> std::ostream &;
};
