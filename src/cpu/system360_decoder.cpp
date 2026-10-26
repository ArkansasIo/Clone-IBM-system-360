#include "ibmlegacy/cpu/system360_decoder.hpp"
namespace ibmlegacy::cpu {
DecodedInstruction decode_rr(std::uint8_t first,std::uint8_t second) noexcept{
 const auto* info=find_system360_opcode(first);
 if(!info||info->format!="RR")return {nullptr,first,second,0,0,0,0,static_cast<std::uint8_t>((second>>4U)&0x0FU),static_cast<std::uint8_t>(second&0x0FU),0};
 return {info,first,second,0,0,static_cast<std::uint8_t>((second>>4U)&0x0FU),static_cast<std::uint8_t>(second&0x0FU),0,0,0};
}
DecodedInstruction decode_rx(std::uint8_t first,std::uint8_t second,std::uint8_t third,std::uint8_t fourth) noexcept{
 const auto* info=find_system360_opcode(first);
 if(!info||info->format!="RX")return {nullptr,first,second,third,fourth,0,0,0,0,0};
 return {info,first,second,third,fourth,static_cast<std::uint8_t>((second>>4U)&0x0FU),0,static_cast<std::uint8_t>(second&0x0FU),static_cast<std::uint8_t>((third>>4U)&0x0FU),static_cast<std::uint16_t>(((third&0x0FU)<<8U)|fourth)};
}
}