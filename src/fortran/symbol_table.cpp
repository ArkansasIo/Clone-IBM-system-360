#include "ibmlegacy/fortran/symbol_table.hpp"
#include <cctype>
#include <utility>
namespace ibmlegacy::fortran {
namespace {std::string key(std::string s){for(char&c:s)c=static_cast<char>(std::toupper(static_cast<unsigned char>(c)));return s;}}
bool SymbolTable::declare(Symbol s){s.name=key(std::move(s.name));const auto name=s.name;return symbols_.emplace(name,std::move(s)).second;}
Symbol* SymbolTable::find(const std::string&n){auto i=symbols_.find(key(n));return i==symbols_.end()?nullptr:&i->second;}
const Symbol* SymbolTable::find(const std::string&n)const{auto i=symbols_.find(key(n));return i==symbols_.end()?nullptr:&i->second;}
const std::map<std::string,Symbol>& SymbolTable::entries()const noexcept{return symbols_;}
void SymbolTable::clear()noexcept{symbols_.clear();}
}