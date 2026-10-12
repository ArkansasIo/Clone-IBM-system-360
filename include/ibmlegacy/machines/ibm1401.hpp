#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
namespace ibmlegacy::machines {
struct Character1401 { std::uint8_t code{0}; bool word_mark{false}; };
class IBM1401Memory {
public:
 explicit IBM1401Memory(std::size_t characters=4000);
 [[nodiscard]] std::size_t size()const noexcept;
 Character1401 read(std::size_t address)const;
 void write(std::size_t address,Character1401 value);
 void load_ascii(std::size_t start,const std::string& text);
 [[nodiscard]] std::string dump_ascii(std::size_t start,std::size_t count)const;
private: std::vector<Character1401> memory_;
};
}
