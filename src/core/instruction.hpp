//
// Created by Kyrylo Rud on 05.05.2025.
//

#pragma once

#include <cstddef>
#include <ostream>

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
};

auto operator<<(std::ostream &os, const mnemonic &m) -> std::ostream &;

enum class address_mode {
  ABSL,
  ABSX,
  ABSY,
  ACCU,
  IMME,
  IMPL,
  INDR,
  INDX,
  INDY,
  RELA,
  ZPAG,
  ZPAX,
  ZPAY,
};

auto operator<<(std::ostream &os, const address_mode &m) -> std::ostream &;

enum class instruction_set {
  STND,
  NMOS,
};

auto operator<<(std::ostream &os, const instruction_set &s) -> std::ostream &;

class instruction {
public:
  const std::byte opcode = std::byte{0xEA};
  const mnemonic op = mnemonic::NOP;
  const address_mode mode = address_mode::IMPL;
  const size_t length = 1;
  const size_t cycles = 2;
  const instruction_set set = instruction_set::STND;

  auto operator==(const instruction &o) const noexcept -> bool;
};

auto operator<<(std::ostream &os, const instruction &instruction) -> std::ostream &;

enum class page_boundary {
  SAME,
  NEXT,
};

auto as_instruction(std::byte byte, instruction_set set) -> instruction;
auto cycles_with_penalty(const instruction &info, page_boundary page_relation) -> size_t;
}; // namespace erelic
