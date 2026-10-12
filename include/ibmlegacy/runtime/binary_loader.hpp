#pragma once
#include "ibmlegacy/machines/system360.hpp"
#include <cstddef>
#include <filesystem>
#include <string>
namespace ibmlegacy::runtime {
struct BinaryLoadResult { bool success{false}; std::size_t bytes_loaded{0}; std::string diagnostic; };
[[nodiscard]] BinaryLoadResult load_binary_program(machines::System360Storage& storage,const std::filesystem::path& path,std::size_t start_address=0);
}