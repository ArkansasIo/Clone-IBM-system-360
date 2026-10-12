#include "ibmlegacy/devices/ibm1403_printer.hpp"
#include <utility>
namespace ibmlegacy::devices {
void VirtualIBM1403Printer::print(std::string s){printer_.print_line(std::move(s));status_=DeviceStatus::Ready;}
void VirtualIBM1403Printer::advance_page(){printer_.form_feed();status_=DeviceStatus::Ready;}
const VirtualLinePrinter& VirtualIBM1403Printer::printer()const noexcept{return printer_;}
void VirtualIBM1403Printer::reset(){status_=DeviceStatus::Ready;}
DeviceStatus VirtualIBM1403Printer::status()const noexcept{return status_;}
std::string VirtualIBM1403Printer::name()const{return "IBM 1403 printer (virtual text model)";}
}