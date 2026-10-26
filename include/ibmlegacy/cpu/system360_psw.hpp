#pragma once
#include <cstdint>
namespace ibmlegacy::cpu {
struct System360PSW {
 std::uint32_t instruction_address{};
 std::uint8_t condition_code{};
 bool problem_state{true};
 bool machine_check_mask{};
 bool program_mask{};
 bool io_mask{};
 bool external_mask{};
 void reset() noexcept { instruction_address=0; condition_code=0; problem_state=true; machine_check_mask=false; program_mask=false; io_mask=false; external_mask=false; }
};
}
