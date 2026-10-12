#pragma once
#include <filesystem>
#include <fstream>
#include <string_view>
namespace ibmlegacy::runtime {
class TraceLogger {
public:
 explicit TraceLogger(const std::filesystem::path& path);
 [[nodiscard]] bool good()const noexcept;
 void write(std::string_view category,std::string_view message);
private: std::ofstream output_;
};
}