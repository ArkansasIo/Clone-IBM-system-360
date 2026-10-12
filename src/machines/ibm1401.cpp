#include "ibmlegacy/machines/ibm1401.hpp"
#include <stdexcept>
namespace ibmlegacy::machines {
IBM1401Memory::IBM1401Memory(std::size_t n):memory_(n){if(!n)throw std::invalid_argument("1401 memory must be non-empty");}
std::size_t IBM1401Memory::size()const noexcept{return memory_.size();}
Character1401 IBM1401Memory::read(std::size_t a)const{if(a>=memory_.size())throw std::out_of_range("1401 read");return memory_[a];}
void IBM1401Memory::write(std::size_t a,Character1401 v){if(a>=memory_.size())throw std::out_of_range("1401 write");memory_[a]=v;}
void IBM1401Memory::load_ascii(std::size_t a,const std::string&t){if(a>memory_.size()||t.size()>memory_.size()-a)throw std::out_of_range("1401 load");for(std::size_t i=0;i<t.size();++i)memory_[a+i]={static_cast<std::uint8_t>(t[i]),false};}
std::string IBM1401Memory::dump_ascii(std::size_t a,std::size_t n)const{if(a>memory_.size()||n>memory_.size()-a)throw std::out_of_range("1401 dump");std::string r;r.reserve(n);for(std::size_t i=a;i<a+n;++i)r.push_back(static_cast<char>(memory_[i].code));return r;}
}
