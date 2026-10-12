#pragma once
#include "ibmlegacy/fortran/source_record.hpp"
#include <filesystem>
#include <string>
#include <vector>
namespace ibmlegacy::fortran {
struct SourceReadResult { bool success{false}; std::vector<SourceRecord> records; std::string diagnostic; };
[[nodiscard]] SourceReadResult read_fixed_form_source(const std::filesystem::path& path);
}