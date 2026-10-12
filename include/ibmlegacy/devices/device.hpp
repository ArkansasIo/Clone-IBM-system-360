#pragma once
#include <cstdint>
#include <string>
namespace ibmlegacy::devices {
enum class DeviceStatus : std::uint8_t { Ready, Busy, EndOfTape, EndOfFile, NotReady, Error };
class Device { public: virtual ~Device()=default; virtual void reset()=0; [[nodiscard]] virtual DeviceStatus status()const noexcept=0; [[nodiscard]] virtual std::string name()const=0; };
}