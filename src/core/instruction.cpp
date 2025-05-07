//
// Created by Kyrylo Rud on 05.05.2025.
//

#include "instruction.hpp"

#include <array>
#include <iomanip>
#include <tuple>

#include "utility.hpp"

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

using instr_info = std::tuple<mnemonic, address_mode, size_t /* cycles */>;
using lookup_table = std::array<instr_info, 256>;

constexpr auto make_opcode_lookup_table() -> lookup_table {
  auto table = lookup_table{};
  table[0x69] = {mnemonic::ADC, address_mode::IMME, 2};
  table[0x65] = {mnemonic::ADC, address_mode::ZPAG, 3};
  table[0x75] = {mnemonic::ADC, address_mode::ZPAX, 4};
  table[0x6D] = {mnemonic::ADC, address_mode::ABSL, 4};
  table[0x7D] = {mnemonic::ADC, address_mode::ABSX, 4};
  table[0x79] = {mnemonic::ADC, address_mode::ABSY, 4};
  table[0x61] = {mnemonic::ADC, address_mode::INDX, 6};
  table[0x71] = {mnemonic::ADC, address_mode::INDY, 5};
  table[0x29] = {mnemonic::AND, address_mode::IMME, 2};
  table[0x25] = {mnemonic::AND, address_mode::ZPAG, 3};
  table[0x35] = {mnemonic::AND, address_mode::ZPAX, 4};
  table[0x2D] = {mnemonic::AND, address_mode::ABSL, 4};
  table[0x3D] = {mnemonic::AND, address_mode::ABSX, 4};
  table[0x39] = {mnemonic::AND, address_mode::ABSY, 4};
  table[0x21] = {mnemonic::AND, address_mode::INDX, 6};
  table[0x31] = {mnemonic::AND, address_mode::INDY, 5};
  table[0x0A] = {mnemonic::ASL, address_mode::ACCU, 2};
  table[0x06] = {mnemonic::ASL, address_mode::ZPAG, 5};
  table[0x16] = {mnemonic::ASL, address_mode::ZPAX, 6};
  table[0x0E] = {mnemonic::ASL, address_mode::ABSL, 6};
  table[0x1E] = {mnemonic::ASL, address_mode::ABSX, 7};
  table[0x90] = {mnemonic::BCC, address_mode::RELA, 2};
  table[0xB0] = {mnemonic::BCS, address_mode::RELA, 2};
  table[0x1A] = {mnemonic::NOP, address_mode::IMPL, 2};
  table[0x3A] = {mnemonic::NOP, address_mode::IMPL, 2};
  table[0x5A] = {mnemonic::NOP, address_mode::IMPL, 2};
  table[0x7A] = {mnemonic::NOP, address_mode::IMPL, 2};
  table[0xDA] = {mnemonic::NOP, address_mode::IMPL, 2};
  table[0xFA] = {mnemonic::NOP, address_mode::IMPL, 2};
  table[0x80] = {mnemonic::NOP, address_mode::IMME, 2};
  table[0x82] = {mnemonic::NOP, address_mode::IMME, 2};
  table[0x89] = {mnemonic::NOP, address_mode::IMME, 2};
  table[0xC2] = {mnemonic::NOP, address_mode::IMME, 2};
  table[0xE2] = {mnemonic::NOP, address_mode::IMME, 2};
  table[0x04] = {mnemonic::NOP, address_mode::ZPAG, 3};
  table[0x44] = {mnemonic::NOP, address_mode::ZPAG, 3};
  table[0x64] = {mnemonic::NOP, address_mode::ZPAG, 3};
  table[0x14] = {mnemonic::NOP, address_mode::ZPAX, 4};
  table[0x34] = {mnemonic::NOP, address_mode::ZPAX, 4};
  table[0x54] = {mnemonic::NOP, address_mode::ZPAX, 4};
  table[0x74] = {mnemonic::NOP, address_mode::ZPAX, 4};
  table[0xD4] = {mnemonic::NOP, address_mode::ZPAX, 4};
  table[0xF4] = {mnemonic::NOP, address_mode::ZPAX, 4};
  table[0x0C] = {mnemonic::NOP, address_mode::ABSL, 4};
  table[0x1C] = {mnemonic::NOP, address_mode::ABSX, 4};
  table[0x3C] = {mnemonic::NOP, address_mode::ABSX, 4};
  table[0x5C] = {mnemonic::NOP, address_mode::ABSX, 4};
  table[0x7C] = {mnemonic::NOP, address_mode::ABSX, 4};
  table[0xDC] = {mnemonic::NOP, address_mode::ABSX, 4};
  table[0xFC] = {mnemonic::NOP, address_mode::ABSX, 4};
  table[0x02] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0x12] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0x22] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0x32] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0x42] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0x52] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0x62] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0x72] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0x92] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0xB2] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0xD2] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0xF2] = {mnemonic::JAM, address_mode::ACCU, 0};
  table[0xF0] = {mnemonic::BEQ, address_mode::RELA, 2};
  table[0x24] = {mnemonic::BIT, address_mode::ZPAG, 3};
  table[0x2C] = {mnemonic::BIT, address_mode::ABSL, 4};
  table[0x30] = {mnemonic::BMI, address_mode::RELA, 2};
  table[0xD0] = {mnemonic::BNE, address_mode::RELA, 2};
  table[0x10] = {mnemonic::BPL, address_mode::RELA, 2};
  table[0x00] = {mnemonic::BRK, address_mode::IMPL, 7};
  table[0x50] = {mnemonic::BVC, address_mode::RELA, 2};
  table[0x70] = {mnemonic::BVS, address_mode::RELA, 2};
  table[0x18] = {mnemonic::CLC, address_mode::IMPL, 2};
  table[0xD8] = {mnemonic::CLD, address_mode::IMPL, 2};
  table[0x58] = {mnemonic::CLI, address_mode::IMPL, 2};
  table[0xB8] = {mnemonic::CLV, address_mode::IMPL, 2};
  table[0xC9] = {mnemonic::CMP, address_mode::IMME, 2};
  table[0xC5] = {mnemonic::CMP, address_mode::ZPAG, 3};
  table[0xD5] = {mnemonic::CMP, address_mode::ZPAX, 4};
  table[0xCD] = {mnemonic::CMP, address_mode::ABSL, 4};
  table[0xDD] = {mnemonic::CMP, address_mode::ABSX, 4};
  table[0xD9] = {mnemonic::CMP, address_mode::ABSY, 4};
  table[0xC1] = {mnemonic::CMP, address_mode::INDX, 6};
  table[0xD1] = {mnemonic::CMP, address_mode::INDY, 5};
  table[0xE0] = {mnemonic::CPX, address_mode::IMME, 2};
  table[0xE4] = {mnemonic::CPX, address_mode::ZPAG, 3};
  table[0xEC] = {mnemonic::CPX, address_mode::ABSL, 4};
  table[0xC0] = {mnemonic::CPY, address_mode::IMME, 2};
  table[0xC4] = {mnemonic::CPY, address_mode::ZPAG, 3};
  table[0xCC] = {mnemonic::CPY, address_mode::ABSL, 4};
  table[0xC6] = {mnemonic::DEC, address_mode::ZPAG, 5};
  table[0xD6] = {mnemonic::DEC, address_mode::ZPAX, 6};
  table[0xCE] = {mnemonic::DEC, address_mode::ABSL, 6};
  table[0xDE] = {mnemonic::DEC, address_mode::ABSX, 7};
  table[0xCA] = {mnemonic::DEX, address_mode::IMPL, 2};
  table[0x88] = {mnemonic::DEY, address_mode::IMPL, 2};
  table[0x49] = {mnemonic::EOR, address_mode::IMME, 2};
  table[0x45] = {mnemonic::EOR, address_mode::ZPAG, 3};
  table[0x55] = {mnemonic::EOR, address_mode::ZPAX, 4};
  table[0x4D] = {mnemonic::EOR, address_mode::ABSL, 4};
  table[0x5D] = {mnemonic::EOR, address_mode::ABSX, 4};
  table[0x59] = {mnemonic::EOR, address_mode::ABSY, 4};
  table[0x41] = {mnemonic::EOR, address_mode::INDX, 6};
  table[0x51] = {mnemonic::EOR, address_mode::INDY, 5};
  table[0xE6] = {mnemonic::INC, address_mode::ZPAG, 5};
  table[0xF6] = {mnemonic::INC, address_mode::ZPAX, 6};
  table[0xEE] = {mnemonic::INC, address_mode::ABSL, 6};
  table[0xFE] = {mnemonic::INC, address_mode::ABSX, 7};
  table[0xE8] = {mnemonic::INX, address_mode::IMPL, 2};
  table[0xC8] = {mnemonic::INY, address_mode::IMPL, 2};
  table[0x4C] = {mnemonic::JMP, address_mode::ABSL, 3};
  table[0x6C] = {mnemonic::JMP, address_mode::INDR, 5};
  table[0x20] = {mnemonic::JSR, address_mode::ABSL, 6};
  table[0xA9] = {mnemonic::LDA, address_mode::IMME, 2};
  table[0xA5] = {mnemonic::LDA, address_mode::ZPAG, 3};
  table[0xB5] = {mnemonic::LDA, address_mode::ZPAX, 4};
  table[0xAD] = {mnemonic::LDA, address_mode::ABSL, 4};
  table[0xBD] = {mnemonic::LDA, address_mode::ABSX, 4};
  table[0xB9] = {mnemonic::LDA, address_mode::ABSY, 4};
  table[0xA1] = {mnemonic::LDA, address_mode::INDX, 6};
  table[0xB1] = {mnemonic::LDA, address_mode::INDY, 5};
  table[0xA2] = {mnemonic::LDX, address_mode::IMME, 2};
  table[0xA6] = {mnemonic::LDX, address_mode::ZPAG, 3};
  table[0xB6] = {mnemonic::LDX, address_mode::ZPAY, 4};
  table[0xAE] = {mnemonic::LDX, address_mode::ABSL, 4};
  table[0xBE] = {mnemonic::LDX, address_mode::ABSY, 4};
  table[0xA0] = {mnemonic::LDY, address_mode::IMME, 2};
  table[0xA4] = {mnemonic::LDY, address_mode::ZPAG, 3};
  table[0xB4] = {mnemonic::LDY, address_mode::ZPAX, 4};
  table[0xAC] = {mnemonic::LDY, address_mode::ABSL, 4};
  table[0xBC] = {mnemonic::LDY, address_mode::ABSX, 4};
  table[0x4A] = {mnemonic::LSR, address_mode::ACCU, 2};
  table[0x46] = {mnemonic::LSR, address_mode::ZPAG, 5};
  table[0x56] = {mnemonic::LSR, address_mode::ZPAX, 6};
  table[0x4E] = {mnemonic::LSR, address_mode::ABSL, 6};
  table[0x5E] = {mnemonic::LSR, address_mode::ABSX, 7};
  table[0xEA] = {mnemonic::NOP, address_mode::IMPL, 2};
  table[0x09] = {mnemonic::ORA, address_mode::IMME, 2};
  table[0x05] = {mnemonic::ORA, address_mode::ZPAG, 3};
  table[0x15] = {mnemonic::ORA, address_mode::ZPAX, 4};
  table[0x0D] = {mnemonic::ORA, address_mode::ABSL, 4};
  table[0x1D] = {mnemonic::ORA, address_mode::ABSX, 4};
  table[0x19] = {mnemonic::ORA, address_mode::ABSY, 4};
  table[0x01] = {mnemonic::ORA, address_mode::INDX, 6};
  table[0x11] = {mnemonic::ORA, address_mode::INDY, 5};
  table[0x48] = {mnemonic::PHA, address_mode::IMPL, 3};
  table[0x08] = {mnemonic::PHP, address_mode::IMPL, 3};
  table[0x68] = {mnemonic::PLA, address_mode::IMPL, 4};
  table[0x28] = {mnemonic::PLP, address_mode::IMPL, 4};
  table[0x2A] = {mnemonic::ROL, address_mode::ACCU, 2};
  table[0x26] = {mnemonic::ROL, address_mode::ZPAG, 5};
  table[0x36] = {mnemonic::ROL, address_mode::ZPAX, 6};
  table[0x2E] = {mnemonic::ROL, address_mode::ABSL, 6};
  table[0x3E] = {mnemonic::ROL, address_mode::ABSX, 7};
  table[0x6A] = {mnemonic::ROR, address_mode::ACCU, 2};
  table[0x66] = {mnemonic::ROR, address_mode::ZPAG, 5};
  table[0x76] = {mnemonic::ROR, address_mode::ZPAX, 6};
  table[0x6E] = {mnemonic::ROR, address_mode::ABSL, 6};
  table[0x7E] = {mnemonic::ROR, address_mode::ABSX, 7};
  table[0x40] = {mnemonic::RTI, address_mode::IMPL, 6};
  table[0x60] = {mnemonic::RTS, address_mode::IMPL, 6};
  table[0xE9] = {mnemonic::SBC, address_mode::IMME, 2};
  table[0xE5] = {mnemonic::SBC, address_mode::ZPAG, 3};
  table[0xF5] = {mnemonic::SBC, address_mode::ZPAX, 4};
  table[0xED] = {mnemonic::SBC, address_mode::ABSL, 4};
  table[0xFD] = {mnemonic::SBC, address_mode::ABSX, 4};
  table[0xF9] = {mnemonic::SBC, address_mode::ABSY, 4};
  table[0xE1] = {mnemonic::SBC, address_mode::INDX, 6};
  table[0xEB] = {mnemonic::SBC, address_mode::IMME, 2};
  table[0xF1] = {mnemonic::SBC, address_mode::INDY, 5};
  table[0x38] = {mnemonic::SEC, address_mode::IMPL, 2};
  table[0xF8] = {mnemonic::SED, address_mode::IMPL, 2};
  table[0x78] = {mnemonic::SEI, address_mode::IMPL, 2};
  table[0x85] = {mnemonic::STA, address_mode::ZPAG, 3};
  table[0x95] = {mnemonic::STA, address_mode::ZPAX, 4};
  table[0x8D] = {mnemonic::STA, address_mode::ABSL, 4};
  table[0x9D] = {mnemonic::STA, address_mode::ABSX, 5};
  table[0x99] = {mnemonic::STA, address_mode::ABSY, 5};
  table[0x81] = {mnemonic::STA, address_mode::INDX, 6};
  table[0x91] = {mnemonic::STA, address_mode::INDY, 6};
  table[0x86] = {mnemonic::STX, address_mode::ZPAG, 3};
  table[0x96] = {mnemonic::STX, address_mode::ZPAY, 4};
  table[0x8E] = {mnemonic::STX, address_mode::ABSL, 4};
  table[0x84] = {mnemonic::STY, address_mode::ZPAG, 3};
  table[0x94] = {mnemonic::STY, address_mode::ZPAX, 4};
  table[0x8C] = {mnemonic::STY, address_mode::ABSL, 4};
  table[0xAA] = {mnemonic::TAX, address_mode::IMPL, 2};
  table[0xA8] = {mnemonic::TAY, address_mode::IMPL, 2};
  table[0xBA] = {mnemonic::TSX, address_mode::IMPL, 2};
  table[0x8A] = {mnemonic::TXA, address_mode::IMPL, 2};
  table[0x9A] = {mnemonic::TXS, address_mode::IMPL, 2};
  table[0x98] = {mnemonic::TYA, address_mode::IMPL, 2};
  table[0x4B] = {mnemonic::ALR, address_mode::IMME, 2};
  table[0x0B] = {mnemonic::ANC, address_mode::IMME, 2};
  table[0x2B] = {mnemonic::ANC, address_mode::IMME, 2};
  table[0x8B] = {mnemonic::ANE, address_mode::IMME, 2};
  table[0x6B] = {mnemonic::ARR, address_mode::IMME, 2};
  table[0xC7] = {mnemonic::DCP, address_mode::ZPAG, 5};
  table[0xD7] = {mnemonic::DCP, address_mode::ZPAX, 6};
  table[0xCF] = {mnemonic::DCP, address_mode::ABSL, 6};
  table[0xDF] = {mnemonic::DCP, address_mode::ABSX, 7};
  table[0xDB] = {mnemonic::DCP, address_mode::ABSY, 7};
  table[0xC3] = {mnemonic::DCP, address_mode::INDX, 8};
  table[0xD3] = {mnemonic::DCP, address_mode::INDY, 8};
  table[0xE7] = {mnemonic::ISC, address_mode::ZPAG, 5};
  table[0xF7] = {mnemonic::ISC, address_mode::ZPAX, 6};
  table[0xEF] = {mnemonic::ISC, address_mode::ABSL, 6};
  table[0xFF] = {mnemonic::ISC, address_mode::ABSX, 7};
  table[0xFB] = {mnemonic::ISC, address_mode::ABSY, 7};
  table[0xE3] = {mnemonic::ISC, address_mode::INDX, 8};
  table[0xF3] = {mnemonic::ISC, address_mode::INDY, 8};
  table[0xBB] = {mnemonic::LAS, address_mode::ABSY, 4};
  table[0xA7] = {mnemonic::LAX, address_mode::ZPAG, 3};
  table[0xB7] = {mnemonic::LAX, address_mode::ZPAY, 4};
  table[0xAF] = {mnemonic::LAX, address_mode::ABSL, 4};
  table[0xBF] = {mnemonic::LAX, address_mode::ABSY, 4};
  table[0xA3] = {mnemonic::LAX, address_mode::INDX, 6};
  table[0xB3] = {mnemonic::LAX, address_mode::INDY, 5};
  table[0xAB] = {mnemonic::LXA, address_mode::IMME, 2};
  table[0x27] = {mnemonic::RLA, address_mode::ZPAG, 5};
  table[0x37] = {mnemonic::RLA, address_mode::ZPAX, 6};
  table[0x2F] = {mnemonic::RLA, address_mode::ABSL, 6};
  table[0x3F] = {mnemonic::RLA, address_mode::ABSX, 7};
  table[0x3B] = {mnemonic::RLA, address_mode::ABSY, 7};
  table[0x23] = {mnemonic::RLA, address_mode::INDX, 8};
  table[0x33] = {mnemonic::RLA, address_mode::INDY, 8};
  table[0x67] = {mnemonic::RRA, address_mode::ZPAG, 5};
  table[0x77] = {mnemonic::RRA, address_mode::ZPAX, 6};
  table[0x6F] = {mnemonic::RRA, address_mode::ABSL, 6};
  table[0x7F] = {mnemonic::RRA, address_mode::ABSX, 7};
  table[0x7B] = {mnemonic::RRA, address_mode::ABSY, 7};
  table[0x63] = {mnemonic::RRA, address_mode::INDX, 8};
  table[0x73] = {mnemonic::RRA, address_mode::INDY, 8};
  table[0x87] = {mnemonic::SAX, address_mode::ZPAG, 3};
  table[0x97] = {mnemonic::SAX, address_mode::ZPAY, 4};
  table[0x8F] = {mnemonic::SAX, address_mode::ABSL, 4};
  table[0x83] = {mnemonic::SAX, address_mode::INDX, 6};
  table[0xCB] = {mnemonic::SBX, address_mode::IMME, 2};
  table[0x9F] = {mnemonic::SHA, address_mode::ABSY, 5};
  table[0x93] = {mnemonic::SHA, address_mode::INDY, 6};
  table[0x9E] = {mnemonic::SHX, address_mode::ABSY, 5};
  table[0x9C] = {mnemonic::SHY, address_mode::ABSX, 5};
  table[0x07] = {mnemonic::SLO, address_mode::ZPAG, 5};
  table[0x17] = {mnemonic::SLO, address_mode::ZPAX, 6};
  table[0x0F] = {mnemonic::SLO, address_mode::ABSL, 6};
  table[0x1F] = {mnemonic::SLO, address_mode::ABSX, 7};
  table[0x1B] = {mnemonic::SLO, address_mode::ABSY, 7};
  table[0x03] = {mnemonic::SLO, address_mode::INDX, 8};
  table[0x13] = {mnemonic::SLO, address_mode::INDY, 8};
  table[0x47] = {mnemonic::SRE, address_mode::ZPAG, 5};
  table[0x57] = {mnemonic::SRE, address_mode::ZPAX, 6};
  table[0x4F] = {mnemonic::SRE, address_mode::ABSL, 6};
  table[0x5F] = {mnemonic::SRE, address_mode::ABSX, 7};
  table[0x5B] = {mnemonic::SRE, address_mode::ABSY, 7};
  table[0x43] = {mnemonic::SRE, address_mode::INDX, 8};
  table[0x53] = {mnemonic::SRE, address_mode::INDY, 8};
  table[0x9B] = {mnemonic::TAS, address_mode::ABSY, 5};
  return table;
}

