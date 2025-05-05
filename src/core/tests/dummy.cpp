//
// Created by Kyrylo Rud on 05.05.2025.
//

#include <gtest/gtest.h>

#include "instruction.hpp"

using namespace erelic;

TEST(AlwaysPass, Dummy) {
  auto inst = as_instruction(std::byte(0x00));
  EXPECT_TRUE(inst.op == mnemonic::NOP);
}
