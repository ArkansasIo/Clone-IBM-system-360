#pragma once
#include <cstddef>
#include <string>
namespace ibmlegacy::fortran {
struct SourceRecord { std::size_t line_number{0}; char indicator{' '}; std::string label; std::string statement; std::string continuation; };
}