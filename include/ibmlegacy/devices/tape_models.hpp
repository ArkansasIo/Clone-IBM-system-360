#pragma once
#include "ibmlegacy/devices/tape_drive.hpp"
namespace ibmlegacy::devices {
// Named model profiles share the same record-image backend; mechanical timing and density encoding are not simulated.
[[nodiscard]] TapeDriveConfig ibm729_model_ii_profile();
[[nodiscard]] TapeDriveConfig ibm729_model_iv_profile();
[[nodiscard]] TapeDriveConfig ibm2401_profile();
[[nodiscard]] TapeDriveConfig ibm2402_profile();
[[nodiscard]] TapeDriveConfig ibm2403_profile();
[[nodiscard]] TapeDriveConfig ibm2404_profile();
}