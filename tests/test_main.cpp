#include "ibmlegacy/cpu/system360_opcodes.hpp"
#include "ibmlegacy/cpu/system360_alu.hpp"
#include "ibmlegacy/cpu/system360_decoder.hpp"
#include "ibmlegacy/cpu/system360_cpu.hpp"
#include "ibmlegacy/assembler/lexer.hpp"
#include "ibmlegacy/assembler/encoder.hpp"
#include "ibmlegacy/devices/card_deck.hpp"
#include "ibmlegacy/devices/device_bus.hpp"
#include "ibmlegacy/devices/ibm1402_reader.hpp"
#include "ibmlegacy/devices/ibm1403_printer.hpp"
#include "ibmlegacy/devices/ibm2540_reader_punch.hpp"
#include "ibmlegacy/devices/channel.hpp"
#include "ibmlegacy/devices/line_printer.hpp"
#include "ibmlegacy/devices/tape_drive.hpp"
#include "ibmlegacy/devices/tape_models.hpp"
#include "ibmlegacy/machines/ebcdic.hpp"
#include "ibmlegacy/runtime/hex_loader.hpp"
#include "ibmlegacy/runtime/binary_loader.hpp"
#include "ibmlegacy/runtime/machine_profiles.hpp"
#include "ibmlegacy/fortran/source_reader.hpp"
#include "ibmlegacy/fortran/fortran_compiler.hpp"
#include "ibmlegacy/fortran/lexer.hpp"
#include "ibmlegacy/fortran/symbol_table.hpp"
#include "ibmlegacy/fortran/intrinsics.hpp"
#include "ibmlegacy/fortran/runtime_io.hpp"
#include "ibmlegacy/fortran/runtime_math.hpp"
#include "ibmlegacy/fortran/format_descriptor.hpp"
#include "ibmlegacy/fortran/expression.hpp"
#include "ibmlegacy/fortran/diagnostic.hpp"
#include "ibmlegacy/fortran/array.hpp"
#include "ibmlegacy/runtime/trace_logger.hpp"
#include "ibmlegacy/machines/ibm1401.hpp"
#include "ibmlegacy/machines/ibm1401_opcodes.hpp"
#include "ibmlegacy/machines/system360.hpp"
#include "ibmlegacy/machines/system360_psw.hpp"
#include "ibmlegacy/tape/tape_image.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
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
 auto hexfile=std::filesystem::temp_directory_path()/"ibm360-test.hex";{std::ofstream hf(hexfile);hf<<"18 12 1A 12\n";}machines::System360Storage loaded(32);auto load=runtime::load_hex_program(loaded,hexfile);assert(load.success&&load.bytes_loaded==4);assert(loaded.read_byte(0)==0x18);std::filesystem::remove(hexfile);auto binfile=std::filesystem::temp_directory_path()/"ibm360-test.bin";{std::ofstream bf(binfile,std::ios::binary);bf.put(static_cast<char>(0x18));bf.put(static_cast<char>(0x12));}machines::System360Storage binaryStorage(16);auto binLoad=runtime::load_binary_program(binaryStorage,binfile);assert(binLoad.success&&binLoad.bytes_loaded==2&&binaryStorage.read_byte(1)==0x12);std::filesystem::remove(binfile);
 auto t729=devices::ibm729_model_ii_profile();assert(t729.model.find("729")!=std::string::npos);auto t2400=devices::ibm2401_profile();assert(t2400.model.find("2401")!=std::string::npos);auto p1401=runtime::ibm1401_4k_profile();assert(p1401.storage_size==4000);auto p360=runtime::system360_model30_profile();assert(p360.kind==runtime::MachineKind::System360);assert(machines::ibm1401_opcode_reference[0].mnemonic=="A");
 auto fsource=std::filesystem::temp_directory_path()/"ibm360-fixed.f";{std::ofstream fs(fsource);fs<<"      PROGRAM T\n      INTEGER I\n      I = 7\n      PRINT *, I\n      END\n";}auto fr=fortran::read_fixed_form_source(fsource);assert(fr.success&&fr.records.size()==4&&fr.records[1].statement.find("INTEGER")!=std::string::npos);fortran::FortranCompiler fc;auto generated=fc.emit_cpp(fsource);assert(generated.success);assert(generated.output.find("I = 7;")<generated.output.find("std::cout"));std::filesystem::remove(fsource);
 machines::System360Storage cpuStorage(32);cpuStorage.write_byte(0,0x18);cpuStorage.write_byte(1,0x12);cpuStorage.write_byte(2,0x1A);cpuStorage.write_byte(3,0x12);cpu::System360Cpu cpu360(cpuStorage);cpu360.registers().general[2]=42;auto step1=cpu360.step();assert(step1.state==cpu::StepState::Executed&&cpu360.registers().general[1]==42&&cpu360.registers().instruction_address==2);cpu360.registers().general[2]=8;auto step2=cpu360.step();assert(step2.state==cpu::StepState::Executed&&cpu360.registers().general[1]==50);
 auto ftokens=fortran::lex_statement("A = 2 ** 3 + 4");assert(ftokens.diagnostics.empty()&&ftokens.tokens.size()>=6);
 auto fx=fortran::evaluate_numeric_expression("2 ** 3 + X * 2",{{"X",4.0}});assert(fx.success&&fx.value==16.0);auto fxerr=fortran::evaluate_numeric_expression("1/0");assert(!fxerr.success);
 fortran::SymbolTable symbols;assert(symbols.declare({"total",fortran::TypeKind::Integer,true,{}}));assert(symbols.find("TOTAL")!=nullptr);assert(!symbols.declare({"TOTAL",fortran::TypeKind::Real,true,{}}));
 std::string ierr;auto iv=fortran::evaluate_intrinsic("SQRT",{{fortran::TypeKind::Real,81.0}},ierr);assert(iv&&std::get<double>(iv->value)==9.0);
 auto fmt=fortran::parse_format_specification("(I5,F8.2,E12.4)");assert(fmt.success&&fmt.descriptors.size()==3);auto fmtbad=fortran::parse_format_specification("(Q8)");assert(!fmtbad.success);
 assert(fortran::runtime::dsqrt(16.0)==4.0);
 std::ostringstream ioout;std::istringstream ioin("abc 123");fortran::FortranRuntimeIO fio(ioin,ioout);fio.write_record("record");std::string inputRecord;assert(fio.read_record(inputRecord)&&inputRecord=="abc 123");fio.print_list({"A","B"});assert(ioout.str()=="record\nA B\n");
 fortran::DiagnosticBag db;db.error({"test.f",4,7},"F0001","bad token");assert(db.has_errors()&&db.format().find("test.f:4:7")!=std::string::npos);
 fortran::NumericArray1D fa(1,5,fortran::TypeKind::Integer);assert(fa.size()==5&&fa.set(3,7.9)&&fa.get(3).value()==7.0&&!fa.set(0,1));fortran::NumericArray1D badArray(10,2);assert(!badArray.error().empty());
 auto add=cpu::add32(1,2);assert(add.value==3&&add.condition_code==2&&!add.overflow);auto dec=cpu::decode_rr(0x18,0x12);assert(dec.info&&dec.r1==1&&dec.r2==2);
 auto asmline=assembler::parse_assembler_line("LOOP LR R1,R2",1);assert(asmline.success&&asmline.line.label=="LOOP"&&asmline.line.mnemonic=="LR");auto enc=assembler::encode_rr_subset(asmline.line);assert(enc.success&&enc.bytes.size()==2&&enc.bytes[0]==0x18);
 devices::VirtualIBM1402Reader reader;reader.load_deck(deck);auto card=reader.read_card();assert(card&&card->substr(0,5)=="HELLO");assert(reader.cards_remaining()==0);
 devices::VirtualIBM1403Printer p1403;p1403.print("test line");assert(p1403.printer().output().size()==1);
 devices::VirtualIBM2540ReaderPunch rp;rp.load_input(deck);assert(rp.read_card().has_value());rp.punch_card("PUNCHED");assert(rp.punched_cards().cards().size()==1);
 auto tracefile=std::filesystem::temp_directory_path()/"ibm360-trace.log";{runtime::TraceLogger logger(tracefile);assert(logger.good());logger.write("TEST","trace event");}assert(std::filesystem::file_size(tracefile)>0);std::filesystem::remove(tracefile);
 devices::DeviceBus bus;auto busPrinter=std::make_shared<devices::VirtualIBM1403Printer>();assert(bus.attach("00E",busPrinter));assert(bus.find("00E")!=nullptr&&bus.size()==1);assert(bus.detach("00E"));
 assert(cpu::find_system360_opcode(0x18)!=nullptr);assert(cpu::find_system360_opcode(0xFF)==nullptr);
 machines::System360PSW psw;psw.set_condition_code(7);assert(psw.condition_code==3);
 std::filesystem::remove(p);std::cout<<"All tests passed\n";
}
