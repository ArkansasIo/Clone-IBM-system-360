#include "ibmlegacy/fortran/diagnostic.hpp"
#include <sstream>
#include <utility>
namespace ibmlegacy::fortran {
void DiagnosticBag::add(Diagnostic d){items_.push_back(std::move(d));}
void DiagnosticBag::error(SourceLocation l,std::string c,std::string m){add({Severity::Error,std::move(l),std::move(c),std::move(m)});}
void DiagnosticBag::warning(SourceLocation l,std::string c,std::string m){add({Severity::Warning,std::move(l),std::move(c),std::move(m)});}
bool DiagnosticBag::has_errors()const noexcept{for(const auto&d:items_)if(d.severity==Severity::Error)return true;return false;}
const std::vector<Diagnostic>& DiagnosticBag::all()const noexcept{return items_;}
std::string DiagnosticBag::format()const{std::ostringstream o;for(const auto&d:items_){if(!d.location.file.empty())o<<d.location.file<<':';o<<d.location.line<<':'<<d.location.column<<": "<<(d.severity==Severity::Error?"error":d.severity==Severity::Warning?"warning":"note")<<" ["<<d.code<<"] "<<d.message<<'\n';}return o.str();}
}