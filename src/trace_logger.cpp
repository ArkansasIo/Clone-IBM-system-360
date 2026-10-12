#include "ibmlegacy/runtime/trace_logger.hpp"
#include <string_view>
#include <utility>
namespace ibmlegacy::runtime {
TraceLogger::TraceLogger(const std::filesystem::path&p):output_(p,std::ios::app){}
bool TraceLogger::good()const noexcept{return output_.good();}
void TraceLogger::write(std::string_view c,std::string_view m){if(output_)output_<<'['<<c<<"] "<<m<<'\n';}
}