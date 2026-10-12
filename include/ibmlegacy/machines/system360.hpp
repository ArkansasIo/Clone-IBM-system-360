#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace ibmlegacy::machines {
class System360Storage {
public:
 explicit System360Storage(std::size_t bytes=64*1024);
 [[nodiscard]] std::size_t size()const noexcept;
 std::uint8_t read_byte(std::size_t address)const;
 void write_byte(std::size_t address,std::uint8_t value);
 std::uint32_t read_word(std::size_t address)const;
 void write_word(std::size_t address,std::uint32_t value);
private: std::vector<std::uint8_t> bytes_;
};
struct System360Registers { std::array<std::uint32_t,16> general{}; std::uint32_t instruction_address{0}; std::uint8_t condition_code{0}; };
}
