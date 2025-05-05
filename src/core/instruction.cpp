//
// Created by Kyrylo Rud on 05.05.2025.
//

#include "instruction.hpp"

namespace erelic {
auto as_instruction(std::byte byte) -> instruction {
  return {
    .opcode = byte,
    .op = mnemonic::NOP,
    .mode = address_mode::a,
    .length = 0,
    .cycles = 0,
    .illegal = true,
  };
}
}; // namespace erelic
