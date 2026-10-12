#include "ibmlegacy/devices/ibm1402_reader.hpp"
#include <utility>
namespace ibmlegacy::devices {
void VirtualIBM1402Reader::load_deck(CardDeck d){deck_=std::move(d);position_=0;status_=deck_.cards().empty()?DeviceStatus::EndOfTape:DeviceStatus::Ready;}
std::optional<std::string> VirtualIBM1402Reader::read_card(){if(status_==DeviceStatus::NotReady)return{};if(position_>=deck_.cards().size()){status_=DeviceStatus::EndOfTape;return{};}status_=DeviceStatus::Ready;return deck_.cards()[position_++];}
void VirtualIBM1402Reader::reset(){position_=0;status_=deck_.cards().empty()?DeviceStatus::EndOfTape:DeviceStatus::Ready;}
DeviceStatus VirtualIBM1402Reader::status()const noexcept{return status_;}
std::string VirtualIBM1402Reader::name()const{return "IBM 1402 reader (virtual text model)";}
std::size_t VirtualIBM1402Reader::cards_remaining()const noexcept{return position_>=deck_.cards().size()?0:deck_.cards().size()-position_;}
}