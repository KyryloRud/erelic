//
// Created by Kyrylo Rud on 05.05.2025.
//

#include "instruction.hpp"

#include <iomanip>
#include <unordered_map>

namespace {
using namespace erelic;

constexpr auto which_instruction_set(mnemonic op) -> instruction_set {
  switch (op) {
  case mnemonic::ALR: [[fallthrough]];
  case mnemonic::ANC: [[fallthrough]];
  case mnemonic::ANE: [[fallthrough]];
  case mnemonic::ARR: [[fallthrough]];
  case mnemonic::DCP: [[fallthrough]];
  case mnemonic::ISC: [[fallthrough]];
  case mnemonic::JAM: [[fallthrough]];
  case mnemonic::LAS: [[fallthrough]];
  case mnemonic::LAX: [[fallthrough]];
  case mnemonic::LXA: [[fallthrough]];
  case mnemonic::RLA: [[fallthrough]];
  case mnemonic::RRA: [[fallthrough]];
  case mnemonic::SAX: [[fallthrough]];
  case mnemonic::SBX: [[fallthrough]];
  case mnemonic::SHA: [[fallthrough]];
  case mnemonic::SHX: [[fallthrough]];
  case mnemonic::SHY: [[fallthrough]];
  case mnemonic::SLO: [[fallthrough]];
  case mnemonic::SRE: [[fallthrough]];
  case mnemonic::TAS: [[fallthrough]];
  case mnemonic::SBC: return instruction_set::NMOS;
  default: return instruction_set::STND;
  }
}

constexpr auto instruction_length(address_mode mode) -> size_t {
  switch (mode) {
  case address_mode::ACCU: return 1;
  case address_mode::ABSL: return 3;
  case address_mode::ABSX: return 3;
  case address_mode::ABSY: return 3;
  case address_mode::IMME: return 2;
  case address_mode::IMPL: return 1;
  case address_mode::INDR: return 3;
  case address_mode::INDX: return 2;
  case address_mode::INDY: return 2;
  case address_mode::RELA: return 2;
  case address_mode::ZPAG: return 2;
  case address_mode::ZPAX: return 2;
  case address_mode::ZPAY: return 2;
  }
}

using instr_info = std::tuple<mnemonic, size_t /* cycles */, address_mode>;
auto instructions_info = std::unordered_map<std::byte, instr_info>{
  {std::byte{0x69}, {mnemonic::ADC, 2, address_mode::IMME}}, {std::byte{0x65}, {mnemonic::ADC, 3, address_mode::ZPAG}},
  {std::byte{0x75}, {mnemonic::ADC, 4, address_mode::ZPAX}}, {std::byte{0x6D}, {mnemonic::ADC, 4, address_mode::ABSL}},
  {std::byte{0x7D}, {mnemonic::ADC, 4, address_mode::ABSX}}, {std::byte{0x79}, {mnemonic::ADC, 4, address_mode::ABSY}},
  {std::byte{0x61}, {mnemonic::ADC, 6, address_mode::INDX}}, {std::byte{0x71}, {mnemonic::ADC, 5, address_mode::INDY}},
  {std::byte{0x29}, {mnemonic::AND, 2, address_mode::IMME}}, {std::byte{0x25}, {mnemonic::AND, 3, address_mode::ZPAG}},
  {std::byte{0x35}, {mnemonic::AND, 4, address_mode::ZPAX}}, {std::byte{0x2D}, {mnemonic::AND, 4, address_mode::ABSL}},
  {std::byte{0x3D}, {mnemonic::AND, 4, address_mode::ABSX}}, {std::byte{0x39}, {mnemonic::AND, 4, address_mode::ABSY}},
  {std::byte{0x21}, {mnemonic::AND, 6, address_mode::INDX}}, {std::byte{0x31}, {mnemonic::AND, 5, address_mode::INDY}},
  {std::byte{0x0A}, {mnemonic::ASL, 2, address_mode::ACCU}}, {std::byte{0x06}, {mnemonic::ASL, 5, address_mode::ZPAG}},
  {std::byte{0x16}, {mnemonic::ASL, 6, address_mode::ZPAX}}, {std::byte{0x0E}, {mnemonic::ASL, 6, address_mode::ABSL}},
  {std::byte{0x1E}, {mnemonic::ASL, 7, address_mode::ABSX}}, {std::byte{0x90}, {mnemonic::BCC, 2, address_mode::RELA}},
  {std::byte{0xB0}, {mnemonic::BCS, 2, address_mode::RELA}}, {std::byte{0x1A}, {mnemonic::NOP, 2, address_mode::IMPL}},
  {std::byte{0x3A}, {mnemonic::NOP, 2, address_mode::IMPL}}, {std::byte{0x5A}, {mnemonic::NOP, 2, address_mode::IMPL}},
  {std::byte{0x7A}, {mnemonic::NOP, 2, address_mode::IMPL}}, {std::byte{0xDA}, {mnemonic::NOP, 2, address_mode::IMPL}},
  {std::byte{0xFA}, {mnemonic::NOP, 2, address_mode::IMPL}}, {std::byte{0x80}, {mnemonic::NOP, 2, address_mode::IMME}},
  {std::byte{0x82}, {mnemonic::NOP, 2, address_mode::IMME}}, {std::byte{0x89}, {mnemonic::NOP, 2, address_mode::IMME}},
  {std::byte{0xC2}, {mnemonic::NOP, 2, address_mode::IMME}}, {std::byte{0xE2}, {mnemonic::NOP, 2, address_mode::IMME}},
  {std::byte{0x04}, {mnemonic::NOP, 3, address_mode::ZPAG}}, {std::byte{0x44}, {mnemonic::NOP, 3, address_mode::ZPAG}},
  {std::byte{0x64}, {mnemonic::NOP, 3, address_mode::ZPAG}}, {std::byte{0x14}, {mnemonic::NOP, 4, address_mode::ZPAX}},
  {std::byte{0x34}, {mnemonic::NOP, 4, address_mode::ZPAX}}, {std::byte{0x54}, {mnemonic::NOP, 4, address_mode::ZPAX}},
  {std::byte{0x74}, {mnemonic::NOP, 4, address_mode::ZPAX}}, {std::byte{0xD4}, {mnemonic::NOP, 4, address_mode::ZPAX}},
  {std::byte{0xF4}, {mnemonic::NOP, 4, address_mode::ZPAX}}, {std::byte{0x0C}, {mnemonic::NOP, 4, address_mode::ABSL}},
  {std::byte{0x1C}, {mnemonic::NOP, 4, address_mode::ABSX}}, {std::byte{0x3C}, {mnemonic::NOP, 4, address_mode::ABSX}},
  {std::byte{0x5C}, {mnemonic::NOP, 4, address_mode::ABSX}}, {std::byte{0x7C}, {mnemonic::NOP, 4, address_mode::ABSX}},
  {std::byte{0xDC}, {mnemonic::NOP, 4, address_mode::ABSX}}, {std::byte{0xFC}, {mnemonic::NOP, 4, address_mode::ABSX}},
  {std::byte{0x02}, {mnemonic::JAM, 0, address_mode::ACCU}}, {std::byte{0x12}, {mnemonic::JAM, 0, address_mode::ACCU}},
  {std::byte{0x22}, {mnemonic::JAM, 0, address_mode::ACCU}}, {std::byte{0x32}, {mnemonic::JAM, 0, address_mode::ACCU}},
  {std::byte{0x42}, {mnemonic::JAM, 0, address_mode::ACCU}}, {std::byte{0x52}, {mnemonic::JAM, 0, address_mode::ACCU}},
  {std::byte{0x62}, {mnemonic::JAM, 0, address_mode::ACCU}}, {std::byte{0x72}, {mnemonic::JAM, 0, address_mode::ACCU}},
  {std::byte{0x92}, {mnemonic::JAM, 0, address_mode::ACCU}}, {std::byte{0xB2}, {mnemonic::JAM, 0, address_mode::ACCU}},
  {std::byte{0xD2}, {mnemonic::JAM, 0, address_mode::ACCU}}, {std::byte{0xF2}, {mnemonic::JAM, 0, address_mode::ACCU}},
  {std::byte{0xF0}, {mnemonic::BEQ, 2, address_mode::RELA}}, {std::byte{0x24}, {mnemonic::BIT, 3, address_mode::ZPAG}},
  {std::byte{0x2C}, {mnemonic::BIT, 4, address_mode::ABSL}}, {std::byte{0x30}, {mnemonic::BMI, 2, address_mode::RELA}},
  {std::byte{0xD0}, {mnemonic::BNE, 2, address_mode::RELA}}, {std::byte{0x10}, {mnemonic::BPL, 2, address_mode::RELA}},
  {std::byte{0x00}, {mnemonic::BRK, 7, address_mode::IMPL}}, {std::byte{0x50}, {mnemonic::BVC, 2, address_mode::RELA}},
  {std::byte{0x70}, {mnemonic::BVS, 2, address_mode::RELA}}, {std::byte{0x18}, {mnemonic::CLC, 2, address_mode::IMPL}},
  {std::byte{0xD8}, {mnemonic::CLD, 2, address_mode::IMPL}}, {std::byte{0x58}, {mnemonic::CLI, 2, address_mode::IMPL}},
  {std::byte{0xB8}, {mnemonic::CLV, 2, address_mode::IMPL}}, {std::byte{0xC9}, {mnemonic::CMP, 2, address_mode::IMME}},
  {std::byte{0xC5}, {mnemonic::CMP, 3, address_mode::ZPAG}}, {std::byte{0xD5}, {mnemonic::CMP, 4, address_mode::ZPAX}},
  {std::byte{0xCD}, {mnemonic::CMP, 4, address_mode::ABSL}}, {std::byte{0xDD}, {mnemonic::CMP, 4, address_mode::ABSX}},
  {std::byte{0xD9}, {mnemonic::CMP, 4, address_mode::ABSY}}, {std::byte{0xC1}, {mnemonic::CMP, 6, address_mode::INDX}},
  {std::byte{0xD1}, {mnemonic::CMP, 5, address_mode::INDY}}, {std::byte{0xE0}, {mnemonic::CPX, 2, address_mode::IMME}},
  {std::byte{0xE4}, {mnemonic::CPX, 3, address_mode::ZPAG}}, {std::byte{0xEC}, {mnemonic::CPX, 4, address_mode::ABSL}},
  {std::byte{0xC0}, {mnemonic::CPY, 2, address_mode::IMME}}, {std::byte{0xC4}, {mnemonic::CPY, 3, address_mode::ZPAG}},
  {std::byte{0xCC}, {mnemonic::CPY, 4, address_mode::ABSL}}, {std::byte{0xC6}, {mnemonic::DEC, 5, address_mode::ZPAG}},
  {std::byte{0xD6}, {mnemonic::DEC, 6, address_mode::ZPAX}}, {std::byte{0xCE}, {mnemonic::DEC, 6, address_mode::ABSL}},
  {std::byte{0xDE}, {mnemonic::DEC, 7, address_mode::ABSX}}, {std::byte{0xCA}, {mnemonic::DEX, 2, address_mode::IMPL}},
  {std::byte{0x88}, {mnemonic::DEY, 2, address_mode::IMPL}}, {std::byte{0x49}, {mnemonic::EOR, 2, address_mode::IMME}},
  {std::byte{0x45}, {mnemonic::EOR, 3, address_mode::ZPAG}}, {std::byte{0x55}, {mnemonic::EOR, 4, address_mode::ZPAX}},
  {std::byte{0x4D}, {mnemonic::EOR, 4, address_mode::ABSL}}, {std::byte{0x5D}, {mnemonic::EOR, 4, address_mode::ABSX}},
  {std::byte{0x59}, {mnemonic::EOR, 4, address_mode::ABSY}}, {std::byte{0x41}, {mnemonic::EOR, 6, address_mode::INDX}},
  {std::byte{0x51}, {mnemonic::EOR, 5, address_mode::INDY}}, {std::byte{0xE6}, {mnemonic::INC, 5, address_mode::ZPAG}},
  {std::byte{0xF6}, {mnemonic::INC, 6, address_mode::ZPAX}}, {std::byte{0xEE}, {mnemonic::INC, 6, address_mode::ABSL}},
  {std::byte{0xFE}, {mnemonic::INC, 7, address_mode::ABSX}}, {std::byte{0xE8}, {mnemonic::INX, 2, address_mode::IMPL}},
  {std::byte{0xC8}, {mnemonic::INY, 2, address_mode::IMPL}}, {std::byte{0x4C}, {mnemonic::JMP, 3, address_mode::ABSL}},
  {std::byte{0x6C}, {mnemonic::JMP, 5, address_mode::INDR}}, {std::byte{0x20}, {mnemonic::JSR, 6, address_mode::ABSL}},
  {std::byte{0xA9}, {mnemonic::LDA, 2, address_mode::IMME}}, {std::byte{0xA5}, {mnemonic::LDA, 3, address_mode::ZPAG}},
  {std::byte{0xB5}, {mnemonic::LDA, 4, address_mode::ZPAX}}, {std::byte{0xAD}, {mnemonic::LDA, 4, address_mode::ABSL}},
  {std::byte{0xBD}, {mnemonic::LDA, 4, address_mode::ABSX}}, {std::byte{0xB9}, {mnemonic::LDA, 4, address_mode::ABSY}},
  {std::byte{0xA1}, {mnemonic::LDA, 6, address_mode::INDX}}, {std::byte{0xB1}, {mnemonic::LDA, 5, address_mode::INDY}},
  {std::byte{0xA2}, {mnemonic::LDX, 2, address_mode::IMME}}, {std::byte{0xA6}, {mnemonic::LDX, 3, address_mode::ZPAG}},
  {std::byte{0xB6}, {mnemonic::LDX, 4, address_mode::ZPAY}}, {std::byte{0xAE}, {mnemonic::LDX, 4, address_mode::ABSL}},
  {std::byte{0xBE}, {mnemonic::LDX, 4, address_mode::ABSY}}, {std::byte{0xA0}, {mnemonic::LDY, 2, address_mode::IMME}},
  {std::byte{0xA4}, {mnemonic::LDY, 3, address_mode::ZPAG}}, {std::byte{0xB4}, {mnemonic::LDY, 4, address_mode::ZPAX}},
  {std::byte{0xAC}, {mnemonic::LDY, 4, address_mode::ABSL}}, {std::byte{0xBC}, {mnemonic::LDY, 4, address_mode::ABSX}},
  {std::byte{0x4A}, {mnemonic::LSR, 2, address_mode::ACCU}}, {std::byte{0x46}, {mnemonic::LSR, 5, address_mode::ZPAG}},
  {std::byte{0x56}, {mnemonic::LSR, 6, address_mode::ZPAX}}, {std::byte{0x4E}, {mnemonic::LSR, 6, address_mode::ABSL}},
  {std::byte{0x5E}, {mnemonic::LSR, 7, address_mode::ABSX}}, {std::byte{0xEA}, {mnemonic::NOP, 2, address_mode::IMPL}},
  {std::byte{0x09}, {mnemonic::ORA, 2, address_mode::IMME}}, {std::byte{0x05}, {mnemonic::ORA, 3, address_mode::ZPAG}},
  {std::byte{0x15}, {mnemonic::ORA, 4, address_mode::ZPAX}}, {std::byte{0x0D}, {mnemonic::ORA, 4, address_mode::ABSL}},
  {std::byte{0x1D}, {mnemonic::ORA, 4, address_mode::ABSX}}, {std::byte{0x19}, {mnemonic::ORA, 4, address_mode::ABSY}},
  {std::byte{0x01}, {mnemonic::ORA, 6, address_mode::INDX}}, {std::byte{0x11}, {mnemonic::ORA, 5, address_mode::INDY}},
  {std::byte{0x48}, {mnemonic::PHA, 3, address_mode::IMPL}}, {std::byte{0x08}, {mnemonic::PHP, 3, address_mode::IMPL}},
  {std::byte{0x68}, {mnemonic::PLA, 4, address_mode::IMPL}}, {std::byte{0x28}, {mnemonic::PLP, 4, address_mode::IMPL}},
  {std::byte{0x2A}, {mnemonic::ROL, 2, address_mode::ACCU}}, {std::byte{0x26}, {mnemonic::ROL, 5, address_mode::ZPAG}},
  {std::byte{0x36}, {mnemonic::ROL, 6, address_mode::ZPAX}}, {std::byte{0x2E}, {mnemonic::ROL, 6, address_mode::ABSL}},
  {std::byte{0x3E}, {mnemonic::ROL, 7, address_mode::ABSX}}, {std::byte{0x6A}, {mnemonic::ROR, 2, address_mode::ACCU}},
  {std::byte{0x66}, {mnemonic::ROR, 5, address_mode::ZPAG}}, {std::byte{0x76}, {mnemonic::ROR, 6, address_mode::ZPAX}},
  {std::byte{0x6E}, {mnemonic::ROR, 6, address_mode::ABSL}}, {std::byte{0x7E}, {mnemonic::ROR, 7, address_mode::ABSX}},
  {std::byte{0x40}, {mnemonic::RTI, 6, address_mode::IMPL}}, {std::byte{0x60}, {mnemonic::RTS, 6, address_mode::IMPL}},
  {std::byte{0xE9}, {mnemonic::SBC, 2, address_mode::IMME}}, {std::byte{0xE5}, {mnemonic::SBC, 3, address_mode::ZPAG}},
  {std::byte{0xF5}, {mnemonic::SBC, 4, address_mode::ZPAX}}, {std::byte{0xED}, {mnemonic::SBC, 4, address_mode::ABSL}},
  {std::byte{0xFD}, {mnemonic::SBC, 4, address_mode::ABSX}}, {std::byte{0xF9}, {mnemonic::SBC, 4, address_mode::ABSY}},
  {std::byte{0xE1}, {mnemonic::SBC, 6, address_mode::INDX}}, {std::byte{0xF1}, {mnemonic::SBC, 5, address_mode::INDY}},
  {std::byte{0x38}, {mnemonic::SEC, 2, address_mode::IMPL}}, {std::byte{0xF8}, {mnemonic::SED, 2, address_mode::IMPL}},
  {std::byte{0x78}, {mnemonic::SEI, 2, address_mode::IMPL}}, {std::byte{0x85}, {mnemonic::STA, 3, address_mode::ZPAG}},
  {std::byte{0x95}, {mnemonic::STA, 4, address_mode::ZPAX}}, {std::byte{0x8D}, {mnemonic::STA, 4, address_mode::ABSL}},
  {std::byte{0x9D}, {mnemonic::STA, 5, address_mode::ABSX}}, {std::byte{0x99}, {mnemonic::STA, 5, address_mode::ABSY}},
  {std::byte{0x81}, {mnemonic::STA, 6, address_mode::INDX}}, {std::byte{0x91}, {mnemonic::STA, 6, address_mode::INDY}},
  {std::byte{0x86}, {mnemonic::STX, 3, address_mode::ZPAG}}, {std::byte{0x96}, {mnemonic::STX, 4, address_mode::ZPAY}},
  {std::byte{0x8E}, {mnemonic::STX, 4, address_mode::ABSL}}, {std::byte{0x84}, {mnemonic::STY, 3, address_mode::ZPAG}},
  {std::byte{0x94}, {mnemonic::STY, 4, address_mode::ZPAX}}, {std::byte{0x8C}, {mnemonic::STY, 4, address_mode::ABSL}},
  {std::byte{0xAA}, {mnemonic::TAX, 2, address_mode::IMPL}}, {std::byte{0xA8}, {mnemonic::TAY, 2, address_mode::IMPL}},
  {std::byte{0xBA}, {mnemonic::TSX, 2, address_mode::IMPL}}, {std::byte{0x8A}, {mnemonic::TXA, 2, address_mode::IMPL}},
  {std::byte{0x9A}, {mnemonic::TXS, 2, address_mode::IMPL}}, {std::byte{0x98}, {mnemonic::TYA, 2, address_mode::IMPL}},
  {std::byte{0x4B}, {mnemonic::ALR, 2, address_mode::IMME}}, {std::byte{0x0B}, {mnemonic::ANC, 2, address_mode::IMME}},
  {std::byte{0x2B}, {mnemonic::ANC, 2, address_mode::IMME}}, {std::byte{0x8B}, {mnemonic::ANE, 2, address_mode::IMME}},
  {std::byte{0x6B}, {mnemonic::ARR, 2, address_mode::IMME}}, {std::byte{0xC7}, {mnemonic::DCP, 5, address_mode::ZPAG}},
  {std::byte{0xD7}, {mnemonic::DCP, 6, address_mode::ZPAX}}, {std::byte{0xCF}, {mnemonic::DCP, 6, address_mode::ABSL}},
  {std::byte{0xDF}, {mnemonic::DCP, 7, address_mode::ABSX}}, {std::byte{0xDB}, {mnemonic::DCP, 7, address_mode::ABSY}},
  {std::byte{0xC3}, {mnemonic::DCP, 8, address_mode::INDX}}, {std::byte{0xD3}, {mnemonic::DCP, 8, address_mode::INDY}},
  {std::byte{0xE7}, {mnemonic::ISC, 5, address_mode::ZPAG}}, {std::byte{0xF7}, {mnemonic::ISC, 6, address_mode::ZPAX}},
  {std::byte{0xEF}, {mnemonic::ISC, 6, address_mode::ABSL}}, {std::byte{0xFF}, {mnemonic::ISC, 7, address_mode::ABSX}},
  {std::byte{0xFB}, {mnemonic::ISC, 7, address_mode::ABSY}}, {std::byte{0xE3}, {mnemonic::ISC, 8, address_mode::INDX}},
  {std::byte{0xF3}, {mnemonic::ISC, 8, address_mode::INDY}}, {std::byte{0xBB}, {mnemonic::LAS, 4, address_mode::ABSY}},
  {std::byte{0xA7}, {mnemonic::LAX, 3, address_mode::ZPAG}}, {std::byte{0xB7}, {mnemonic::LAX, 4, address_mode::ZPAY}},
  {std::byte{0xAF}, {mnemonic::LAX, 4, address_mode::ABSL}}, {std::byte{0xBF}, {mnemonic::LAX, 4, address_mode::ABSY}},
  {std::byte{0xA3}, {mnemonic::LAX, 6, address_mode::INDX}}, {std::byte{0xB3}, {mnemonic::LAX, 5, address_mode::INDY}},
  {std::byte{0xAB}, {mnemonic::LXA, 2, address_mode::IMME}}, {std::byte{0x27}, {mnemonic::RLA, 5, address_mode::ZPAG}},
  {std::byte{0x37}, {mnemonic::RLA, 6, address_mode::ZPAX}}, {std::byte{0x2F}, {mnemonic::RLA, 6, address_mode::ABSL}},
  {std::byte{0x3F}, {mnemonic::RLA, 7, address_mode::ABSX}}, {std::byte{0x3B}, {mnemonic::RLA, 7, address_mode::ABSY}},
  {std::byte{0x23}, {mnemonic::RLA, 8, address_mode::INDX}}, {std::byte{0x33}, {mnemonic::RLA, 8, address_mode::INDY}},
  {std::byte{0x67}, {mnemonic::RRA, 5, address_mode::ZPAG}}, {std::byte{0x77}, {mnemonic::RRA, 6, address_mode::ZPAX}},
  {std::byte{0x6F}, {mnemonic::RRA, 6, address_mode::ABSL}}, {std::byte{0x7F}, {mnemonic::RRA, 7, address_mode::ABSX}},
  {std::byte{0x7B}, {mnemonic::RRA, 7, address_mode::ABSY}}, {std::byte{0x63}, {mnemonic::RRA, 8, address_mode::INDX}},
  {std::byte{0x73}, {mnemonic::RRA, 8, address_mode::INDY}}, {std::byte{0x87}, {mnemonic::SAX, 3, address_mode::ZPAG}},
  {std::byte{0x97}, {mnemonic::SAX, 4, address_mode::ZPAY}}, {std::byte{0x8F}, {mnemonic::SAX, 4, address_mode::ABSL}},
  {std::byte{0x83}, {mnemonic::SAX, 6, address_mode::INDX}}, {std::byte{0xCB}, {mnemonic::SBX, 2, address_mode::IMME}},
  {std::byte{0x9F}, {mnemonic::SHA, 5, address_mode::ABSY}}, {std::byte{0x93}, {mnemonic::SHA, 6, address_mode::INDY}},
  {std::byte{0x9E}, {mnemonic::SHX, 5, address_mode::ABSY}}, {std::byte{0x9C}, {mnemonic::SHY, 5, address_mode::ABSX}},
  {std::byte{0x07}, {mnemonic::SLO, 5, address_mode::ZPAG}}, {std::byte{0x17}, {mnemonic::SLO, 6, address_mode::ZPAX}},
  {std::byte{0x0F}, {mnemonic::SLO, 6, address_mode::ABSL}}, {std::byte{0x1F}, {mnemonic::SLO, 7, address_mode::ABSX}},
  {std::byte{0x1B}, {mnemonic::SLO, 7, address_mode::ABSY}}, {std::byte{0x03}, {mnemonic::SLO, 8, address_mode::INDX}},
  {std::byte{0x13}, {mnemonic::SLO, 8, address_mode::INDY}}, {std::byte{0x47}, {mnemonic::SRE, 5, address_mode::ZPAG}},
  {std::byte{0x57}, {mnemonic::SRE, 6, address_mode::ZPAX}}, {std::byte{0x4F}, {mnemonic::SRE, 6, address_mode::ABSL}},
  {std::byte{0x5F}, {mnemonic::SRE, 7, address_mode::ABSX}}, {std::byte{0x5B}, {mnemonic::SRE, 7, address_mode::ABSY}},
  {std::byte{0x43}, {mnemonic::SRE, 8, address_mode::INDX}}, {std::byte{0x53}, {mnemonic::SRE, 8, address_mode::INDY}},
  {std::byte{0x9B}, {mnemonic::TAS, 5, address_mode::ABSY}},
};
}; // namespace

