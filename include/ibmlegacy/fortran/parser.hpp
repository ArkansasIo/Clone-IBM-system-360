#pragma once
#include "ibmlegacy/fortran/ast.hpp"
#include "ibmlegacy/fortran/diagnostic.hpp"
#include <filesystem>
#include <vector>
namespace ibmlegacy::fortran {
struct ParseResult { bool success{false}; Program program; std::vector<Diagnostic> diagnostics; };
[[nodiscard]] ParseResult parse_fortran_source(const std::filesystem::path& path);
}