#include "ibmlegacy/cpu/system360_decoder.hpp"
namespace ibmlegacy::cpu {
DecodedInstruction decode_rr(std::uint8_t first,std::uint8_t second)noexcept{
 const auto* info=find_system360_opcode(first);
 if(!info||info->format!="RR")return {nullptr,first,second,0,0};
 return {info,first,second,static_cast<std::uint8_t>((second>>4U)&0x0FU),static_cast<std::uint8_t>(second&0x0FU)};
}
}