#include "ibmlegacy/assembler/lexer.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
namespace ibmlegacy::assembler {
namespace {std::string trim(std::string s){auto n=[](unsigned char c){return !std::isspace(c);};s.erase(s.begin(),std::find_if(s.begin(),s.end(),n));s.erase(std::find_if(s.rbegin(),s.rend(),n).base(),s.end());return s;}std::string upper(std::string s){for(auto&c:s)c=static_cast<char>(std::toupper(static_cast<unsigned char>(c)));return s;}}
LexResult parse_assembler_line(const std::string& source,std::size_t number){
 AssemblerLine out;out.line_number=number;auto text=source;auto star=text.find('*');if(star!=std::string::npos){out.comment=text.substr(star+1);text.resize(star);}text=trim(text);if(text.empty())return {true,out,{}};
 std::istringstream in(text);std::vector<std::string> words;std::string word;while(in>>word)words.push_back(word);if(words.empty())return {true,out,{}};
 std::size_t index=0;if(!source.empty()&&!std::isspace(static_cast<unsigned char>(source.front()))&&words.size()>1){out.label=upper(words[index++]);}
 if(index>=words.size())return {false,out,"Missing mnemonic at line "+std::to_string(number)};
 out.mnemonic=upper(words[index++]);std::string rest;for(;index<words.size();++index){if(!rest.empty())rest+=' ';rest+=words[index];}
 std::string operand;for(char c:rest){if(c==','){if(!operand.empty()){out.operands.push_back(trim(operand));operand.clear();}}else operand+=c;}if(!trim(operand).empty())out.operands.push_back(trim(operand));
 return {true,out,{}};
}
}