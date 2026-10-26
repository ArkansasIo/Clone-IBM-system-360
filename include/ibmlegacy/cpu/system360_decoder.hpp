#pragma once
#include "ibmlegacy/cpu/system360_formats.hpp"
#include "ibmlegacy/cpu/system360_opcodes.hpp"
#include <cstdint>
namespace ibmlegacy::cpu {
struct DecodedInstruction { const OpcodeInfo* info{nullptr}; InstructionFormat format{InstructionFormat::Unknown}; std::uint8_t first{},second{},third{},fourth{}; std::uint8_t r1{},r2{},r3{},x2{},b1{},b2{},i2{},l1{},l2{}; std::uint16_t d1{},d2{},displacement{}; };
[[nodiscard]] DecodedInstruction decode_rr(std::uint8_t,std::uint8_t) noexcept;
[[nodiscard]] DecodedInstruction decode_rx(std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t) noexcept;
[[nodiscard]] DecodedInstruction decode_rs(std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t) noexcept;
[[nodiscard]] DecodedInstruction decode_si(std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t) noexcept;
[[nodiscard]] DecodedInstruction decode_ss(std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t,std::uint8_t) noexcept;
}
