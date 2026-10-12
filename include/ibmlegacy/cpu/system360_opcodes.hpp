#pragma once
#include <cstdint>
#include <string_view>
namespace ibmlegacy::cpu {
struct OpcodeInfo { std::uint8_t opcode; std::string_view mnemonic; std::uint8_t length; std::string_view format; };
inline constexpr OpcodeInfo system360_subset_opcodes[] = {
 {0x05,"BALR",2,"RR"},{0x07,"BCR",2,"RR"},{0x18,"LR",2,"RR"},{0x1A,"AR",2,"RR"}
};
[[nodiscard]] constexpr const OpcodeInfo* find_system360_opcode(std::uint8_t op) noexcept {
 for(const auto& info:system360_subset_opcodes) if(info.opcode==op) return &info;
 return nullptr;
}
}