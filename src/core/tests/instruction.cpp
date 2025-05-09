//
// Created by Kyrylo Rud on 07.05.2025.
//

#include <cstddef>
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <ranges>
#include <tuple>

#include "instruction.hpp"

using namespace erelic;

namespace instruction_sets {
constexpr auto stnd = std::array{
  // clang-format off
  instruction{ .opcode=std::byte{0x69}, .op=mnemonic::ADC, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x65}, .op=mnemonic::ADC, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x75}, .op=mnemonic::ADC, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x6D}, .op=mnemonic::ADC, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x7D}, .op=mnemonic::ADC, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x79}, .op=mnemonic::ADC, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x61}, .op=mnemonic::ADC, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x71}, .op=mnemonic::ADC, .mode=address_mode::INDY, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x29}, .op=mnemonic::AND, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x25}, .op=mnemonic::AND, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x35}, .op=mnemonic::AND, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x2D}, .op=mnemonic::AND, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x3D}, .op=mnemonic::AND, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x39}, .op=mnemonic::AND, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x21}, .op=mnemonic::AND, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x31}, .op=mnemonic::AND, .mode=address_mode::INDY, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x0A}, .op=mnemonic::ASL, .mode=address_mode::ACCU, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x06}, .op=mnemonic::ASL, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x16}, .op=mnemonic::ASL, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x0E}, .op=mnemonic::ASL, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x1E}, .op=mnemonic::ASL, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x90}, .op=mnemonic::BCC, .mode=address_mode::RELA, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xB0}, .op=mnemonic::BCS, .mode=address_mode::RELA, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xF0}, .op=mnemonic::BEQ, .mode=address_mode::RELA, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x24}, .op=mnemonic::BIT, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x2C}, .op=mnemonic::BIT, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x30}, .op=mnemonic::BMI, .mode=address_mode::RELA, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xD0}, .op=mnemonic::BNE, .mode=address_mode::RELA, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x10}, .op=mnemonic::BPL, .mode=address_mode::RELA, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x00}, .op=mnemonic::BRK, .mode=address_mode::IMPL, .length=1, .cycles=7, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x50}, .op=mnemonic::BVC, .mode=address_mode::RELA, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x70}, .op=mnemonic::BVS, .mode=address_mode::RELA, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x18}, .op=mnemonic::CLC, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xD8}, .op=mnemonic::CLD, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x58}, .op=mnemonic::CLI, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xB8}, .op=mnemonic::CLV, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xC9}, .op=mnemonic::CMP, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xC5}, .op=mnemonic::CMP, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xD5}, .op=mnemonic::CMP, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xCD}, .op=mnemonic::CMP, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xDD}, .op=mnemonic::CMP, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xD9}, .op=mnemonic::CMP, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xC1}, .op=mnemonic::CMP, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xD1}, .op=mnemonic::CMP, .mode=address_mode::INDY, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xE0}, .op=mnemonic::CPX, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xE4}, .op=mnemonic::CPX, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xEC}, .op=mnemonic::CPX, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xC0}, .op=mnemonic::CPY, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xC4}, .op=mnemonic::CPY, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xCC}, .op=mnemonic::CPY, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xC6}, .op=mnemonic::DEC, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xD6}, .op=mnemonic::DEC, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xCE}, .op=mnemonic::DEC, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xDE}, .op=mnemonic::DEC, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xCA}, .op=mnemonic::DEX, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x88}, .op=mnemonic::DEY, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x49}, .op=mnemonic::EOR, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x45}, .op=mnemonic::EOR, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x55}, .op=mnemonic::EOR, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x4D}, .op=mnemonic::EOR, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x5D}, .op=mnemonic::EOR, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x59}, .op=mnemonic::EOR, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x41}, .op=mnemonic::EOR, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x51}, .op=mnemonic::EOR, .mode=address_mode::INDY, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xE6}, .op=mnemonic::INC, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xF6}, .op=mnemonic::INC, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xEE}, .op=mnemonic::INC, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xFE}, .op=mnemonic::INC, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xE8}, .op=mnemonic::INX, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xC8}, .op=mnemonic::INY, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x4C}, .op=mnemonic::JMP, .mode=address_mode::ABSL, .length=3, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x6C}, .op=mnemonic::JMP, .mode=address_mode::INDR, .length=3, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x20}, .op=mnemonic::JSR, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xA9}, .op=mnemonic::LDA, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xA5}, .op=mnemonic::LDA, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xB5}, .op=mnemonic::LDA, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xAD}, .op=mnemonic::LDA, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xBD}, .op=mnemonic::LDA, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xB9}, .op=mnemonic::LDA, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xA1}, .op=mnemonic::LDA, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xB1}, .op=mnemonic::LDA, .mode=address_mode::INDY, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xA2}, .op=mnemonic::LDX, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xA6}, .op=mnemonic::LDX, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xB6}, .op=mnemonic::LDX, .mode=address_mode::ZPAY, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xAE}, .op=mnemonic::LDX, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xBE}, .op=mnemonic::LDX, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xA0}, .op=mnemonic::LDY, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xA4}, .op=mnemonic::LDY, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xB4}, .op=mnemonic::LDY, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xAC}, .op=mnemonic::LDY, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xBC}, .op=mnemonic::LDY, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x4A}, .op=mnemonic::LSR, .mode=address_mode::ACCU, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x46}, .op=mnemonic::LSR, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x56}, .op=mnemonic::LSR, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x4E}, .op=mnemonic::LSR, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x5E}, .op=mnemonic::LSR, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xEA}, .op=mnemonic::NOP, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x09}, .op=mnemonic::ORA, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x05}, .op=mnemonic::ORA, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x15}, .op=mnemonic::ORA, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x0D}, .op=mnemonic::ORA, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x1D}, .op=mnemonic::ORA, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x19}, .op=mnemonic::ORA, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x01}, .op=mnemonic::ORA, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x11}, .op=mnemonic::ORA, .mode=address_mode::INDY, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x48}, .op=mnemonic::PHA, .mode=address_mode::IMPL, .length=1, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x08}, .op=mnemonic::PHP, .mode=address_mode::IMPL, .length=1, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x68}, .op=mnemonic::PLA, .mode=address_mode::IMPL, .length=1, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x28}, .op=mnemonic::PLP, .mode=address_mode::IMPL, .length=1, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x2A}, .op=mnemonic::ROL, .mode=address_mode::ACCU, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x26}, .op=mnemonic::ROL, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x36}, .op=mnemonic::ROL, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x2E}, .op=mnemonic::ROL, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x3E}, .op=mnemonic::ROL, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x6A}, .op=mnemonic::ROR, .mode=address_mode::ACCU, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x66}, .op=mnemonic::ROR, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x76}, .op=mnemonic::ROR, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x6E}, .op=mnemonic::ROR, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x7E}, .op=mnemonic::ROR, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x40}, .op=mnemonic::RTI, .mode=address_mode::IMPL, .length=1, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x60}, .op=mnemonic::RTS, .mode=address_mode::IMPL, .length=1, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xE9}, .op=mnemonic::SBC, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xE5}, .op=mnemonic::SBC, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xF5}, .op=mnemonic::SBC, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xED}, .op=mnemonic::SBC, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xFD}, .op=mnemonic::SBC, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xF9}, .op=mnemonic::SBC, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xE1}, .op=mnemonic::SBC, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xF1}, .op=mnemonic::SBC, .mode=address_mode::INDY, .length=2, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x38}, .op=mnemonic::SEC, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xF8}, .op=mnemonic::SED, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x78}, .op=mnemonic::SEI, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x85}, .op=mnemonic::STA, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x95}, .op=mnemonic::STA, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x8D}, .op=mnemonic::STA, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x9D}, .op=mnemonic::STA, .mode=address_mode::ABSX, .length=3, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x99}, .op=mnemonic::STA, .mode=address_mode::ABSY, .length=3, .cycles=5, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x81}, .op=mnemonic::STA, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x91}, .op=mnemonic::STA, .mode=address_mode::INDY, .length=2, .cycles=6, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x86}, .op=mnemonic::STX, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x96}, .op=mnemonic::STX, .mode=address_mode::ZPAY, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x8E}, .op=mnemonic::STX, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x84}, .op=mnemonic::STY, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x94}, .op=mnemonic::STY, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x8C}, .op=mnemonic::STY, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xAA}, .op=mnemonic::TAX, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xA8}, .op=mnemonic::TAY, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0xBA}, .op=mnemonic::TSX, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x8A}, .op=mnemonic::TXA, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x9A}, .op=mnemonic::TXS, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  instruction{ .opcode=std::byte{0x98}, .op=mnemonic::TYA, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::STND },
  // clang-format on
};

