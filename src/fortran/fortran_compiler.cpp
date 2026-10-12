#include "ibmlegacy/fortran/fortran_compiler.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
namespace ibmlegacy::fortran {
namespace {
std::string trim(std::string s){auto ns=[](unsigned char c){return !std::isspace(c);};s.erase(s.begin(),std::find_if(s.begin(),s.end(),ns));s.erase(std::find_if(s.rbegin(),s.rend(),ns).base(),s.end());return s;}
std::string upper(std::string s){for(char&c:s)c=static_cast<char>(std::toupper(static_cast<unsigned char>(c)));return s;}
std::vector<std::string> statements(const std::filesystem::path&p,std::string&err){std::ifstream in(p);if(!in){err="Cannot open source file: "+p.string();return{};}std::vector<std::string> v;std::string l;while(std::getline(in,l)){if(l.empty())continue;if(l[0]=='C'||l[0]=='c'||l[0]=='*'||l[0]=='!')continue;if(l.size()<7)l.resize(7,' ');auto st=trim(l.substr(6,std::min<std::size_t>(66,l.size()-6)));if(st.empty())continue;if(l[5]!=' '&&l[5]!='0'){if(v.empty()){err="Continuation without prior statement";return{};}v.back()+=" "+st;}else v.push_back(st);}return v;}
}
CompileResult FortranCompiler::emit_cpp(const std::filesystem::path&p)const{
 std::string err;auto ss=statements(p,err);if(!err.empty())return{false,{},err};
 std::ostringstream declarations;std::vector<std::string> exec;
 for(const auto&s:ss){auto u=upper(s);if(u.rfind("PROGRAM ",0)==0||u=="END"||u=="STOP"||u=="STOP 0"||u=="CONTINUE")continue;
  std::string type;std::size_t varsStart=0;
  if(u.rfind("DOUBLE PRECISION ",0)==0){type="double";varsStart=17;}
  else if(u.rfind("INTEGER ",0)==0){type="long long";varsStart=8;}
  else if(u.rfind("REAL ",0)==0){type="double";varsStart=5;}
  else if(u.rfind("LOGICAL ",0)==0){type="bool";varsStart=8;}
  if(!type.empty()){std::stringstream vars(s.substr(varsStart));std::string var;declarations<<type<<" ";bool first=true;while(std::getline(vars,var,',')){var=trim(var);if(var.empty())continue;if(!first)declarations<<", ";declarations<<var<<"{}";first=false;}declarations<<";\n";continue;}
  if(u.rfind("PRINT",0)==0){auto pos=s.find(',');if(pos==std::string::npos)return{false,{},"Unsupported PRINT statement: "+s};auto args=trim(s.substr(pos+1));std::stringstream exprs(args);std::string e;std::ostringstream statement;statement<<"std::cout";while(std::getline(exprs,e,',')){e=trim(e);if(!e.empty())statement<<" << "<<e<<" << ' '";}statement<<" << '\\n';";exec.push_back(statement.str());continue;}
  if(u.rfind("WRITE",0)==0||u.rfind("READ",0)==0)return{false,{},"Formatted and unformatted I/O is not implemented: "+s};
  if(u.rfind("DO ",0)==0||u.rfind("GO TO ",0)==0||u.rfind("GOTO ",0)==0||u.rfind("IF ",0)==0)return{false,{},"Control-flow lowering not implemented for: "+s};
  auto eq=s.find('=');if(eq==std::string::npos)return{false,{},"Unsupported statement: "+s};exec.push_back(trim(s.substr(0,eq))+" = "+trim(s.substr(eq+1))+";");
 }
 std::ostringstream out;out<<"// Independent educational FORTRAN subset translation\n#include <iostream>\nint main(){\n"<<declarations.str();for(const auto&statement:exec)out<<"  "<<statement<<'\n';out<<"  return 0;\n}\n";return{true,out.str(),{}};
}
CompileResult FortranCompiler::emit_s360_listing(const std::filesystem::path&p)const{
 std::string err;auto ss=statements(p,err);if(!err.empty())return{false,{},err};std::ostringstream out;out<<"* Educational System/360 FORTRAN listing scaffold; NOT executable object code\n         PRINT NOGEN\n         START 0\n";
 for(const auto&s:ss){auto u=upper(s);if(u.rfind("PROGRAM ",0)==0)out<<"MAIN     DS    0H\n";else if(u=="END"||u=="STOP"||u=="STOP 0")out<<"         BR    14\n";else out<<"* LOWERING REQUIRED: "<<s<<"\n";}
 out<<"         END   MAIN\n";return{true,out.str(),{}};
}
}
