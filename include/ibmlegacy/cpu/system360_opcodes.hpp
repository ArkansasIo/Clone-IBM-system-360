#pragma once
#include <cstdint>
#include <string_view>
namespace ibmlegacy::cpu {
struct OpcodeInfo { std::uint8_t opcode; std::string_view mnemonic; std::uint8_t length; std::string_view format; };
inline constexpr OpcodeInfo system360_subset_opcodes[] = {
 {0x05,"BALR",2,"RR"},{0x07,"BCR",2,"RR"},{0x12,"LTR",2,"RR"},{0x14,"NR",2,"RR"},{0x15,"CLR",2,"RR"},{0x16,"OR",2,"RR"},{0x17,"XR",2,"RR"},{0x18,"LR",2,"RR"},{0x19,"CR",2,"RR"},{0x1A,"AR",2,"RR"},{0x1B,"SR",2,"RR"},{0x1C,"MR",2,"RR"},{0x1D,"DR",2,"RR"},{0x1E,"ALR",2,"RR"},{0x1F,"SLR",2,"RR"},
 {0x40,"STC",4,"RX"},{0x41,"LA",4,"RX"},{0x45,"BAL",4,"RX"},{0x46,"BCT",4,"RX"},{0x47,"BC",4,"RX"},{0x48,"LH",4,"RX"},{0x49,"CH",4,"RX"},{0x4A,"AH",4,"RX"},{0x4B,"SH",4,"RX"},{0x50,"ST",4,"RX"},{0x54,"N",4,"RX"},{0x55,"CL",4,"RX"},{0x56,"O",4,"RX"},{0x57,"X",4,"RX"},{0x58,"L",4,"RX"},{0x59,"C",4,"RX"},{0x5A,"A",4,"RX"},{0x5B,"S",4,"RX"},
 {0x88,"SRL",4,"RS"},{0x89,"SLL",4,"RS"},{0x8A,"SRA",4,"RS"},{0x8B,"SLA",4,"RS"},{0x90,"STM",4,"RS"},{0x91,"TM",4,"SI"},{0x92,"MVI",4,"SI"},{0x94,"NI",4,"SI"},{0x95,"CLI",4,"SI"},{0x96,"OI",4,"SI"},{0x97,"XI",4,"SI"},{0x98,"LM",4,"RS"},
 {0xD2,"MVC",6,"SS"},{0xD5,"CLC",6,"SS"},{0xD7,"XC",6,"SS"},{0xDC,"TR",6,"SS"}
};
[[nodiscard]] constexpr const OpcodeInfo* find_system360_opcode(std::uint8_t op) noexcept { for(const auto& info:system360_subset_opcodes) if(info.opcode==op) return &info; return nullptr; }
}
