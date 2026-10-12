#include "ibmlegacy/fortran/parser.hpp"
#include "ibmlegacy/fortran/source_reader.hpp"
#include <algorithm>
#include <cctype>
namespace ibmlegacy::fortran {
namespace {
std::string trim(std::string s){auto p=[](unsigned char c){return !std::isspace(c);};s.erase(s.begin(),std::find_if(s.begin(),s.end(),p));s.erase(std::find_if(s.rbegin(),s.rend(),p).base(),s.end());return s;}
std::string upper(std::string s){for(char&c:s)c=static_cast<char>(std::toupper(static_cast<unsigned char>(c)));return s;}
bool starts(const std::string&s,const std::string&word){return s==word||(s.size()>word.size()&&s.compare(0,word.size(),word)==0&&std::isspace(static_cast<unsigned char>(s[word.size()])));}
StatementKind classify(const std::string&u){
 if(starts(u,"PROGRAM"))return StatementKind::Program;if(u=="END")return StatementKind::End;
 if(starts(u,"INTEGER")||starts(u,"REAL")||starts(u,"LOGICAL")||starts(u,"COMPLEX")||starts(u,"DOUBLE PRECISION"))return StatementKind::Declaration;
 if(starts(u,"PRINT"))return StatementKind::Print;if(starts(u,"READ"))return StatementKind::Read;if(starts(u,"WRITE"))return StatementKind::Write;if(starts(u,"FORMAT"))return StatementKind::Format;
 if(starts(u,"DO"))return StatementKind::DoLoop;if(starts(u,"IF"))return StatementKind::IfStatement;if(starts(u,"GO TO")||starts(u,"GOTO"))return StatementKind::GoTo;
 if(starts(u,"CALL"))return StatementKind::Call;if(starts(u,"RETURN"))return StatementKind::Return;if(starts(u,"STOP"))return StatementKind::Stop;if(starts(u,"PAUSE"))return StatementKind::Pause;if(starts(u,"CONTINUE"))return StatementKind::Continue;
 if(starts(u,"DATA"))return StatementKind::Data;if(starts(u,"COMMON"))return StatementKind::Common;if(starts(u,"EQUIVALENCE"))return StatementKind::Equivalence;if(starts(u,"PARAMETER"))return StatementKind::Parameter;if(starts(u,"DIMENSION"))return StatementKind::Dimension;if(starts(u,"EXTERNAL"))return StatementKind::External;if(starts(u,"INTRINSIC"))return StatementKind::Intrinsic;if(starts(u,"ASSIGN"))return StatementKind::AssignLabel;
 if(u.find('=')!=std::string::npos)return StatementKind::Assignment;return StatementKind::Unknown;
}
}
ParseResult parse_fortran_source(const std::filesystem::path&p){
 auto read=read_fixed_form_source(p);if(!read.success)return {false,{},{{Severity::Error,{p.string(),1,1},"FPARSE001",read.diagnostic}}};
 ParseResult result;result.success=true;
 for(const auto&rec:read.records){const auto source=trim(rec.statement);if(source.empty())continue;const auto u=upper(source);const auto kind=classify(u);Statement stmt;stmt.kind=kind;stmt.location={p.string(),rec.line_number,7};stmt.label=trim(rec.label);stmt.source=source;stmt.keyword=u.substr(0,u.find_first_of(" \t("));
  if(kind==StatementKind::Program){auto space=u.find_first_of(" \t");if(space!=std::string::npos)result.program.name=trim(source.substr(space+1));}
  if(kind==StatementKind::Unknown)result.diagnostics.push_back({Severity::Warning,stmt.location,"FPARSE002","Statement classified as unknown; full grammar is not implemented"});
  result.program.statements.push_back(std::move(stmt));
 }
 return result;
}
}