#pragma once
#include "ibmlegacy/fortran/ast.hpp"
#include <filesystem>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>
namespace ibmlegacy::fortran {
// Result of running a fixed-form source file or an interactive REPL line.
struct AppRunResult {
 bool success{false};
 std::string output;        // captured program output
 std::string diagnostics;   // formatted diagnostics
};
// Interactive read-eval-print front end for the educational FORTRAN subset.
// Expressions are evaluated with the numeric expression evaluator; statements
// are classified with the parser scaffold and echoed with their kind.
class FortranRepl {
public:
 FortranRepl(std::istream& in, std::ostream& out);
 // Runs one line of input and writes any response to the output stream.
 // Returns false when the line requests termination (QUIT or EXIT).
 bool handle_line(const std::string& line);
 void banner()const;
private:
 std::istream& in_;
 std::ostream& out_;
 std::map<std::string,double> variables_;
};
// Minimal tree-walking interpreter over the current statement scaffold.
// Only assignment, declaration, PRINT and STOP/END are meaningful; other
// statement families are reported as unsupported rather than executed.
AppRunResult run_fortran_source(const std::filesystem::path& path);
// Runs the REPL until EOF or a QUIT/EXIT line.
int run_fortran_repl(std::istream& in, std::ostream& out);
} // namespace ibmlegacy::fortran
