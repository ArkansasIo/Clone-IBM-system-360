#pragma once
#include "ibmlegacy/cpu/cpu_result.hpp"
#include "ibmlegacy/machines/system360.hpp"
namespace ibmlegacy::cpu {
class System360Cpu { public: explicit System360Cpu(machines::System360Storage&); [[nodiscard]] machines::System360Registers& registers()noexcept; [[nodiscard]] const machines::System360Registers& registers()const noexcept; StepResult step(); void reset()noexcept; private: machines::System360Storage& storage_; machines::System360Registers regs_{}; };
}