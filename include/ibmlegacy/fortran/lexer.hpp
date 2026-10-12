#pragma once
#include "ibmlegacy/fortran/diagnostic.hpp"
#include "ibmlegacy/fortran/token.hpp"
#include <string_view>
#include <vector>
namespace ibmlegacy::fortran {
struct LexedLine { std::vector<Token> tokens; std::vector<Diagnostic> diagnostics; };
[[nodiscard]] LexedLine lex_statement(std::string_view text,std::string file={},std::size_t line=1,std::size_t base_column=7);
}