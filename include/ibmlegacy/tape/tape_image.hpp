#pragma once
#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>
namespace ibmlegacy::tape {
struct TapeRecord { bool tape_mark{false}; std::vector<std::uint8_t> bytes; };
class TapeImage {
public:
 void append_record(std::vector<std::uint8_t> bytes);
 void append_tape_mark();
 [[nodiscard]] const std::vector<TapeRecord>& records() const noexcept;
 [[nodiscard]] std::optional<TapeRecord> read_next();
 [[nodiscard]] std::optional<TapeRecord> backspace_read();
 void rewind() noexcept;
 [[nodiscard]] std::size_t position() const noexcept;
 void save(const std::filesystem::path& path) const;
 static TapeImage load(const std::filesystem::path& path);
private:
 std::vector<TapeRecord> records_; std::size_t position_{0};
};
}
