#pragma once
#include "ibmlegacy/fortran/types.hpp"
#include <string>
#include <vector>
namespace ibmlegacy::fortran {
enum class Severity { Note, Warning, Error };
struct Diagnostic { Severity severity{Severity::Error}; SourceLocation location; std::string code; std::string message; };
class DiagnosticBag {
public:
 void add(Diagnostic d); void error(SourceLocation l,std::string code,std::string message); void warning(SourceLocation l,std::string code,std::string message);
 [[nodiscard]] bool has_errors()const noexcept; [[nodiscard]] const std::vector<Diagnostic>& all()const noexcept; [[nodiscard]] std::string format()const;
private: std::vector<Diagnostic> items_;
};
}