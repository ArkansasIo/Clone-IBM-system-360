#pragma once
#include <cstddef>
#include <string>
namespace ibmlegacy::runtime {
enum class MachineKind { IBM1401, System360 };
struct MachineConfig { MachineKind kind{MachineKind::IBM1401}; std::size_t storage_size{4000}; std::string profile{"development"}; bool enable_tape{true}; bool enable_cards{true}; bool enable_printer{true}; };
}