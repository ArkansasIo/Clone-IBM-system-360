#pragma once
#include "ibmlegacy/assembler/line.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
namespace ibmlegacy::assembler {
struct EncodeResult { bool success{false}; std::vector<std::uint8_t> bytes; std::string diagnostic; };
[[nodiscard]] EncodeResult encode_rr_subset(const AssemblerLine& line);
}