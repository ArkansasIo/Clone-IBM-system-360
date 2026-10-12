#pragma once
#include <cstdint>
namespace ibmlegacy::machines {
// Simplified educational PSW model; bit layout is not a complete hardware implementation.
struct System360PSW {
 std::uint32_t instruction_address{0};
 std::uint8_t condition_code{0};
 bool problem_state{true};
 bool interrupts_enabled{false};
 void set_condition_code(std::uint8_t value) noexcept { condition_code=static_cast<std::uint8_t>(value&0x03U); }
};
}