namespace erelic {
auto operator<<(std::ostream &os, const mnemonic &m) -> std::ostream & {
  switch (m) {
  case mnemonic::ADC: os << "ADC";
  case mnemonic::ALR: os << "ALR";
  case mnemonic::ANC: os << "ANC";
  case mnemonic::AND: os << "AND";
  case mnemonic::ANE: os << "ANE";
  case mnemonic::ARR: os << "ARR";
  case mnemonic::ASL: os << "ASL";
  case mnemonic::BCC: os << "BCC";
  case mnemonic::BCS: os << "BCS";
  case mnemonic::BEQ: os << "BEQ";
  case mnemonic::BIT: os << "BIT";
  case mnemonic::BMI: os << "BMI";
  case mnemonic::BNE: os << "BNE";
  case mnemonic::BPL: os << "BPL";
  case mnemonic::BRK: os << "BRK";
  case mnemonic::BVC: os << "BVC";
  case mnemonic::BVS: os << "BVS";
  case mnemonic::CLC: os << "CLC";
  case mnemonic::CLD: os << "CLD";
  case mnemonic::CLI: os << "CLI";
  case mnemonic::CLV: os << "CLV";
  case mnemonic::CMP: os << "CMP";
  case mnemonic::CPX: os << "CPX";
  case mnemonic::CPY: os << "CPY";
  case mnemonic::DCP: os << "DCP";
  case mnemonic::DEC: os << "DEC";
  case mnemonic::DEX: os << "DEX";
  case mnemonic::DEY: os << "DEY";
  case mnemonic::EOR: os << "EOR";
  case mnemonic::INC: os << "INC";
  case mnemonic::INX: os << "INX";
  case mnemonic::INY: os << "INY";
  case mnemonic::ISC: os << "ISC";
  case mnemonic::JAM: os << "JAM";
  case mnemonic::JMP: os << "JMP";
  case mnemonic::JSR: os << "JSR";
  case mnemonic::LAS: os << "LAS";
  case mnemonic::LAX: os << "LAX";
  case mnemonic::LDA: os << "LDA";
  case mnemonic::LDX: os << "LDX";
  case mnemonic::LDY: os << "LDY";
  case mnemonic::LSR: os << "LSR";
  case mnemonic::LXA: os << "LXA";
  case mnemonic::NOP: os << "NOP";
  case mnemonic::ORA: os << "ORA";
  case mnemonic::PHA: os << "PHA";
  case mnemonic::PHP: os << "PHP";
  case mnemonic::PLA: os << "PLA";
  case mnemonic::PLP: os << "PLP";
  case mnemonic::RLA: os << "RLA";
  case mnemonic::ROL: os << "ROL";
  case mnemonic::ROR: os << "ROR";
  case mnemonic::RRA: os << "RRA";
  case mnemonic::RTI: os << "RTI";
  case mnemonic::RTS: os << "RTS";
  case mnemonic::SAX: os << "SAX";
  case mnemonic::SBC: os << "SBC";
  case mnemonic::SBX: os << "SBX";
  case mnemonic::SEC: os << "SEC";
  case mnemonic::SED: os << "SED";
  case mnemonic::SEI: os << "SEI";
  case mnemonic::SHA: os << "SHA";
  case mnemonic::SHX: os << "SHX";
  case mnemonic::SHY: os << "SHY";
  case mnemonic::SLO: os << "SLO";
  case mnemonic::SRE: os << "SRE";
  case mnemonic::STA: os << "STA";
  case mnemonic::STX: os << "STX";
  case mnemonic::STY: os << "STY";
  case mnemonic::TAS: os << "TAS";
  case mnemonic::TAX: os << "TAX";
  case mnemonic::TAY: os << "TAY";
  case mnemonic::TSX: os << "TSX";
  case mnemonic::TXA: os << "TXA";
  case mnemonic::TXS: os << "TXS";
  case mnemonic::TYA: os << "TYA";
  }
  return os;
}

auto operator<<(std::ostream &os, const address_mode &m) -> std::ostream & {
  switch (m) {
  case address_mode::ABSL: os << "ABSL";
  case address_mode::ABSX: os << "ABSX";
  case address_mode::ABSY: os << "ABSY";
  case address_mode::ACCU: os << "ACCU";
  case address_mode::IMME: os << "IMME";
  case address_mode::IMPL: os << "IMPL";
  case address_mode::INDR: os << "INDR";
  case address_mode::INDX: os << "INDX";
  case address_mode::INDY: os << "INDY";
  case address_mode::RELA: os << "RELA";
  case address_mode::ZPAG: os << "ZPAG";
  case address_mode::ZPAX: os << "ZPAX";
  case address_mode::ZPAY: os << "ZPAY";
  }
  return os;
}

auto operator<<(std::ostream &os, const instruction_set &s) -> std::ostream & {
  switch (s) {
  case instruction_set::STND: os << "STND";
  case instruction_set::NMOS: os << "NMOS";
  }
  return os;
}

auto instruction::operator<<(std::ostream &os) const -> std::ostream & {
  os << op << '(';
  os << std::hex << std::setw(2) << std::to_integer<std::uint8_t>(opcode) << ", mem=";
  os << mode << ", len";
  os << length << ", cycl=";
  os << cycles << ", ";
  os << set << ")";
  return os;
}

auto as_instruction(std::byte byte) -> instruction {
  auto [op, cycles, mode] = instructions_info[byte];
  return {
    .opcode = byte,
    .op = op,
    .mode = mode,
    .length = instruction_length(mode),
    .cycles = cycles,
    .set = which_instruction_set(op),
  };
}

auto cycles_with_penalty(const instruction &info, address_boundary page_relation) -> size_t {
  auto is_page_crossed = page_relation == address_boundary::CROSSED;
  auto is_mode_penalty =
    info.mode == address_mode::ABSX || info.mode == address_mode::ABSY || info.mode == address_mode::INDY;

  switch (info.op) {
  case mnemonic::BCC: [[fallthrough]];
  case mnemonic::BCS: [[fallthrough]];
  case mnemonic::BEQ: [[fallthrough]];
  case mnemonic::BMI: [[fallthrough]];
  case mnemonic::BNE: [[fallthrough]];
  case mnemonic::BPL: [[fallthrough]];
  case mnemonic::BVC: [[fallthrough]];
  case mnemonic::BVS: return info.cycles + (is_page_crossed ? 1 : 0);
  case mnemonic::ADC: [[fallthrough]];
  case mnemonic::AND: [[fallthrough]];
  case mnemonic::CMP: [[fallthrough]];
  case mnemonic::EOR: [[fallthrough]];
  case mnemonic::LAS: [[fallthrough]];
  case mnemonic::LAX: [[fallthrough]];
  case mnemonic::LDA: [[fallthrough]];
  case mnemonic::LDX: [[fallthrough]];
  case mnemonic::LDY: [[fallthrough]];
  case mnemonic::ORA: [[fallthrough]];
  case mnemonic::SBC: return info.cycles + (is_page_crossed && is_mode_penalty ? 2 : 0);
  default: return info.cycles;
  }
}
}; // namespace erelic