constexpr auto nmos = std::array{
  // clang-format off
  instruction{ .opcode=std::byte{0xCF}, .op=mnemonic::DCP, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xEF}, .op=mnemonic::ISC, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xAF}, .op=mnemonic::LAX, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x2F}, .op=mnemonic::RLA, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x6F}, .op=mnemonic::RRA, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x8F}, .op=mnemonic::SAX, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x0F}, .op=mnemonic::SLO, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x4F}, .op=mnemonic::SRE, .mode=address_mode::ABSL, .length=3, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xDF}, .op=mnemonic::DCP, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xFF}, .op=mnemonic::ISC, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x3F}, .op=mnemonic::RLA, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x7F}, .op=mnemonic::RRA, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x9C}, .op=mnemonic::SHY, .mode=address_mode::ABSX, .length=3, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x1F}, .op=mnemonic::SLO, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x5F}, .op=mnemonic::SRE, .mode=address_mode::ABSX, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xDB}, .op=mnemonic::DCP, .mode=address_mode::ABSY, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xFB}, .op=mnemonic::ISC, .mode=address_mode::ABSY, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xBB}, .op=mnemonic::LAS, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xBF}, .op=mnemonic::LAX, .mode=address_mode::ABSY, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x3B}, .op=mnemonic::RLA, .mode=address_mode::ABSY, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x7B}, .op=mnemonic::RRA, .mode=address_mode::ABSY, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x9F}, .op=mnemonic::SHA, .mode=address_mode::ABSY, .length=3, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x9E}, .op=mnemonic::SHX, .mode=address_mode::ABSY, .length=3, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x1B}, .op=mnemonic::SLO, .mode=address_mode::ABSY, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x5B}, .op=mnemonic::SRE, .mode=address_mode::ABSY, .length=3, .cycles=7, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x9B}, .op=mnemonic::TAS, .mode=address_mode::ABSY, .length=3, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x02}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x12}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x22}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x32}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x42}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x52}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x62}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x72}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x92}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xB2}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xD2}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xF2}, .op=mnemonic::JAM, .mode=address_mode::ACCU, .length=1, .cycles=0, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x4B}, .op=mnemonic::ALR, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x0B}, .op=mnemonic::ANC, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x2B}, .op=mnemonic::ANC, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x8B}, .op=mnemonic::ANE, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x6B}, .op=mnemonic::ARR, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xAB}, .op=mnemonic::LXA, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xCB}, .op=mnemonic::SBX, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xEB}, .op=mnemonic::SBC, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xC3}, .op=mnemonic::DCP, .mode=address_mode::INDX, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xE3}, .op=mnemonic::ISC, .mode=address_mode::INDX, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xA3}, .op=mnemonic::LAX, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x23}, .op=mnemonic::RLA, .mode=address_mode::INDX, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x63}, .op=mnemonic::RRA, .mode=address_mode::INDX, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x83}, .op=mnemonic::SAX, .mode=address_mode::INDX, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x03}, .op=mnemonic::SLO, .mode=address_mode::INDX, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x43}, .op=mnemonic::SRE, .mode=address_mode::INDX, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xD3}, .op=mnemonic::DCP, .mode=address_mode::INDY, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xF3}, .op=mnemonic::ISC, .mode=address_mode::INDY, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xB3}, .op=mnemonic::LAX, .mode=address_mode::INDY, .length=2, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x33}, .op=mnemonic::RLA, .mode=address_mode::INDY, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x73}, .op=mnemonic::RRA, .mode=address_mode::INDY, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x93}, .op=mnemonic::SHA, .mode=address_mode::INDY, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x13}, .op=mnemonic::SLO, .mode=address_mode::INDY, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x53}, .op=mnemonic::SRE, .mode=address_mode::INDY, .length=2, .cycles=8, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x0C}, .op=mnemonic::NOP, .mode=address_mode::ABSL, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x1C}, .op=mnemonic::NOP, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x3C}, .op=mnemonic::NOP, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x5C}, .op=mnemonic::NOP, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x7C}, .op=mnemonic::NOP, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xDC}, .op=mnemonic::NOP, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xFC}, .op=mnemonic::NOP, .mode=address_mode::ABSX, .length=3, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x80}, .op=mnemonic::NOP, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x82}, .op=mnemonic::NOP, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x89}, .op=mnemonic::NOP, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xC2}, .op=mnemonic::NOP, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xE2}, .op=mnemonic::NOP, .mode=address_mode::IMME, .length=2, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x1A}, .op=mnemonic::NOP, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x3A}, .op=mnemonic::NOP, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x5A}, .op=mnemonic::NOP, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x7A}, .op=mnemonic::NOP, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xDA}, .op=mnemonic::NOP, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xFA}, .op=mnemonic::NOP, .mode=address_mode::IMPL, .length=1, .cycles=2, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x04}, .op=mnemonic::NOP, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x44}, .op=mnemonic::NOP, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x64}, .op=mnemonic::NOP, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x14}, .op=mnemonic::NOP, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x34}, .op=mnemonic::NOP, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x54}, .op=mnemonic::NOP, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x74}, .op=mnemonic::NOP, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xD4}, .op=mnemonic::NOP, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xF4}, .op=mnemonic::NOP, .mode=address_mode::ZPAX, .length=2, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xC7}, .op=mnemonic::DCP, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xE7}, .op=mnemonic::ISC, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xA7}, .op=mnemonic::LAX, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x27}, .op=mnemonic::RLA, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x67}, .op=mnemonic::RRA, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x87}, .op=mnemonic::SAX, .mode=address_mode::ZPAG, .length=2, .cycles=3, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x07}, .op=mnemonic::SLO, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x47}, .op=mnemonic::SRE, .mode=address_mode::ZPAG, .length=2, .cycles=5, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xD7}, .op=mnemonic::DCP, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xF7}, .op=mnemonic::ISC, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x37}, .op=mnemonic::RLA, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x77}, .op=mnemonic::RRA, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x17}, .op=mnemonic::SLO, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x57}, .op=mnemonic::SRE, .mode=address_mode::ZPAX, .length=2, .cycles=6, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0xB7}, .op=mnemonic::LAX, .mode=address_mode::ZPAY, .length=2, .cycles=4, .set=instruction_set::NMOS },
  instruction{ .opcode=std::byte{0x97}, .op=mnemonic::SAX, .mode=address_mode::ZPAY, .length=2, .cycles=4, .set=instruction_set::NMOS },
  // clang-format on
};
}; // namespace instruction_sets

