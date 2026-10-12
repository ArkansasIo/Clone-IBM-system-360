#pragma once
#include <cstdint>
#include <string>
namespace ibmlegacy::cpu {
enum class StepState { Executed, Halted, IllegalInstruction, MemoryFault };
struct StepResult { StepState state{StepState::Executed}; std::uint8_t opcode{0}; std::string message; };
}