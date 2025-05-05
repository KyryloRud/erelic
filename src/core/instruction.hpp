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
  DOP,
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
  TOP,
  TSX,
  TXA,
  TXS,
  TYA,
  USBC,
};

enum class address_mode {
  a,
  abs,
  absx,
  absy,
  imd,
  impl,
  ind,
  indx,
  indy,
  rel,
  zpg,
  zpgx,
  zpgy,
};

struct instruction {
  const std::byte opcode;
  const mnemonic op;
  const address_mode mode;
  const size_t length;
  const size_t cycles;
  const bool illegal;
};

auto as_instruction(std::byte byte) -> instruction;
}; // namespace erelic
