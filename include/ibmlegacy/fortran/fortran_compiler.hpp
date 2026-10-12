#pragma once
#include <filesystem>
#include <string>
namespace ibmlegacy::fortran {
struct CompileResult { bool success{false}; std::string output; std::string diagnostics; };
class FortranCompiler { public: [[nodiscard]] CompileResult emit_cpp(const std::filesystem::path&)const; [[nodiscard]] CompileResult emit_s360_listing(const std::filesystem::path&)const; };
}