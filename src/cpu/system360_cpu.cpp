#include "ibmlegacy/cpu/system360_cpu.hpp"
#include "ibmlegacy/cpu/system360_alu.hpp"
#include "ibmlegacy/cpu/system360_decoder.hpp"
#include <cstdint>
#include <stdexcept>
namespace ibmlegacy::cpu {
namespace {
std::uint8_t cmp(std::uint32_t a,std::uint32_t b) noexcept { auto sa=static_cast<std::int32_t>(a),sb=static_cast<std::int32_t>(b); return sa<sb?1U:(sa>sb?2U:0U); }
std::uint8_t ucmp(std::uint32_t a,std::uint32_t b) noexcept { return a<b?1U:(a>b?2U:0U); }
std::uint32_t ea(const DecodedInstruction& d,const machines::System360Registers&r) noexcept { return (d.b2? r.general[d.b2]:0U)+(d.x2? r.general[d.x2]:0U)+d.d2; }
std::uint32_t ea1(const DecodedInstruction& d,const machines::System360Registers&r) noexcept { return (d.b1? r.general[d.b1]:0U)+d.d1; }
std::uint16_t hw(const machines::System360Storage&s,std::size_t a){return static_cast<std::uint16_t>((std::uint16_t(s.read_byte(a))<<8U)|s.read_byte(a+1));}
std::int32_t shw(const machines::System360Storage&s,std::size_t a){return static_cast<std::int16_t>(hw(s,a));}
bool branch(std::uint8_t m,std::uint8_t cc) noexcept{return (m&(1U<<(3U-cc)))!=0U;}
}
System360Cpu::System360Cpu(machines::System360Storage&s):storage_(s){}
machines::System360Registers& System360Cpu::registers()noexcept{return regs_;}
const machines::System360Registers& System360Cpu::registers()const noexcept{return regs_;}
void System360Cpu::reset()noexcept{regs_={};psw_.reset();interrupts_.clear();}
StepResult System360Cpu::step(){
 const auto pc=regs_.instruction_address;
 try {
  if(interrupts_.pending() && psw_.io_mask){ interrupts_.take(); }
  const auto op=storage_.read_byte(pc); const auto* info=find_system360_opcode(op); if(!info)return{StepState::IllegalInstruction,op,"Unsupported System/360 opcode"};
  if(info->format=="RR") { auto d=decode_rr(op,storage_.read_byte(pc+1));auto r1=d.r1,r2=d.r2;regs_.instruction_address+=2U;switch(op){
   case 0x05:{auto n=regs_.instruction_address;if(r1)regs_.general[r1]=n;if(r2)regs_.instruction_address=regs_.general[r2];return{StepState::Executed,op,"BALR"};}
   case 0x07:if(branch(r1,regs_.condition_code)&&r2)regs_.instruction_address=regs_.general[r2];return{StepState::Executed,op,"BCR"};
   case 0x12:regs_.general[r1]=regs_.general[r2];regs_.condition_code=condition_code_logical(regs_.general[r1]);return{StepState::Executed,op,"LTR"};
   case 0x14:regs_.general[r1]&=regs_.general[r2];regs_.condition_code=condition_code_logical(regs_.general[r1]);return{StepState::Executed,op,"NR"};
   case 0x15:regs_.condition_code=ucmp(regs_.general[r1],regs_.general[r2]);return{StepState::Executed,op,"CLR"};
   case 0x16:regs_.general[r1]|=regs_.general[r2];regs_.condition_code=condition_code_logical(regs_.general[r1]);return{StepState::Executed,op,"OR"};
   case 0x17:regs_.general[r1]^=regs_.general[r2];regs_.condition_code=condition_code_logical(regs_.general[r1]);return{StepState::Executed,op,"XR"};
   case 0x18:regs_.general[r1]=regs_.general[r2];return{StepState::Executed,op,"LR"};
   case 0x19:regs_.condition_code=cmp(regs_.general[r1],regs_.general[r2]);return{StepState::Executed,op,"CR"};
   case 0x1A:{auto x=add32(regs_.general[r1],regs_.general[r2]);regs_.general[r1]=x.value;regs_.condition_code=x.condition_code;return{StepState::Executed,op,"AR"};}
   case 0x1B:{auto x=subtract32(regs_.general[r1],regs_.general[r2]);regs_.general[r1]=x.value;regs_.condition_code=x.condition_code;return{StepState::Executed,op,"SR"};}
   case 0x1E:{auto x=add32(regs_.general[r1],regs_.general[r2]);regs_.general[r1]=x.value;regs_.condition_code=x.condition_code;return{StepState::Executed,op,"ALR"};}
   case 0x1F:{auto x=subtract32(regs_.general[r1],regs_.general[r2]);regs_.general[r1]=x.value;regs_.condition_code=x.condition_code;return{StepState::Executed,op,"SLR"};}
   default:return{StepState::IllegalInstruction,op,"RR opcode catalogued but not implemented"};}}
  if(info->format=="RX") {auto d=decode_rx(op,storage_.read_byte(pc+1),storage_.read_byte(pc+2),storage_.read_byte(pc+3));auto a=ea(d,regs_);regs_.instruction_address+=4U;switch(op){
   case 0x40:storage_.write_byte(a,static_cast<std::uint8_t>(regs_.general[d.r1]));return{StepState::Executed,op,"STC"};case 0x41:regs_.general[d.r1]=a;return{StepState::Executed,op,"LA"};
   case 0x45:{auto n=regs_.instruction_address;if(d.r1)regs_.general[d.r1]=n;regs_.instruction_address=a;return{StepState::Executed,op,"BAL"};}case 0x46:if(--regs_.general[d.r1])regs_.instruction_address=a;return{StepState::Executed,op,"BCT"};case 0x47:if(branch(d.r1,regs_.condition_code))regs_.instruction_address=a;return{StepState::Executed,op,"BC"};
   case 0x48:regs_.general[d.r1]=static_cast<std::uint32_t>(shw(storage_,a));return{StepState::Executed,op,"LH"};case 0x49:regs_.condition_code=cmp(regs_.general[d.r1],static_cast<std::uint32_t>(shw(storage_,a)));return{StepState::Executed,op,"CH"};case 0x4A:regs_.general[d.r1]+=static_cast<std::uint32_t>(shw(storage_,a));return{StepState::Executed,op,"AH"};case 0x4B:regs_.general[d.r1]-=static_cast<std::uint32_t>(shw(storage_,a));return{StepState::Executed,op,"SH"};
   case 0x50:storage_.write_word(a,regs_.general[d.r1]);return{StepState::Executed,op,"ST"};case 0x54:regs_.general[d.r1]&=storage_.read_word(a);regs_.condition_code=condition_code_logical(regs_.general[d.r1]);return{StepState::Executed,op,"N"};case 0x55:regs_.condition_code=ucmp(regs_.general[d.r1],storage_.read_word(a));return{StepState::Executed,op,"CL"};case 0x56:regs_.general[d.r1]|=storage_.read_word(a);regs_.condition_code=condition_code_logical(regs_.general[d.r1]);return{StepState::Executed,op,"O"};case 0x57:regs_.general[d.r1]^=storage_.read_word(a);regs_.condition_code=condition_code_logical(regs_.general[d.r1]);return{StepState::Executed,op,"X"};case 0x58:regs_.general[d.r1]=storage_.read_word(a);return{StepState::Executed,op,"L"};case 0x59:regs_.condition_code=cmp(regs_.general[d.r1],storage_.read_word(a));return{StepState::Executed,op,"C"};
   case 0x5A:{auto x=add32(regs_.general[d.r1],storage_.read_word(a));regs_.general[d.r1]=x.value;regs_.condition_code=x.condition_code;return{StepState::Executed,op,"A"};}case 0x5B:{auto x=subtract32(regs_.general[d.r1],storage_.read_word(a));regs_.general[d.r1]=x.value;regs_.condition_code=x.condition_code;return{StepState::Executed,op,"S"};}default:return{StepState::IllegalInstruction,op,"RX opcode catalogued but not implemented"};}}
  if(info->format=="RS") {auto d=decode_rs(op,storage_.read_byte(pc+1),storage_.read_byte(pc+2),storage_.read_byte(pc+3));auto a=ea(d,regs_);regs_.instruction_address+=4U;switch(op){
   case 0x88:regs_.general[d.r1] >>= (a&31U);return{StepState::Executed,op,"SRL"};case 0x89:regs_.general[d.r1] <<= (a&31U);return{StepState::Executed,op,"SLL"};case 0x8A:regs_.general[d.r1]=static_cast<std::uint32_t>(static_cast<std::int32_t>(regs_.general[d.r1])>>(a&31U));return{StepState::Executed,op,"SRA"};case 0x8B:regs_.general[d.r1]=static_cast<std::uint32_t>(static_cast<std::int32_t>(regs_.general[d.r1])<<(a&31U));return{StepState::Executed,op,"SLA"};
   case 0x90:{auto r=d.r1;for(std::uint8_t n=r;;++n){storage_.write_word(a+(n-r)*4U,regs_.general[n]);if(n==d.r3)break;}return{StepState::Executed,op,"STM"};}
   case 0x98:{auto r=d.r1;for(std::uint8_t n=r;;++n){regs_.general[n]=storage_.read_word(a+(n-r)*4U);if(n==d.r3)break;}return{StepState::Executed,op,"LM"};}default:return{StepState::IllegalInstruction,op,"RS opcode catalogued but not implemented"};}}
  if(info->format=="SI") {auto d=decode_si(op,storage_.read_byte(pc+1),storage_.read_byte(pc+2),storage_.read_byte(pc+3));auto a=ea1(d,regs_);auto v=storage_.read_byte(a);regs_.instruction_address+=4U;switch(op){case 0x91:regs_.condition_code=((v&d.i2)==0)?0:((v&d.i2)==d.i2?3:1);return{StepState::Executed,op,"TM"};case 0x92:storage_.write_byte(a,d.i2);return{StepState::Executed,op,"MVI"};case 0x94:storage_.write_byte(a,v&d.i2);return{StepState::Executed,op,"NI"};case 0x95:regs_.condition_code=(v<d.i2)?1:(v>d.i2?2:0);return{StepState::Executed,op,"CLI"};case 0x96:storage_.write_byte(a,v|d.i2);return{StepState::Executed,op,"OI"};case 0x97:storage_.write_byte(a,v^d.i2);return{StepState::Executed,op,"XI"};default:return{StepState::IllegalInstruction,op,"SI opcode catalogued but not implemented"};}}
  if(info->format=="SS") {auto d=decode_ss(op,storage_.read_byte(pc+1),storage_.read_byte(pc+2),storage_.read_byte(pc+3),storage_.read_byte(pc+4),storage_.read_byte(pc+5));auto a=ea1(d,regs_);auto b=(d.b2?regs_.general[d.b2]:0U)+d.d2;auto len=static_cast<std::size_t>(d.l1)+1U;regs_.instruction_address+=6U;switch(op){case 0xD2:for(std::size_t i=0;i<len;++i)storage_.write_byte(a+i,storage_.read_byte(b+i));return{StepState::Executed,op,"MVC"};case 0xD5:{std::uint8_t cc=0;for(std::size_t i=0;i<len;++i){auto x=storage_.read_byte(a+i),y=storage_.read_byte(b+i);if(x<y){cc=1;break;}if(x>y){cc=2;break;}}regs_.condition_code=cc;return{StepState::Executed,op,"CLC"};}case 0xD7:for(std::size_t i=0;i<len;++i)storage_.write_byte(a+i,storage_.read_byte(a+i)^storage_.read_byte(b+i));return{StepState::Executed,op,"XC"};case 0xDC:for(std::size_t i=0;i<len;++i)storage_.write_byte(a+i,storage_.read_byte(b+i));return{StepState::Executed,op,"TR"};default:return{StepState::IllegalInstruction,op,"SS opcode catalogued but not implemented"};}}
  return{StepState::IllegalInstruction,op,"Unsupported instruction format"};
 }catch(const std::out_of_range&){return{StepState::MemoryFault,0,"Instruction or operand access outside storage"};}
}
}
