#pragma once
#include "ibmlegacy/runtime/machine_config.hpp"
namespace ibmlegacy::runtime {
[[nodiscard]] MachineConfig ibm1401_4k_profile();
[[nodiscard]] MachineConfig ibm1401_8k_profile();
[[nodiscard]] MachineConfig system360_model30_profile();
[[nodiscard]] MachineConfig system360_model40_profile();
[[nodiscard]] MachineConfig system360_model50_profile();
}