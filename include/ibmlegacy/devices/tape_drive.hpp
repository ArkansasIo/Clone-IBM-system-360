#pragma once
#include "ibmlegacy/devices/device.hpp"
#include "ibmlegacy/tape/tape_image.hpp"
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
namespace ibmlegacy::devices {
struct TapeDriveConfig { std::string model{"virtual-729"}; unsigned density_cpi{800}; unsigned nominal_bpi_speed{0}; bool write_protected{false}; };
class VirtualTapeDrive final:public Device {
public:
 explicit VirtualTapeDrive(TapeDriveConfig config={});
 void mount(const std::filesystem::path& path); void create_blank(); void save(const std::filesystem::path& path)const;
 void reset()override; [[nodiscard]] DeviceStatus status()const noexcept override; [[nodiscard]] std::string name()const override;
 [[nodiscard]] std::size_t position()const noexcept; [[nodiscard]] const TapeDriveConfig& config()const noexcept;
 std::optional<tape::TapeRecord> read_forward(); std::optional<tape::TapeRecord> read_backward(); void rewind();
 void write_record(std::vector<std::uint8_t> bytes); void write_tape_mark();
private: TapeDriveConfig config_; tape::TapeImage image_; DeviceStatus status_{DeviceStatus::Ready}; bool mounted_{false};
};
}