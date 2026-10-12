#include "ibmlegacy/fortran/runtime_math.hpp"
#include <cmath>
namespace ibmlegacy::fortran::runtime {
double dabs(double x)noexcept{return std::abs(x);}double dsqrt(double x)noexcept{return std::sqrt(x);}double dexp(double x)noexcept{return std::exp(x);}double dlog(double x)noexcept{return std::log(x);}double dsin(double x)noexcept{return std::sin(x);}double dcos(double x)noexcept{return std::cos(x);}double datan(double x)noexcept{return std::atan(x);}double dmod(double x,double y)noexcept{return std::fmod(x,y);}
}