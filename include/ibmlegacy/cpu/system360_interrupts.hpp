#pragma once
#include <cstdint>
namespace ibmlegacy::cpu {
enum class InterruptClass : std::uint8_t { None, External, SupervisorCall, Program, MachineCheck, IO };
struct InterruptRequest { InterruptClass type{InterruptClass::None}; std::uint16_t code{}; std::uint32_t parameter{}; };
class System360InterruptController {
public:
 void request(InterruptRequest r) noexcept { pending_=r; }
 [[nodiscard]] bool pending() const noexcept { return pending_.type != InterruptClass::None; }
 [[nodiscard]] InterruptRequest take() noexcept { auto r=pending_; pending_={}; return r; }
 void clear() noexcept { pending_={}; }
private: InterruptRequest pending_{};
};
}
