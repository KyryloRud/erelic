//
// Created by Kyrylo Rud on 05.05.2025.
//

#pragma once

#include <cstddef>

namespace erelic {
enum class mnemonic {
  ADC,
  ALR,
  ANC,
  AND,
  ANE,
  ARR,
  ASL,
  BCC,
  BCS,
  BEQ,
  BIT,
  BMI,
  BNE,
  BPL,
  BRK,
  BVC,
  BVS,
  CLC,
  CLD,
  CLI,
  CLV,
  CMP,
  CPX,
  CPY,
  DCP,
  DEC,
  DEX,
  DEY,
  EOR,
  INC,
  INX,
  INY,
  ISC,
  JAM,
  JMP,
  JSR,
  LAS,
  LAX,
  LDA,
  LDX,
  LDY,
  LSR,
  LXA,
  NOP,
  ORA,
  PHA,
  PHP,
  PLA,
  PLP,
  RLA,
  ROL,
  ROR,
  RRA,
  RTI,
  RTS,
  SAX,
  SBC,
  SBX,
  SEC,
  SED,
  SEI,
  SHA,
  SHX,
  SHY,
  SLO,
  SRE,
  STA,
  STX,
  STY,
  TAS,
  TAX,
  TAY,
  TSX,
  TXA,
  TXS,
  TYA,
  USBC,
};

enum class address_mode {
  ABSOLUTE,
  ABSOLUTEX,
  ABSOLUTEY,
  ACCUMULATOR,
  IMMEDIATE,
  IMPLIED,
  INDIRECT,
  INDIRECTX,
  INDIRECTY,
  RELATIVE,
  ZEROPAGE,
  ZEROPAGEX,
  ZEROPAGEY,
};

struct instruction {
  const std::byte opcode = std::byte{0x80};
  const mnemonic op = mnemonic::NOP;
  const address_mode mode = address_mode::IMMEDIATE;
  const size_t length = 2;
  const size_t cycles = 2;
  const bool illegal = true;
};

enum class address_boundary {
  CROSSED,
  SAME,
};

auto as_instruction(std::byte byte) -> instruction;
auto cycles_with_penalty(const instruction &info, address_boundary page_relation) -> size_t;
}; // namespace erelic
