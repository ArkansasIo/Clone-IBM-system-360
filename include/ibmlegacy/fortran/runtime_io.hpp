#pragma once
#include <istream>
#include <ostream>
#include <string>
#include <vector>
namespace ibmlegacy::fortran {
class FortranRuntimeIO {
public:
 explicit FortranRuntimeIO(std::istream& input,std::ostream& output);
 void print_list(const std::vector<std::string>& values,bool newline=true);
 [[nodiscard]] bool read_list(std::vector<std::string>& values);
 void write_record(const std::string& record); [[nodiscard]] bool read_record(std::string& record);
private: std::istream& input_; std::ostream& output_;
};
}