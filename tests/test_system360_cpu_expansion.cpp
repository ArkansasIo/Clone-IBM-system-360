#include "ibmlegacy/cpu/system360_cpu.hpp"
#include <cassert>
#include <cstdint>
int main() {
 using namespace ibmlegacy;
 machines::System360Storage s(256);
 cpu::System360Cpu cpu(s);

 // RX: LA R1,100(R0,R0)
 s.write_byte(0,0x41); s.write_byte(1,0x10); s.write_byte(2,0x00); s.write_byte(3,100);
 assert(cpu.step().state==cpu::StepState::Executed);
 assert(cpu.registers().general[1]==100);

 // RX: ST R1,104(R0,R0), then L R2,104(R0,R0)
 s.write_byte(4,0x50); s.write_byte(5,0x20); s.write_byte(6,0x00); s.write_byte(7,104);
 s.write_byte(8,0x58); s.write_byte(9,0x20); s.write_byte(10,0x00); s.write_byte(11,104);
 cpu.registers().general[1]=0x12345678U;
 assert(cpu.step().state==cpu::StepState::Executed);
 assert(s.read_word(104)==0x12345678U);
 assert(cpu.step().state==cpu::StepState::Executed);
 assert(cpu.registers().general[2]==0x12345678U);

 // RR: CR R1,R2 and BC mask=2 (branch on high).
 s.write_byte(12,0x19); s.write_byte(13,0x12);
 s.write_byte(14,0x47); s.write_byte(15,0x20); s.write_byte(16,0x00); s.write_byte(17,32);
 cpu.registers().general[1]=5; cpu.registers().general[2]=3;
 assert(cpu.step().state==cpu::StepState::Executed);
 assert(cpu.registers().condition_code==2);
 assert(cpu.step().state==cpu::StepState::Executed);
 assert(cpu.registers().instruction_address==32);

 // RX: BCT decrements and branches until zero.
 cpu.registers().instruction_address=20; cpu.registers().general[3]=2;
 s.write_byte(20,0x46); s.write_byte(21,0x30); s.write_byte(22,0x00); s.write_byte(23,20);
 assert(cpu.step().state==cpu::StepState::Executed);
 assert(cpu.registers().general[3]==1 && cpu.registers().instruction_address==20);
 cpu.registers().instruction_address=20;
 assert(cpu.step().state==cpu::StepState::Executed);
 assert(cpu.registers().general[3]==0 && cpu.registers().instruction_address==24);
 return 0;
}
