#pragma once
#include "ibmlegacy/fortran/types.hpp"
#include <map>
#include <string>
namespace ibmlegacy::fortran {
struct ExpressionResult { bool success{false}; double value{0.0}; std::string diagnostic; };
[[nodiscard]] ExpressionResult evaluate_numeric_expression(const std::string& expression,const std::map<std::string,double>& variables={});
}