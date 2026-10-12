#pragma once
#include <cstddef>
#include <string>
#include <variant>
namespace ibmlegacy::fortran {
enum class TypeKind { Integer, Real, DoublePrecision, Logical, Character };
using ScalarValue = std::variant<long long,double,bool,std::string>;
struct SourceLocation { std::string file; std::size_t line{1}; std::size_t column{1}; };
struct TypedValue { TypeKind type{TypeKind::Integer}; ScalarValue value{0LL}; };
}