#include "ibmlegacy/devices/card_deck.hpp"
#include <fstream>
#include <stdexcept>
#include <utility>
namespace ibmlegacy::devices {
void CardDeck::add(std::string c){if(c.size()>columns)throw std::invalid_argument("Card exceeds 80 columns");c.resize(columns,' ');cards_.push_back(std::move(c));}
const std::vector<std::string>& CardDeck::cards()const noexcept{return cards_;}
void CardDeck::save_text(const std::filesystem::path&p)const{std::ofstream o(p);if(!o)throw std::runtime_error("Cannot write card deck");for(auto&c:cards_)o<<c<<'\n';}
CardDeck CardDeck::load_text(const std::filesystem::path&p){std::ifstream i(p);if(!i)throw std::runtime_error("Cannot read card deck");CardDeck d;std::string l;while(std::getline(i,l))d.add(l);return d;}
}