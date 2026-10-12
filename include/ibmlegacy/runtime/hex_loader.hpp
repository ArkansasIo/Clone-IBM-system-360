#pragma once
#include "ibmlegacy/machines/system360.hpp"
#include <filesystem>
#include <cstddef>
#include <string>
namespace ibmlegacy::runtime {
struct LoadResult { bool success{false}; std::size_t bytes_loaded{0}; std::string error; };
// Loads whitespace-separated hexadecimal bytes into storage at a checked start address.
[[nodiscard]] LoadResult load_hex_program(machines::System360Storage& storage,const std::filesystem::path& file,std::size_t start_address=0);
}