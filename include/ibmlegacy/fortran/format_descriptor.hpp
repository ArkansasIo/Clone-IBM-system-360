#pragma once
#include <cstddef>
#include <string>
#include <vector>
namespace ibmlegacy::fortran {
enum class FormatKind { Integer, FixedReal, Exponential, Character, Literal, Slash, Scale };
struct FormatDescriptor { FormatKind kind{FormatKind::Literal}; std::size_t repeat{1}; std::size_t width{0}; std::size_t precision{0}; std::string literal; };
struct FormatParseResult { bool success{false}; std::vector<FormatDescriptor> descriptors; std::string diagnostic; };
[[nodiscard]] FormatParseResult parse_format_specification(const std::string& text);
}