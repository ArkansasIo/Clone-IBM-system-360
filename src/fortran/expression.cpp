#include "ibmlegacy/fortran/expression.hpp"
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <map>
#include <string>
namespace ibmlegacy::fortran {
namespace {
class Parser {
public:
 Parser(const std::string&s,const std::map<std::string,double>&v):s_(s),vars_(v){}
 ExpressionResult run(){try{double x=expr();space();if(pos_!=s_.size())return{false,0,"Unexpected token at column "+std::to_string(pos_+1)};return{true,x,{}};}catch(const std::string&e){return{false,0,e};}}
private:
 const std::string&s_;const std::map<std::string,double>&vars_;std::size_t pos_{0};
 void space(){while(pos_<s_.size()&&std::isspace(static_cast<unsigned char>(s_[pos_])))++pos_;}
 bool take(char c){space();if(pos_<s_.size()&&s_[pos_]==c){++pos_;return true;}return false;}
 double expr(){double x=term();for(;;){if(take('+'))x+=term();else if(take('-'))x-=term();else return x;}}
 double term(){double x=power();for(;;){if(take('*'))x*=power();else if(take('/')){double y=power();if(y==0)throw std::string("Division by zero");x/=y;}else return x;}}
 double power(){double x=unary();if(take('*')){if(!take('*'))throw std::string("Expected ** exponent operator");x=std::pow(x,power());}return x;}
 double unary(){if(take('+'))return unary();if(take('-'))return -unary();return atom();}
 double atom(){space();if(take('(')){double x=expr();if(!take(')'))throw std::string("Missing closing parenthesis");return x;}
  if(pos_>=s_.size())throw std::string("Expected expression value");
  if(std::isdigit(static_cast<unsigned char>(s_[pos_]))||s_[pos_]=='.'){const char*begin=s_.c_str()+pos_;char*end=nullptr;double x=std::strtod(begin,&end);if(end==begin)throw std::string("Invalid numeric literal");pos_=static_cast<std::size_t>(end-s_.c_str());if(pos_<s_.size()&&(s_[pos_]=='D'||s_[pos_]=='d')){++pos_;}return x;}
  if(std::isalpha(static_cast<unsigned char>(s_[pos_]))){std::size_t start=pos_++;while(pos_<s_.size()&&(std::isalnum(static_cast<unsigned char>(s_[pos_]))||s_[pos_]=='_'))++pos_;std::string name=s_.substr(start,pos_-start);for(char&c:name)c=static_cast<char>(std::toupper(static_cast<unsigned char>(c)));auto i=vars_.find(name);if(i==vars_.end())throw std::string("Undefined variable: ")+name;return i->second;}
  throw std::string("Unexpected character at column ")+std::to_string(pos_+1);
 }
};
}
ExpressionResult evaluate_numeric_expression(const std::string&s,const std::map<std::string,double>&v){return Parser(s,v).run();}
}