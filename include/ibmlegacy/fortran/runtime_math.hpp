#pragma once
#include <cstddef>
namespace ibmlegacy::fortran::runtime {
[[nodiscard]] double dabs(double x)noexcept; [[nodiscard]] double dsqrt(double x)noexcept; [[nodiscard]] double dexp(double x)noexcept; [[nodiscard]] double dlog(double x)noexcept;
[[nodiscard]] double dsin(double x)noexcept; [[nodiscard]] double dcos(double x)noexcept; [[nodiscard]] double datan(double x)noexcept;
[[nodiscard]] double dmod(double x,double y)noexcept;
}