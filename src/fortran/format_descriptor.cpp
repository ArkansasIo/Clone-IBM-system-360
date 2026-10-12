#include "ibmlegacy/fortran/format_descriptor.hpp"
#include <cctype>
#include <string>
namespace ibmlegacy::fortran {
FormatParseResult parse_format_specification(const std::string&s){
 FormatParseResult r;std::size_t i=0;while(i<s.size()&&std::isspace(static_cast<unsigned char>(s[i])))++i;if(i<s.size()&&s[i]=='(')++i;
 while(i<s.size()){while(i<s.size()&&(std::isspace(static_cast<unsigned char>(s[i]))||s[i]==','))++i;if(i>=s.size()||s[i]==')')break;std::size_t repeat=0;while(i<s.size()&&std::isdigit(static_cast<unsigned char>(s[i])))repeat=repeat*10+static_cast<unsigned>(s[i++]-'0');if(!repeat)repeat=1;if(i>=s.size()){r.diagnostic="Expected format descriptor";return r;}char c=static_cast<char>(std::toupper(static_cast<unsigned char>(s[i++])));
  FormatDescriptor d;d.repeat=repeat;
  if(c=='I')d.kind=FormatKind::Integer;else if(c=='F')d.kind=FormatKind::FixedReal;else if(c=='E'||c=='D')d.kind=FormatKind::Exponential;else if(c=='A')d.kind=FormatKind::Character;else if(c=='/') {d.kind=FormatKind::Slash;r.descriptors.push_back(d);continue;}else if(c=='X'){d.kind=FormatKind::Literal;r.descriptors.push_back(d);continue;}else {r.diagnostic=std::string("Unsupported format descriptor: ")+c;return r;}
  while(i<s.size()&&std::isdigit(static_cast<unsigned char>(s[i])))d.width=d.width*10+static_cast<unsigned>(s[i++]-'0');if(i<s.size()&&s[i]=='.'){++i;while(i<s.size()&&std::isdigit(static_cast<unsigned char>(s[i])))d.precision=d.precision*10+static_cast<unsigned>(s[i++]-'0');}
  if(!d.width){r.diagnostic="Descriptor width is required";return r;}r.descriptors.push_back(d);
 }
 r.success=true;return r;
}
}