namespace penalty_opcodes {
enum class type {
  NEVER_CROSS,
  SINGLE_PENALTY,
  BRANCH_PENALTY,
};

constexpr auto single = std::array{
  std::byte{0x7D}, std::byte{0x79}, std::byte{0x71}, std::byte{0x3D}, std::byte{0x39}, std::byte{0x31},
  std::byte{0xDD}, std::byte{0xD9}, std::byte{0xD1}, std::byte{0x5D}, std::byte{0x59}, std::byte{0x51},
  std::byte{0xBD}, std::byte{0xB9}, std::byte{0xB1}, std::byte{0xBE}, std::byte{0xBC}, std::byte{0x1D},
  std::byte{0x19}, std::byte{0x11}, std::byte{0xFD}, std::byte{0xF9}, std::byte{0xF1},
};

constexpr auto branch = std::array{
  std::byte{0x90}, std::byte{0xB0}, std::byte{0xF0}, std::byte{0x30},
  std::byte{0xD0}, std::byte{0x10}, std::byte{0x50}, std::byte{0x70},
};

namespace {
template <std::size_t N1, std::size_t N2>
consteval auto opcodes_excluding(const std::array<std::byte, N1> &a, const std::array<std::byte, N2> &b) {
  constexpr auto opcode_count = 0xFF + 1;
  constexpr auto out_size = opcode_count - (N1 + N2);

  auto result = std::array<std::byte, out_size>{};
  auto view = std::views::iota(0, int(opcode_count)) |
              std::views::transform([](int x) { return static_cast<std::byte>(x); }) |
              std::views::filter([&](std::byte v) {
                return std::ranges::none_of(a, [&](auto x) { return x == v; }) &&
                       std::ranges::none_of(b, [&](auto x) { return x == v; });
              });

  std::ranges::copy_n(std::ranges::begin(view), out_size, result.begin());
  return result;
}
}; // namespace

constexpr auto never_cross = opcodes_excluding(branch, single);
}; // namespace penalty_opcodes

