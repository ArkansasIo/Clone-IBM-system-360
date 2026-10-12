#include "ibmlegacy/fortran/array.hpp"
#include <limits>
namespace ibmlegacy::fortran {
NumericArray1D::NumericArray1D(long lo,long hi,TypeKind type):lower_(lo),upper_(hi),type_(type){
 if(hi<lo){error_="Upper bound is less than lower bound";return;}
 const auto count=static_cast<unsigned long long>(hi-lo)+1ULL;
 if(count>10000000ULL||count>static_cast<unsigned long long>(std::numeric_limits<std::size_t>::max())){error_="Array extent exceeds safety limit";return;}
 values_.resize(static_cast<std::size_t>(count),0.0);
}
long NumericArray1D::lower_bound()const noexcept{return lower_;}long NumericArray1D::upper_bound()const noexcept{return upper_;}std::size_t NumericArray1D::size()const noexcept{return values_.size();}
bool NumericArray1D::contains(long i)const noexcept{return !values_.empty()&&i>=lower_&&i<=upper_;}
std::optional<double> NumericArray1D::get(long i)const noexcept{if(!contains(i))return{};return values_[static_cast<std::size_t>(i-lower_)];}
bool NumericArray1D::set(long i,double v)noexcept{if(!contains(i))return false;if(type_==TypeKind::Integer)v=static_cast<double>(static_cast<long long>(v));values_[static_cast<std::size_t>(i-lower_)]=v;return true;}
const std::string& NumericArray1D::error()const noexcept{return error_;}
}