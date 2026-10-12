#include "ibmlegacy/cpu/ibm1401_cpu.hpp"
#include <stdexcept>
namespace ibmlegacy::cpu {
IBM1401Cpu::IBM1401Cpu(machines::IBM1401Memory&m):memory_(m){}
std::size_t IBM1401Cpu::instruction_address()const noexcept{return instruction_address_;}
void IBM1401Cpu::set_instruction_address(std::size_t a){if(a>=memory_.size())throw std::out_of_range("1401 instruction address");instruction_address_=a;}
StepResult IBM1401Cpu::step(){try{auto c=memory_.read(instruction_address_);return{StepState::IllegalInstruction,c.code,"IBM 1401 decoding not implemented yet"};}catch(const std::out_of_range&){return{StepState::MemoryFault,0,"1401 fetch outside storage"};}}
void IBM1401Cpu::reset()noexcept{instruction_address_=0;}
}