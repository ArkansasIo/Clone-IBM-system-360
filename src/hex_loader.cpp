#include "ibmlegacy/runtime/hex_loader.hpp"
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
namespace ibmlegacy::runtime {
LoadResult load_hex_program(machines::System360Storage& storage,const std::filesystem::path& file,std::size_t start){
 std::ifstream in(file);if(!in)return{false,0,"Cannot open hex program: "+file.string()};
 std::size_t address=start,count=0;std::string token;
 while(in>>token){
  if(token.starts_with("#")||token.starts_with(";")){std::string rest;std::getline(in,rest);continue;}
  if(token.size()!=2)return{false,count,"Each token must be exactly two hex digits: "+token};
  auto digit=[](char c)->int{if(c>='0'&&c<='9')return c-'0';c=static_cast<char>(std::toupper(static_cast<unsigned char>(c)));if(c>='A'&&c<='F')return c-'A'+10;return -1;};
  int hi=digit(token[0]),lo=digit(token[1]);if(hi<0||lo<0)return{false,count,"Invalid hexadecimal byte: "+token};
  if(address>=storage.size())return{false,count,"Program exceeds configured storage"};
  storage.write_byte(address++,static_cast<unsigned char>((hi<<4)|lo));++count;
 }
 return{true,count,{}};
}
}