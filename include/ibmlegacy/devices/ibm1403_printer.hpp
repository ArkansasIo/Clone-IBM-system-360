#pragma once
#include "ibmlegacy/devices/device.hpp"
#include "ibmlegacy/devices/line_printer.hpp"
#include <string>
namespace ibmlegacy::devices {
class VirtualIBM1403Printer final:public Device {
public:
 void print(std::string line); void advance_page();
 [[nodiscard]] const VirtualLinePrinter& printer()const noexcept;
 void reset()override; [[nodiscard]] DeviceStatus status()const noexcept override; [[nodiscard]] std::string name()const override;
private: VirtualLinePrinter printer_; DeviceStatus status_{DeviceStatus::Ready};
};
}