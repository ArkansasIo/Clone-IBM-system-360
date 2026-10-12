#include "ibmlegacy/devices/card_deck.hpp"
#include "ibmlegacy/devices/line_printer.hpp"
#include "ibmlegacy/devices/tape_drive.hpp"
#include "ibmlegacy/machines/ibm1401.hpp"
#include "ibmlegacy/machines/system360.hpp"
#include "ibmlegacy/tape/tape_image.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>
int main(){using namespace ibmlegacy;machines::IBM1401Memory m(100);m.load_ascii(5,"TEST");assert(m.dump_ascii(5,4)=="TEST");machines::System360Storage s(64);s.write_word(4,0x12345678U);assert(s.read_word(4)==0x12345678U);auto p=std::filesystem::temp_directory_path()/"ibm360-test.vmt";tape::TapeImage t;t.append_record({'A','B'});t.append_tape_mark();t.save(p);auto x=tape::TapeImage::load(p);assert(x.records().size()==2);devices::VirtualTapeDrive d;d.mount(p);assert(d.read_forward()->bytes.size()==2);devices::CardDeck deck;deck.add("HELLO");assert(deck.cards()[0].size()==80);devices::VirtualLinePrinter printer;printer.print_line("hello");assert(printer.output().size()==1);std::filesystem::remove(p);std::cout<<"All tests passed\n";}