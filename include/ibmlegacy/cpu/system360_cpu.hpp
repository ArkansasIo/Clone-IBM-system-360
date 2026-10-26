#pragma once
#include "ibmlegacy/cpu/cpu_result.hpp"
#include "ibmlegacy/cpu/system360_interrupts.hpp"
#include "ibmlegacy/cpu/system360_psw.hpp"
#include "ibmlegacy/machines/system360.hpp"
namespace ibmlegacy::cpu {
class System360Cpu {
public:
 explicit System360Cpu(machines::System360Storage&);
 [[nodiscard]] machines::System360Registers& registers() noexcept;
 [[nodiscard]] const machines::System360Registers& registers() const noexcept;
 [[nodiscard]] System360PSW& psw() noexcept { return psw_; }
 [[nodiscard]] const System360PSW& psw() const noexcept { return psw_; }
 [[nodiscard]] System360InterruptController& interrupts() noexcept { return interrupts_; }
 StepResult step(); void reset() noexcept;
private: machines::System360Storage& storage_; machines::System360Registers regs_{}; System360PSW psw_{}; System360InterruptController interrupts_{};
};
}
