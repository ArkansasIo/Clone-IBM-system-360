#pragma once
#include <cstdint>
#include <string>
#include <string_view>
namespace ibmlegacy::machines {
// Small ASCII/EBCDIC invariant-character conversion table; not a full code page.
[[nodiscard]] std::uint8_t ascii_to_ebcdic(char value) noexcept;
[[nodiscard]] char ebcdic_to_ascii(std::uint8_t value) noexcept;
[[nodiscard]] std::string ascii_to_ebcdic_bytes(std::string_view text);
[[nodiscard]] std::string ebcdic_bytes_to_ascii(std::string_view bytes);
}