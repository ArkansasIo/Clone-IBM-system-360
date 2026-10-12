#pragma once
#include "ibmlegacy/fortran/types.hpp"
#include <optional>
#include <string>
#include <vector>
namespace ibmlegacy::fortran {
[[nodiscard]] std::optional<TypedValue> evaluate_intrinsic(const std::string& name,const std::vector<TypedValue>& args,std::string& error);
}