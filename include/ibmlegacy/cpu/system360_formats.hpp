#pragma once
#include <cstdint>
namespace ibmlegacy::cpu {
enum class InstructionFormat : std::uint8_t { RR, RX, RS, SI, SS, Unknown };
struct EffectiveAddress { std::uint32_t address{}; std::uint8_t base{}; std::uint8_t index{}; std::uint16_t displacement{}; };
struct DecodedRS { std::uint8_t opcode{}; std::uint8_t r1{}; std::uint8_t r3{}; std::uint8_t b2{}; std::uint16_t d2{}; };
struct DecodedSI { std::uint8_t opcode{}; std::uint8_t i2{}; std::uint8_t b1{}; std::uint16_t d1{}; };
struct DecodedSS { std::uint8_t opcode{}; std::uint8_t l1{}; std::uint8_t l2{}; std::uint8_t b1{}; std::uint8_t b2{}; std::uint16_t d1{}; std::uint16_t d2{}; };
}
