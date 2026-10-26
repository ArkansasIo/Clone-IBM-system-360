#pragma once
#include "ibmlegacy/devices/ccw.hpp"
#include <cstdint>
#include <unordered_map>
namespace ibmlegacy::devices {
class IChannelDevice { public: virtual ~IChannelDevice()=default; virtual DeviceStatus execute(const CCW&, std::uint8_t*, std::size_t)=0; };
class ChannelSubsystem {
public:
 void attach(std::uint8_t address, IChannelDevice* device) { devices_[address]=device; }
 [[nodiscard]] bool attached(std::uint8_t address) const { return devices_.contains(address); }
 DeviceStatus start(std::uint8_t address, const CCW& ccw, std::uint8_t* memory, std::size_t size);
private: std::unordered_map<std::uint8_t,IChannelDevice*> devices_;
};
}
