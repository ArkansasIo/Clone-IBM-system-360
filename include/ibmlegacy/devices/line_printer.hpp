#pragma once
#include <filesystem>
#include <string>
#include <vector>
namespace ibmlegacy::devices {
class VirtualLinePrinter { public: void print_line(std::string line); void form_feed(); [[nodiscard]] const std::vector<std::string>& output()const noexcept; void save(const std::filesystem::path&)const; private: std::vector<std::string> lines_; };
}