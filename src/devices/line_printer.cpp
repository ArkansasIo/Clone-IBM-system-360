#include "ibmlegacy/devices/line_printer.hpp"
#include <fstream>
#include <stdexcept>
#include <utility>
namespace ibmlegacy::devices {
void VirtualLinePrinter::print_line(std::string l){lines_.push_back(std::move(l));}
void VirtualLinePrinter::form_feed(){lines_.emplace_back("\f");}
const std::vector<std::string>& VirtualLinePrinter::output()const noexcept{return lines_;}
void VirtualLinePrinter::save(const std::filesystem::path&p)const{std::ofstream o(p);if(!o)throw std::runtime_error("Cannot write printer output");for(auto&l:lines_)o<<l<<'\n';}
}