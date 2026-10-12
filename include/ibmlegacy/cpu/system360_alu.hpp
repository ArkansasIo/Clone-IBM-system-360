#pragma once
#include <cstdint>
namespace ibmlegacy::cpu {
struct ArithmeticResult { std::uint32_t value{0}; std::uint8_t condition_code{0}; bool carry{false}; bool overflow{false}; };
[[nodiscard]] ArithmeticResult add32(std::uint32_t lhs,std::uint32_t rhs) noexcept;
[[nodiscard]] ArithmeticResult subtract32(std::uint32_t lhs,std::uint32_t rhs) noexcept;
[[nodiscard]] std::uint8_t condition_code_logical(std::uint32_t value) noexcept;
}