constexpr auto opcode_lookup_table = make_opcode_lookup_table();
}; // namespace

namespace erelic {
auto operator<<(std::ostream &os, const mnemonic &m) -> std::ostream & {
  switch (m) {
  case mnemonic::ADC: os << "ADC"; break;
  case mnemonic::ALR: os << "ALR"; break;
  case mnemonic::ANC: os << "ANC"; break;
  case mnemonic::AND: os << "AND"; break;
  case mnemonic::ANE: os << "ANE"; break;
  case mnemonic::ARR: os << "ARR"; break;
  case mnemonic::ASL: os << "ASL"; break;
  case mnemonic::BCC: os << "BCC"; break;
  case mnemonic::BCS: os << "BCS"; break;
  case mnemonic::BEQ: os << "BEQ"; break;
  case mnemonic::BIT: os << "BIT"; break;
  case mnemonic::BMI: os << "BMI"; break;
  case mnemonic::BNE: os << "BNE"; break;
  case mnemonic::BPL: os << "BPL"; break;
  case mnemonic::BRK: os << "BRK"; break;
  case mnemonic::BVC: os << "BVC"; break;
  case mnemonic::BVS: os << "BVS"; break;
  case mnemonic::CLC: os << "CLC"; break;
  case mnemonic::CLD: os << "CLD"; break;
  case mnemonic::CLI: os << "CLI"; break;
  case mnemonic::CLV: os << "CLV"; break;
  case mnemonic::CMP: os << "CMP"; break;
  case mnemonic::CPX: os << "CPX"; break;
  case mnemonic::CPY: os << "CPY"; break;
  case mnemonic::DCP: os << "DCP"; break;
  case mnemonic::DEC: os << "DEC"; break;
  case mnemonic::DEX: os << "DEX"; break;
  case mnemonic::DEY: os << "DEY"; break;
  case mnemonic::EOR: os << "EOR"; break;
  case mnemonic::INC: os << "INC"; break;
  case mnemonic::INX: os << "INX"; break;
  case mnemonic::INY: os << "INY"; break;
  case mnemonic::ISC: os << "ISC"; break;
  case mnemonic::JAM: os << "JAM"; break;
  case mnemonic::JMP: os << "JMP"; break;
  case mnemonic::JSR: os << "JSR"; break;
  case mnemonic::LAS: os << "LAS"; break;
  case mnemonic::LAX: os << "LAX"; break;
  case mnemonic::LDA: os << "LDA"; break;
  case mnemonic::LDX: os << "LDX"; break;
  case mnemonic::LDY: os << "LDY"; break;
  case mnemonic::LSR: os << "LSR"; break;
  case mnemonic::LXA: os << "LXA"; break;
  case mnemonic::NOP: os << "NOP"; break;
  case mnemonic::ORA: os << "ORA"; break;
  case mnemonic::PHA: os << "PHA"; break;
  case mnemonic::PHP: os << "PHP"; break;
  case mnemonic::PLA: os << "PLA"; break;
  case mnemonic::PLP: os << "PLP"; break;
  case mnemonic::RLA: os << "RLA"; break;
  case mnemonic::ROL: os << "ROL"; break;
  case mnemonic::ROR: os << "ROR"; break;
  case mnemonic::RRA: os << "RRA"; break;
  case mnemonic::RTI: os << "RTI"; break;
  case mnemonic::RTS: os << "RTS"; break;
  case mnemonic::SAX: os << "SAX"; break;
  case mnemonic::SBC: os << "SBC"; break;
  case mnemonic::SBX: os << "SBX"; break;
  case mnemonic::SEC: os << "SEC"; break;
  case mnemonic::SED: os << "SED"; break;
  case mnemonic::SEI: os << "SEI"; break;
  case mnemonic::SHA: os << "SHA"; break;
  case mnemonic::SHX: os << "SHX"; break;
  case mnemonic::SHY: os << "SHY"; break;
  case mnemonic::SLO: os << "SLO"; break;
  case mnemonic::SRE: os << "SRE"; break;
  case mnemonic::STA: os << "STA"; break;
  case mnemonic::STX: os << "STX"; break;
  case mnemonic::STY: os << "STY"; break;
  case mnemonic::TAS: os << "TAS"; break;
  case mnemonic::TAX: os << "TAX"; break;
  case mnemonic::TAY: os << "TAY"; break;
  case mnemonic::TSX: os << "TSX"; break;
  case mnemonic::TXA: os << "TXA"; break;
  case mnemonic::TXS: os << "TXS"; break;
  case mnemonic::TYA: os << "TYA"; break;
  }
  return os;
}

auto operator<<(std::ostream &os, const address_mode &m) -> std::ostream & {
  switch (m) {
  case address_mode::ABSL: os << "ABSL"; break;
  case address_mode::ABSX: os << "ABSX"; break;
  case address_mode::ABSY: os << "ABSY"; break;
  case address_mode::ACCU: os << "ACCU"; break;
  case address_mode::IMME: os << "IMME"; break;
  case address_mode::IMPL: os << "IMPL"; break;
  case address_mode::INDR: os << "INDR"; break;
  case address_mode::INDX: os << "INDX"; break;
  case address_mode::INDY: os << "INDY"; break;
  case address_mode::RELA: os << "RELA"; break;
  case address_mode::ZPAG: os << "ZPAG"; break;
  case address_mode::ZPAX: os << "ZPAX"; break;
  case address_mode::ZPAY: os << "ZPAY"; break;
  }
  return os;
}

auto operator<<(std::ostream &os, const instruction_set &s) -> std::ostream & {
  switch (s) {
  case instruction_set::STND: os << "STND"; break;
  case instruction_set::NMOS: os << "NMOS"; break;
  }
  return os;
}

auto operator<<(std::ostream &os, const instruction &instruction) -> std::ostream & {
  os << instruction.op << "(opc=";
  os << instruction.opcode << ", mem=";
  os << instruction.mode << ", len=";
  os << instruction.length << ", cycl=";
  os << instruction.cycles << ", set=";
  os << instruction.set << ")";
  return os;
}

auto as_instruction(std::byte byte) -> instruction {
  auto [op, mode, cycles] = opcode_lookup_table[std::to_integer<size_t>(byte)];
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
