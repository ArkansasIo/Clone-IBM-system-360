#pragma once
#include <cstddef>
#include <string>
#include <vector>
namespace ibmlegacy::assembler {
struct AssemblerLine { std::size_t line_number{0}; std::string label; std::string mnemonic; std::vector<std::string> operands; std::string comment; };
}