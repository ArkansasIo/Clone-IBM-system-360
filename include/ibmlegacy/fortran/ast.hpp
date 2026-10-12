#pragma once
#include "ibmlegacy/fortran/types.hpp"
#include <string>
#include <vector>
namespace ibmlegacy::fortran {
enum class StatementKind { Program, End, Declaration, Assignment, Print, Read, Write, Format, DoLoop, IfStatement, GoTo, Call, Return, Stop, Pause, Continue, Data, Common, Equivalence, Parameter, Dimension, External, Intrinsic, AssignLabel, Unknown };
struct Statement { StatementKind kind{StatementKind::Unknown}; SourceLocation location; std::string label; std::string source; std::string keyword; };
struct Program { std::string name; std::vector<Statement> statements; };
}