#include "ibmlegacy/cpu/system360_cpu.hpp"
#include "ibmlegacy/cpu/system360_alu.hpp"
#include "ibmlegacy/cpu/system360_decoder.hpp"
#include <cstdint>
#include <stdexcept>
namespace ibmlegacy::cpu {
namespace {
std::uint8_t compare32(std::uint32_t a,std::uint32_t b) noexcept {
 const auto sa=static_cast<std::int32_t>(a), sb=static_cast<std::int32_t>(b);
 return sa<sb?1U:(sa>sb?2U:0U);
}
std::uint8_t compare_unsigned32(std::uint32_t a,std::uint32_t b) noexcept { return a<b?1U:(a>b?2U:0U); }
std::uint32_t effective_address(const DecodedInstruction& d,const machines::System360Registers& r) noexcept {
 const std::uint32_t base=d.b2==0?0U:r.general[d.b2];
 const std::uint32_t index=d.x2==0?0U:r.general[d.x2];
 return base+index+d.displacement;
}
std::uint16_t read_halfword(const machines::System360Storage& s,std::size_t a) {
 return static_cast<std::uint16_t>((std::uint16_t(s.read_byte(a))<<8U)|s.read_byte(a+1));
}
std::int32_t signed_halfword(const machines::System360Storage& s,std::size_t a) { return static_cast<std::int16_t>(read_halfword(s,a)); }
bool branch_selected(std::uint8_t mask,std::uint8_t cc) noexcept { return (mask&(1U<<(3U-cc)))!=0U; }
}
System360Cpu::System360Cpu(machines::System360Storage&s):storage_(s){}
machines::System360Registers& System360Cpu::registers()noexcept{return regs_;}
const machines::System360Registers& System360Cpu::registers()const noexcept{return regs_;}
void System360Cpu::reset()noexcept{regs_={};}
StepResult System360Cpu::step(){
 const auto pc=regs_.instruction_address;
 try {
  const auto first=storage_.read_byte(pc);
  const auto* info=find_system360_opcode(first);
  if(!info)return{StepState::IllegalInstruction,first,"Unsupported System/360 opcode"};
  if(info->format=="RR") {
   const auto d=decode_rr(first,storage_.read_byte(pc+1));
   const auto r1=d.r1; const auto r2=d.r2;
   regs_.instruction_address+=2U;
   switch(first) {
    case 0x05: { const auto next=regs_.instruction_address; if(r1) regs_.general[r1]=next; if(r2) regs_.instruction_address=regs_.general[r2]; return{StepState::Executed,first,"BALR"}; }
    case 0x07: if(branch_selected(r1,regs_.condition_code)&&r2) regs_.instruction_address=regs_.general[r2]; return{StepState::Executed,first,"BCR"};
    case 0x12: regs_.general[r1]=regs_.general[r2]; regs_.condition_code=condition_code_logical(regs_.general[r1]); return{StepState::Executed,first,"LTR"};
    case 0x14: regs_.general[r1]&=regs_.general[r2]; regs_.condition_code=condition_code_logical(regs_.general[r1]); return{StepState::Executed,first,"NR"};
    case 0x15: regs_.condition_code=compare_unsigned32(regs_.general[r1],regs_.general[r2]); return{StepState::Executed,first,"CLR"};
    case 0x16: regs_.general[r1]|=regs_.general[r2]; regs_.condition_code=condition_code_logical(regs_.general[r1]); return{StepState::Executed,first,"OR"};
    case 0x17: regs_.general[r1]^=regs_.general[r2]; regs_.condition_code=condition_code_logical(regs_.general[r1]); return{StepState::Executed,first,"XR"};
    case 0x18: regs_.general[r1]=regs_.general[r2]; return{StepState::Executed,first,"LR"};
    case 0x19: regs_.condition_code=compare32(regs_.general[r1],regs_.general[r2]); return{StepState::Executed,first,"CR"};
    case 0x1A: { const auto x=add32(regs_.general[r1],regs_.general[r2]); regs_.general[r1]=x.value; regs_.condition_code=x.condition_code; return{StepState::Executed,first,"AR"}; }
    case 0x1B: { const auto x=subtract32(regs_.general[r1],regs_.general[r2]); regs_.general[r1]=x.value; regs_.condition_code=x.condition_code; return{StepState::Executed,first,"SR"}; }
    case 0x1E: { const auto x=add32(regs_.general[r1],regs_.general[r2]); regs_.general[r1]=x.value; regs_.condition_code=x.condition_code; return{StepState::Executed,first,"ALR"}; }
    case 0x1F: { const auto x=subtract32(regs_.general[r1],regs_.general[r2]); regs_.general[r1]=x.value; regs_.condition_code=x.condition_code; return{StepState::Executed,first,"SLR"}; }
    default: return{StepState::IllegalInstruction,first,"Opcode is catalogued but not implemented in this CPU milestone"};
   }
  }
  if(info->format=="RX") {
   const auto d=decode_rx(first,storage_.read_byte(pc+1),storage_.read_byte(pc+2),storage_.read_byte(pc+3));
   const auto ea=effective_address(d,regs_);
   regs_.instruction_address+=4U;
   switch(first) {
    case 0x40: storage_.write_byte(ea,static_cast<std::uint8_t>(regs_.general[d.r1])); return{StepState::Executed,first,"STC"};
    case 0x41: regs_.general[d.r1]=ea; return{StepState::Executed,first,"LA"};
    case 0x45: { const auto next=regs_.instruction_address; if(d.r1) regs_.general[d.r1]=next; regs_.instruction_address=ea; return{StepState::Executed,first,"BAL"}; }
    case 0x46: if(--regs_.general[d.r1]!=0U) regs_.instruction_address=ea; return{StepState::Executed,first,"BCT"};
    case 0x47: if(branch_selected(d.r1,regs_.condition_code)) regs_.instruction_address=ea; return{StepState::Executed,first,"BC"};
    case 0x48: regs_.general[d.r1]=static_cast<std::uint32_t>(signed_halfword(storage_,ea)); return{StepState::Executed,first,"LH"};
    case 0x49: regs_.condition_code=compare32(regs_.general[d.r1],static_cast<std::uint32_t>(signed_halfword(storage_,ea))); return{StepState::Executed,first,"CH"};
    case 0x4A: regs_.general[d.r1]+=static_cast<std::uint32_t>(signed_halfword(storage_,ea)); return{StepState::Executed,first,"AH"};
    case 0x4B: regs_.general[d.r1]-=static_cast<std::uint32_t>(signed_halfword(storage_,ea)); return{StepState::Executed,first,"SH"};
    case 0x50: storage_.write_word(ea,regs_.general[d.r1]); return{StepState::Executed,first,"ST"};
    case 0x54: regs_.general[d.r1]&=storage_.read_word(ea); regs_.condition_code=condition_code_logical(regs_.general[d.r1]); return{StepState::Executed,first,"N"};
    case 0x55: regs_.condition_code=compare_unsigned32(regs_.general[d.r1],storage_.read_word(ea)); return{StepState::Executed,first,"CL"};
    case 0x56: regs_.general[d.r1]|=storage_.read_word(ea); regs_.condition_code=condition_code_logical(regs_.general[d.r1]); return{StepState::Executed,first,"O"};
    case 0x57: regs_.general[d.r1]^=storage_.read_word(ea); regs_.condition_code=condition_code_logical(regs_.general[d.r1]); return{StepState::Executed,first,"X"};
    case 0x58: regs_.general[d.r1]=storage_.read_word(ea); return{StepState::Executed,first,"L"};
    case 0x59: regs_.condition_code=compare32(regs_.general[d.r1],storage_.read_word(ea)); return{StepState::Executed,first,"C"};
    case 0x5A: { const auto x=add32(regs_.general[d.r1],storage_.read_word(ea)); regs_.general[d.r1]=x.value; regs_.condition_code=x.condition_code; return{StepState::Executed,first,"A"}; }
    case 0x5B: { const auto x=subtract32(regs_.general[d.r1],storage_.read_word(ea)); regs_.general[d.r1]=x.value; regs_.condition_code=x.condition_code; return{StepState::Executed,first,"S"}; }
    default: return{StepState::IllegalInstruction,first,"RX opcode is catalogued but not implemented in this CPU milestone"};
   }
  }
  return{StepState::IllegalInstruction,first,"Unsupported instruction format"};
 } catch(const std::out_of_range&) { return{StepState::MemoryFault,0,"Instruction or operand access outside storage"}; }
}
}