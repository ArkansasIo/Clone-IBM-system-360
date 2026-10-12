#include "ibmlegacy/assembler/encoder.hpp"
#include <algorithm>
#include <cctype>
#include <string>
namespace ibmlegacy::assembler {
namespace {bool parse_reg(std::string s,unsigned&v){if(!s.empty()&&(s[0]=='R'||s[0]=='r'))s.erase(0,1);if(s.empty())return false;try{std::size_t n=0;auto x=std::stoul(s,&n);if(n!=s.size()||x>15)return false;v=static_cast<unsigned>(x);return true;}catch(...){return false;}}}
EncodeResult encode_rr_subset(const AssemblerLine& l){
 unsigned op=0; if(l.mnemonic=="LR")op=0x18;else if(l.mnemonic=="AR")op=0x1A;else if(l.mnemonic=="BALR")op=0x05;else if(l.mnemonic=="BCR")op=0x07;else return {false,{},"Unsupported mnemonic: "+l.mnemonic};
 if(l.operands.size()!=2)return {false,{},"RR instruction requires two register operands"};
 unsigned r1=0,r2=0;if(!parse_reg(l.operands[0],r1)||!parse_reg(l.operands[1],r2))return {false,{},"Invalid register operand"};
 return {true,{static_cast<std::uint8_t>(op),static_cast<std::uint8_t>((r1<<4U)|r2)},{}};
}
}