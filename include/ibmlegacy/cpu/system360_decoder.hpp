#pragma once
#include "ibmlegacy/cpu/system360_opcodes.hpp"
#include <array>
#include <cstdint>
namespace ibmlegacy::cpu {
struct DecodedInstruction { const OpcodeInfo* info{nullptr}; std::uint8_t first{0}; std::uint8_t second{0}; std::uint8_t r1{0}; std::uint8_t r2{0}; };
[[nodiscard]] DecodedInstruction decode_rr(std::uint8_t first,std::uint8_t second) noexcept;
}