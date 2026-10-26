#pragma once
#include "ibmlegacy/cpu/system360_opcodes.hpp"
#include <cstdint>
namespace ibmlegacy::cpu {
struct DecodedInstruction {
 const OpcodeInfo* info{nullptr};
 std::uint8_t first{0}; std::uint8_t second{0}; std::uint8_t third{0}; std::uint8_t fourth{0};
 std::uint8_t r1{0}; std::uint8_t r2{0}; std::uint8_t x2{0}; std::uint8_t b2{0}; std::uint16_t displacement{0};
};
[[nodiscard]] DecodedInstruction decode_rr(std::uint8_t first,std::uint8_t second) noexcept;
[[nodiscard]] DecodedInstruction decode_rx(std::uint8_t first,std::uint8_t second,std::uint8_t third,std::uint8_t fourth) noexcept;
}