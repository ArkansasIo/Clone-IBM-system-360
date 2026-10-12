#include "ibmlegacy/machines/system360.hpp"
#include <stdexcept>
namespace ibmlegacy::machines {
System360Storage::System360Storage(std::size_t n):bytes_(n){if(n<4)throw std::invalid_argument("System/360 storage too small");}
std::size_t System360Storage::size()const noexcept{return bytes_.size();}
std::uint8_t System360Storage::read_byte(std::size_t a)const{if(a>=bytes_.size())throw std::out_of_range("storage read");return bytes_[a];}
void System360Storage::write_byte(std::size_t a,std::uint8_t v){if(a>=bytes_.size())throw std::out_of_range("storage write");bytes_[a]=v;}
std::uint32_t System360Storage::read_word(std::size_t a)const{if(a%4)throw std::invalid_argument("word alignment");if(a>bytes_.size()||bytes_.size()-a<4)throw std::out_of_range("word read");return(std::uint32_t(bytes_[a])<<24U)|(std::uint32_t(bytes_[a+1])<<16U)|(std::uint32_t(bytes_[a+2])<<8U)|bytes_[a+3];}
void System360Storage::write_word(std::size_t a,std::uint32_t v){if(a%4)throw std::invalid_argument("word alignment");if(a>bytes_.size()||bytes_.size()-a<4)throw std::out_of_range("word write");bytes_[a]=static_cast<std::uint8_t>(v>>24U);bytes_[a+1]=static_cast<std::uint8_t>(v>>16U);bytes_[a+2]=static_cast<std::uint8_t>(v>>8U);bytes_[a+3]=static_cast<std::uint8_t>(v);}
}
