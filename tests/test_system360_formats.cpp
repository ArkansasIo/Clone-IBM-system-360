#include "ibmlegacy/cpu/system360_decoder.hpp"
#include "ibmlegacy/cpu/system360_opcodes.hpp"
#include <cassert>
int main(){
 using namespace ibmlegacy::cpu;
 auto rr=decode_rr(0x18,0x23);assert(rr.format==InstructionFormat::RR&&rr.r1==2&&rr.r2==3);
 auto rx=decode_rx(0x41,0x23,0x45,0x67);assert(rx.format==InstructionFormat::RX&&rx.r1==2&&rx.x2==3&&rx.b2==4&&rx.d2==0x567);
 auto rs=decode_rs(0x90,0x2F,0x31,0x23);assert(rs.format==InstructionFormat::RS&&rs.r1==2&&rs.r3==15&&rs.b2==3&&rs.d2==0x123);
 auto si=decode_si(0x92,0xAA,0xB1,0x23);assert(si.format==InstructionFormat::SI&&si.i2==0xAA&&si.b1==0xB&&si.d1==0x123);
 auto ss=decode_ss(0xD2,0xF2,0x31,0x23,0x45,0x67);assert(ss.format==InstructionFormat::SS&&ss.l1==15&&ss.l2==2&&ss.b1==3&&ss.d1==0x123&&ss.b2==4&&ss.d2==0x567);
 return 0;
}
