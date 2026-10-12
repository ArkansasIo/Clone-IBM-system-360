#include "ibmlegacy/machines/ebcdic.hpp"
namespace ibmlegacy::machines {
std::uint8_t ascii_to_ebcdic(char c)noexcept{
 if(c>='0'&&c<='9')return static_cast<std::uint8_t>(0xF0+(c-'0'));
 if(c>='A'&&c<='I')return static_cast<std::uint8_t>(0xC1+(c-'A'));
 if(c>='J'&&c<='R')return static_cast<std::uint8_t>(0xD1+(c-'J'));
 if(c>='S'&&c<='Z')return static_cast<std::uint8_t>(0xE2+(c-'S'));
 if(c>='a'&&c<='i')return static_cast<std::uint8_t>(0x81+(c-'a'));
 if(c>='j'&&c<='r')return static_cast<std::uint8_t>(0x91+(c-'j'));
 if(c>='s'&&c<='z')return static_cast<std::uint8_t>(0xA2+(c-'s'));
 if(c==' ')return 0x40;if(c=='.')return 0x4B;if(c==',')return 0x6B;if(c=='-')return 0x60;if(c=='/')return 0x61;if(c=='=')return 0x7E;
 return 0x6F;
}
char ebcdic_to_ascii(std::uint8_t b)noexcept{
 if(b>=0xF0&&b<=0xF9)return static_cast<char>('0'+b-0xF0);
 if(b>=0xC1&&b<=0xC9)return static_cast<char>('A'+b-0xC1);
 if(b>=0xD1&&b<=0xD9)return static_cast<char>('J'+b-0xD1);
 if(b>=0xE2&&b<=0xE9)return static_cast<char>('S'+b-0xE2);
 if(b>=0x81&&b<=0x89)return static_cast<char>('a'+b-0x81);
 if(b>=0x91&&b<=0x99)return static_cast<char>('j'+b-0x91);
 if(b>=0xA2&&b<=0xA9)return static_cast<char>('s'+b-0xA2);
 switch(b){case 0x40:return ' ';case 0x4B:return '.';case 0x6B:return ',';case 0x60:return '-';case 0x61:return '/';case 0x7E:return '=';default:return '?';}
}
std::string ascii_to_ebcdic_bytes(std::string_view s){std::string o;o.reserve(s.size());for(char c:s)o.push_back(static_cast<char>(ascii_to_ebcdic(c)));return o;}
std::string ebcdic_bytes_to_ascii(std::string_view s){std::string o;o.reserve(s.size());for(unsigned char c:s)o.push_back(ebcdic_to_ascii(c));return o;}
}