#include "ibmlegacy/devices/ibm2540_reader_punch.hpp"
#include <utility>
namespace ibmlegacy::devices {
void VirtualIBM2540ReaderPunch::load_input(CardDeck d){input_=std::move(d);input_position_=0;status_=input_.cards().empty()?DeviceStatus::EndOfTape:DeviceStatus::Ready;}
std::optional<std::string> VirtualIBM2540ReaderPunch::read_card(){if(status_==DeviceStatus::NotReady)return{};if(input_position_>=input_.cards().size()){status_=DeviceStatus::EndOfTape;return{};}status_=DeviceStatus::Ready;return input_.cards()[input_position_++];}
void VirtualIBM2540ReaderPunch::punch_card(std::string card){punched_.add(std::move(card));status_=DeviceStatus::Ready;}
const CardDeck& VirtualIBM2540ReaderPunch::punched_cards()const noexcept{return punched_;}
void VirtualIBM2540ReaderPunch::reset(){input_position_=0;status_=input_.cards().empty()?DeviceStatus::EndOfTape:DeviceStatus::Ready;}
DeviceStatus VirtualIBM2540ReaderPunch::status()const noexcept{return status_;}
std::string VirtualIBM2540ReaderPunch::name()const{return "IBM 2540 reader/punch (virtual text model)";}
}