class decode_instruction : public testing::TestWithParam<instruction> {};

INSTANTIATE_TEST_SUITE_P(stdn, decode_instruction, testing::ValuesIn(instruction_sets::stnd));

INSTANTIATE_TEST_SUITE_P(nmos, decode_instruction, testing::ValuesIn(instruction_sets::nmos));

TEST_P(decode_instruction, as_instruction) {
  auto expected = GetParam();
  auto actual = erelic::as_instruction(expected.opcode, expected.set);
  EXPECT_EQ(expected, actual);
}

class decode_illegal_instruction : public testing::TestWithParam<instruction> {};

INSTANTIATE_TEST_SUITE_P(illegal, decode_illegal_instruction, testing::ValuesIn(instruction_sets::nmos));

TEST_P(decode_illegal_instruction, as_instruction) {
  auto expected = erelic::instruction{};
  auto actual = erelic::as_instruction(GetParam().opcode, instruction_set::STND);
  EXPECT_EQ(expected, actual);
}

class calculate_cycle_penalty : public testing::TestWithParam<std::tuple<penalty_opcodes::type, std::byte>> {};

INSTANTIATE_TEST_SUITE_P(NEVER_CROSS, calculate_cycle_penalty,
                         testing::Combine(testing::Values(penalty_opcodes::type::NEVER_CROSS),
                                          testing::ValuesIn(penalty_opcodes::never_cross)));

