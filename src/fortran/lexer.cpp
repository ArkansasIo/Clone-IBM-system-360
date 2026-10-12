#include "ibmlegacy/fortran/lexer.hpp"
#include <cctype>
#include <utility>
namespace ibmlegacy::fortran {
LexedLine lex_statement(std::string_view s,std::string file,std::size_t line,std::size_t base){
 LexedLine out;std::size_t i=0;
 auto push=[&](TokenKind k,std::size_t start,std::size_t end){out.tokens.push_back({k,std::string(s.substr(start,end-start)),{file,line,base+start}});};
 while(i<s.size()){unsigned char c=static_cast<unsigned char>(s[i]);if(std::isspace(c)){++i;continue;}std::size_t start=i;
  if(std::isalpha(c)||c=='_'){++i;while(i<s.size()){auto q=static_cast<unsigned char>(s[i]);if(!std::isalnum(q)&&q!='_')break;++i;}push(TokenKind::Identifier,start,i);continue;}
  if(std::isdigit(c)){bool real=false;++i;while(i<s.size()&&std::isdigit(static_cast<unsigned char>(s[i])))++i;if(i<s.size()&&s[i]=='.'){real=true;++i;while(i<s.size()&&std::isdigit(static_cast<unsigned char>(s[i])))++i;}if(i<s.size()&&(s[i]=='E'||s[i]=='e'||s[i]=='D'||s[i]=='d')){real=true;++i;if(i<s.size()&&(s[i]=='+'||s[i]=='-'))++i;while(i<s.size()&&std::isdigit(static_cast<unsigned char>(s[i])))++i;}push(real?TokenKind::RealLiteral:TokenKind::IntegerLiteral,start,i);continue;}
  if(c=='\\''||c=='"'){char quote=static_cast<char>(c);++i;bool terminated=false;while(i<s.size()){if(s[i]==quote){if(i+1<s.size()&&s[i+1]==quote){i+=2;continue;}++i;terminated=true;break;}++i;}if(!terminated)out.diagnostics.push_back({Severity::Error,{file,line,base+start},"FLEX001","Unterminated character literal"});push(TokenKind::StringLiteral,start,i);continue;}
  ++i;switch(c){case '+':push(TokenKind::Plus,start,i);break;case '-':push(TokenKind::Minus,start,i);break;case '*':if(i<s.size()&&s[i]=='*'){++i;push(TokenKind::Power,start,i);}else push(TokenKind::Star,start,i);break;case '/':if(i<s.size()&&s[i]=='='){++i;push(TokenKind::Relational,start,i);}else push(TokenKind::Slash,start,i);break;case '(':push(TokenKind::LeftParen,start,i);break;case ')':push(TokenKind::RightParen,start,i);break;case ',':push(TokenKind::Comma,start,i);break;case '=':push(TokenKind::Equals,start,i);break;case '<':case '>':push(TokenKind::Relational,start,i);break;default:out.diagnostics.push_back({Severity::Error,{file,line,base+start},"FLEX002","Unsupported character"});push(TokenKind::Invalid,start,i);break;}
 }
 out.tokens.push_back({TokenKind::EndOfLine,"",{file,line,base+s.size()}});return out;
}
}