#include "ibmlegacy/cpu/system360_cpu.hpp"
#include <stdexcept>
namespace ibmlegacy::cpu {
System360Cpu::System360Cpu(machines::System360Storage&s):storage_(s){}
machines::System360Registers& System360Cpu::registers()noexcept{return regs_;}
const machines::System360Registers& System360Cpu::registers()const noexcept{return regs_;}
void System360Cpu::reset()noexcept{regs_={};}
StepResult System360Cpu::step(){auto pc=regs_.instruction_address;try{auto op=storage_.read_byte(pc);if(op!=0x18&&op!=0x1A&&op!=0x05&&op!=0x07)return{StepState::IllegalInstruction,op,"Unsupported opcode in educational System/360 subset"};auto rb=storage_.read_byte(pc+1);unsigned r1=(rb>>4U)&15U,r2=rb&15U;regs_.instruction_address+=2;if(op==0x18){regs_.general[r1]=regs_.general[r2];return{StepState::Executed,op,"LR"};}if(op==0x1A){regs_.general[r1]+=regs_.general[r2];auto v=regs_.general[r1];regs_.condition_code=v==0?0:((v&0x80000000U)?1:2);return{StepState::Executed,op,"AR"};}if(op==0x05){regs_.general[r1]=regs_.instruction_address;if(r2)regs_.instruction_address=regs_.general[r2];return{StepState::Executed,op,"BALR"};}unsigned mask=r1;bool take=(mask&(1U<<(3U-regs_.condition_code)))!=0;if(take&&r2)regs_.instruction_address=regs_.general[r2];return{StepState::Executed,op,"BCR"};}catch(const std::out_of_range&){return{StepState::MemoryFault,0,"Instruction fetch outside storage"};}}
}