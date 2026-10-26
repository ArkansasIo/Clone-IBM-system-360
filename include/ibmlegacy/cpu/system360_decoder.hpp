#pragma once
#include "ibmlegacy/cpu/system360_formats.hpp"
#include "ibmlegacy/cpu/system360_opcodes.hpp"
#include <cstdint>
namespace ibmlegacy::cpu {
struct DecodedInstruction {
 const OpcodeInfo* info{nullptr}; InstructionFormat format{InstructionFormat::Unknown};
 std::uint8_t first{0},second{0},third{0},fourth{0};
 std::uint8_t r1{0},r2{0},r3{0},x2{0},b1{0},b2{0},i2{0},l1{0},l2{0};
 std::uint16_t d1{0},d2{0},displacement{0};
};
[[nodiscard]] DecodedInstruction decode_rr(std::uint8_t,std::uint8_t) noexcept;
[[nodiscard]] DecodedInstruction decode_rx(std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t) noexcept;
[[nodiscard]] DecodedInstruction decode_rs(std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t) noexcept;
[[nodiscard]] DecodedInstruction decode_si(std::uint8_t,std::uint8_t,std::uint8_t) noexcept;
[[nodiscard]] DecodedInstruction decode_ss(std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t) noexcept;
}
