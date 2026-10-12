#pragma once
#include "ibmlegacy/fortran/types.hpp"
#include <map>
#include <optional>
#include <string>
namespace ibmlegacy::fortran {
struct Symbol { std::string name; TypeKind type{TypeKind::Real}; bool declared{false}; std::optional<TypedValue> initial_value; };
class SymbolTable {
public:
 [[nodiscard]] bool declare(Symbol symbol); [[nodiscard]] Symbol* find(const std::string& name); [[nodiscard]] const Symbol* find(const std::string& name)const;
 [[nodiscard]] const std::map<std::string,Symbol>& entries()const noexcept; void clear()noexcept;
private: std::map<std::string,Symbol> symbols_;
};
}