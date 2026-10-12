#pragma once
#include "ibmlegacy/fortran/types.hpp"
#include <cstddef>
#include <optional>
#include <string>
#include <vector>
namespace ibmlegacy::fortran {
class NumericArray1D {
public:
 NumericArray1D(long lower_bound,long upper_bound,TypeKind type=TypeKind::Real);
 [[nodiscard]] long lower_bound()const noexcept; [[nodiscard]] long upper_bound()const noexcept; [[nodiscard]] std::size_t size()const noexcept;
 [[nodiscard]] bool contains(long index)const noexcept;
 [[nodiscard]] std::optional<double> get(long index)const noexcept;
 [[nodiscard]] bool set(long index,double value)noexcept;
 [[nodiscard]] const std::string& error()const noexcept;
private: long lower_{0};long upper_{-1};TypeKind type_{TypeKind::Real};std::vector<double> values_;std::string error_;
};
}