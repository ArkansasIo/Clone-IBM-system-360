#include "ibmlegacy/cpu/system360_alu.hpp"
namespace ibmlegacy::cpu {
std::uint8_t condition_code_logical(std::uint32_t v)noexcept{return v==0?0:((v&0x80000000U)?1:2);}
ArithmeticResult add32(std::uint32_t a,std::uint32_t b)noexcept{
 const std::uint64_t wide=static_cast<std::uint64_t>(a)+b;const auto v=static_cast<std::uint32_t>(wide);
 const bool ov=((~(a^b)&(a^v)&0x80000000U)!=0);
 return {v,condition_code_logical(v),wide>0xFFFFFFFFULL,ov};
}
ArithmeticResult subtract32(std::uint32_t a,std::uint32_t b)noexcept{
 const auto v=static_cast<std::uint32_t>(a-b);const bool borrow=a<b;
 const bool ov=(((a^b)&(a^v)&0x80000000U)!=0);
 return {v,condition_code_logical(v),borrow,ov};
}
}