INSTANTIATE_TEST_SUITE_P(SINGLE_PENALTY, calculate_cycle_penalty,
                         testing::Combine(testing::Values(penalty_opcodes::type::SINGLE_PENALTY),
                                          testing::ValuesIn(penalty_opcodes::single)));

INSTANTIATE_TEST_SUITE_P(BRANCH_PENALTY, calculate_cycle_penalty,
                         testing::Combine(testing::Values(penalty_opcodes::type::BRANCH_PENALTY),
                                          testing::ValuesIn(penalty_opcodes::branch)));

TEST_P(calculate_cycle_penalty, cycles_with_penalty) {
  auto [penalty_type, byte] = GetParam();
  auto instruction = erelic::as_instruction(byte, instruction_set::STND);

  constexpr auto get_penalty = [](const auto type, const auto boundary) {
    switch (type) {
      using enum penalty_opcodes::type;
    case SINGLE_PENALTY: return page_boundary::SAME == boundary ? 0 : 1;
    case BRANCH_PENALTY: return page_boundary::SAME == boundary ? 1 : 2;
    case NEVER_CROSS: return 0;
    }
  };

  const auto same_page_penalty = get_penalty(penalty_type, page_boundary::SAME);
  const auto next_page_penalty = get_penalty(penalty_type, page_boundary::NEXT);

  EXPECT_EQ(instruction.cycles + same_page_penalty, erelic::cycles_with_penalty(instruction, page_boundary::SAME));
  EXPECT_EQ(instruction.cycles + next_page_penalty, erelic::cycles_with_penalty(instruction, page_boundary::NEXT));
}
