#include "ibmlegacy/fortran/intrinsics.hpp"
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstdlib>
namespace ibmlegacy::fortran {
namespace {double num(const TypedValue&v){if(auto p=std::get_if<double>(&v.value))return *p;if(auto p=std::get_if<long long>(&v.value))return static_cast<double>(*p);if(auto p=std::get_if<bool>(&v.value))return *p?1.0:0.0;return 0.0;}std::string upper(std::string s){for(char&c:s)c=static_cast<char>(std::toupper(static_cast<unsigned char>(c)));return s;}}
std::optional<TypedValue> evaluate_intrinsic(const std::string&raw,const std::vector<TypedValue>&a,std::string&err){
 const auto n=upper(raw);if(a.empty()){err=n+" requires at least one argument";return{};}double x=num(a[0]),y=a.size()>1?num(a[1]):0;
 if(n=="ABS")return TypedValue{a[0].type,a[0].type==TypeKind::Integer?ScalarValue{static_cast<long long>(std::llabs(static_cast<long long>(x)))}:ScalarValue{std::abs(x)}};
 if(n=="INT")return TypedValue{TypeKind::Integer,static_cast<long long>(x)};
 if(n=="NINT")return TypedValue{TypeKind::Integer,static_cast<long long>(std::llround(x))};
 if(n=="REAL")return TypedValue{TypeKind::Real,x};
 if(n=="DBLE")return TypedValue{TypeKind::DoublePrecision,x};
 if(n=="SQRT"){if(x<0){err="SQRT argument must be nonnegative";return{};}return TypedValue{TypeKind::Real,std::sqrt(x)};}
 if(n=="EXP")return TypedValue{TypeKind::Real,std::exp(x)};
 if(n=="LOG"||n=="ALOG"){if(x<=0){err=n+" argument must be positive";return{};}return TypedValue{TypeKind::Real,std::log(x)};}
 if(n=="SIN")return TypedValue{TypeKind::Real,std::sin(x)};
 if(n=="COS")return TypedValue{TypeKind::Real,std::cos(x)};
 if(n=="TAN")return TypedValue{TypeKind::Real,std::tan(x)};
 if(n=="MAX"||n=="AMAX0"||n=="MAX0"){double z=x;for(std::size_t i=1;i<a.size();++i)z=std::max(z,num(a[i]));return TypedValue{TypeKind::Real,z};}
 if(n=="MIN"||n=="AMIN0"||n=="MIN0"){double z=x;for(std::size_t i=1;i<a.size();++i)z=std::min(z,num(a[i]));return TypedValue{TypeKind::Real,z};}
 if(n=="MOD"){if(a.size()<2||y==0){err="MOD requires two arguments and a nonzero divisor";return{};}return TypedValue{a[0].type,std::fmod(x,y)};}
 err="Unknown or unsupported intrinsic: "+n;return{};
}
}