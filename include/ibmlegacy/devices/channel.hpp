#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace ibmlegacy::devices {
enum class ChannelCommandCode : std::uint8_t { TestReady=0x00, Read=0x02, Write=0x01, Control=0x03, Sense=0x04, NoOperation=0x03 };
struct ChannelCommandWord { std::uint8_t command{0}; std::uint8_t flags{0}; std::uint16_t count{0}; std::uint32_t data_address{0}; };
enum class ChannelStatus : std::uint8_t { Idle, Busy, ChannelEnd, DeviceEnd, UnitCheck, ProgramCheck, InvalidCommand };
struct ChannelResult { ChannelStatus status{ChannelStatus::Idle}; std::uint16_t residual_count{0}; std::string message; };
// This is an educational CCW queue model, not full System/360 channel hardware.
class VirtualChannel {
public:
 void submit(ChannelCommandWord ccw);
 [[nodiscard]] bool has_pending()const noexcept;
 [[nodiscard]] ChannelCommandWord next();
 void complete(ChannelStatus status,std::uint16_t residual=0,std::string message={});
 [[nodiscard]] ChannelResult last_result()const;
 void reset()noexcept;
private: std::vector<ChannelCommandWord> queue_; std::size_t cursor_{0}; ChannelResult last_{};
};
}