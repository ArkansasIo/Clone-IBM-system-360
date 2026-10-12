#pragma once
#include "ibmlegacy/cpu/cpu_result.hpp"
#include "ibmlegacy/machines/ibm1401.hpp"
#include <cstddef>
namespace ibmlegacy::cpu {
class IBM1401Cpu { public: explicit IBM1401Cpu(machines::IBM1401Memory&); [[nodiscard]] std::size_t instruction_address()const noexcept; void set_instruction_address(std::size_t); StepResult step(); void reset()noexcept; private: machines::IBM1401Memory& memory_; std::size_t instruction_address_{0}; };
}