#pragma once
#include <cstdint>
namespace ibmlegacy::devices {
enum class CCWCommand : std::uint8_t { NoOp=0x03, Read=0x02, Write=0x01, Sense=0x04, Control=0x08 };
struct CCW { CCWCommand command{CCWCommand::NoOp}; std::uint8_t flags{}; std::uint16_t count{}; std::uint32_t data_address{}; std::uint32_t chain_address{}; };
struct DeviceStatus { std::uint8_t unit_status{}; std::uint8_t channel_status{}; bool busy{}; bool sense_available{}; };
}
