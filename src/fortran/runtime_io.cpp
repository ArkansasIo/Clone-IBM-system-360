#include "ibmlegacy/fortran/runtime_io.hpp"
#include <utility>
namespace ibmlegacy::fortran {
FortranRuntimeIO::FortranRuntimeIO(std::istream&i,std::ostream&o):input_(i),output_(o){}
void FortranRuntimeIO::print_list(const std::vector<std::string>&v,bool nl){for(std::size_t i=0;i<v.size();++i){if(i)output_<<' ';output_<<v[i];}if(nl)output_<<'\n';}
bool FortranRuntimeIO::read_list(std::vector<std::string>&v){for(auto&x:v)if(!(input_>>x))return false;return true;}
void FortranRuntimeIO::write_record(const std::string&r){output_<<r<<'\n';}
bool FortranRuntimeIO::read_record(std::string&r){return static_cast<bool>(std::getline(input_,r));}
}