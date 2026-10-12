#include "ibmlegacy/fortran/source_reader.hpp"
#include <fstream>
#include <string>
#include <utility>
namespace ibmlegacy::fortran {
SourceReadResult read_fixed_form_source(const std::filesystem::path&p){
 std::ifstream in(p);if(!in)return {false,{},"Cannot open source file: "+p.string()};
 SourceReadResult result;std::string line;std::size_t number=0;
 while(std::getline(in,line)){++number;if(line.empty())continue;line.resize(line.size()<7?7:line.size(),' ');const char indicator=line[0];if(indicator=='C'||indicator=='c'||indicator=='*'||indicator=='!')continue;
 SourceRecord rec;rec.line_number=number;rec.indicator=line[5];rec.label=line.substr(0,5);rec.statement=line.substr(6,line.size()>72?66:line.size()-6);if(line.size()>72)rec.continuation=line.substr(72);
 result.records.push_back(std::move(rec));}
 result.success=true;return result;
}
}