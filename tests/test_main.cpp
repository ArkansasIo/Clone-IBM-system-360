#include "ibmlegacy/cpu/system360_opcodes.hpp"
#include "ibmlegacy/devices/card_deck.hpp"
#include "ibmlegacy/devices/channel.hpp"
#include "ibmlegacy/devices/line_printer.hpp"
#include "ibmlegacy/devices/tape_drive.hpp"
#include "ibmlegacy/devices/tape_models.hpp"
#include "ibmlegacy/machines/ebcdic.hpp"
#include "ibmlegacy/runtime/hex_loader.hpp"
#include "ibmlegacy/runtime/machine_profiles.hpp"
#include "ibmlegacy/machines/ibm1401.hpp"
#include "ibmlegacy/machines/ibm1401_opcodes.hpp"
#include "ibmlegacy/machines/system360.hpp"
#include "ibmlegacy/machines/system360_psw.hpp"
#include "ibmlegacy/tape/tape_image.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>
#include <fstream>
int main(){
 using namespace ibmlegacy;
 machines::IBM1401Memory m(100);m.load_ascii(5,"TEST");assert(m.dump_ascii(5,4)=="TEST");
 machines::System360Storage s(64);s.write_word(4,0x12345678U);assert(s.read_word(4)==0x12345678U);
 auto p=std::filesystem::temp_directory_path()/"ibm360-test.vmt";tape::TapeImage t;t.append_record({'A','B'});t.append_tape_mark();t.save(p);auto x=tape::TapeImage::load(p);assert(x.records().size()==2);assert(x.records()[1].tape_mark);
 devices::VirtualTapeDrive d;d.mount(p);auto rec=d.read_forward();assert(rec&&rec->bytes.size()==2);
 devices::CardDeck deck;deck.add("HELLO");assert(deck.cards()[0].size()==80);
 devices::VirtualLinePrinter printer;printer.print_line("hello");assert(printer.output().size()==1);
 devices::VirtualChannel channel;channel.submit({0x02,0,10,0x100});assert(channel.has_pending());assert(channel.next().count==10);channel.complete(devices::ChannelStatus::DeviceEnd,0,"ok");assert(channel.last_result().status==devices::ChannelStatus::DeviceEnd);
 assert(machines::ascii_to_ebcdic('A')==0xC1);assert(machines::ebcdic_to_ascii(0xF5)=='5');assert(machines::ebcdic_bytes_to_ascii(machines::ascii_to_ebcdic_bytes("A9"))=="A9");
 auto hexfile=std::filesystem::temp_directory_path()/"ibm360-test.hex";{std::ofstream hf(hexfile);hf<<"18 12 1A 12\n";;}machines::System360Storage loaded(32);auto load=runtime::load_hex_program(loaded,hexfile);assert(load.success&&load.bytes_loaded==4);assert(loaded.read_byte(0)==0x18);std::filesystem::remove(hexfile);
 auto t729=devices::ibm729_model_ii_profile();assert(t729.model.find("729")!=std::string::npos);auto t2400=devices::ibm2401_profile();assert(t2400.model.find("2401")!=std::string::npos);auto p1401=runtime::ibm1401_4k_profile();assert(p1401.storage_size==4000);auto p360=runtime::system360_model30_profile();assert(p360.kind==runtime::MachineKind::System360);assert(machines::ibm1401_opcode_reference[0].mnemonic=="A");
 assert(cpu::find_system360_opcode(0x18)!=nullptr);assert(cpu::find_system360_opcode(0xFF)==nullptr);
 machines::System360PSW psw;psw.set_condition_code(7);assert(psw.condition_code==3);
 std::filesystem::remove(p);std::cout<<"All tests passed\n";
}
