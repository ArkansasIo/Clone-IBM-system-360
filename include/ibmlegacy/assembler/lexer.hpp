#pragma once
#include "ibmlegacy/assembler/line.hpp"
#include <optional>
#include <string>
namespace ibmlegacy::assembler {
struct LexResult { bool success{false}; AssemblerLine line; std::string diagnostic; };
[[nodiscard]] LexResult parse_assembler_line(const std::string& source,std::size_t line_number=1);
}