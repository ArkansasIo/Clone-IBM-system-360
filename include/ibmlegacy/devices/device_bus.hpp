#pragma once
#include "ibmlegacy/devices/device.hpp"
#include <map>
#include <memory>
#include <string>
namespace ibmlegacy::devices {
class DeviceBus {
public:
 bool attach(std::string address,std::shared_ptr<Device> device);
 [[nodiscard]] std::shared_ptr<Device> find(const std::string& address)const;
 bool detach(const std::string& address);
 [[nodiscard]] std::size_t size()const noexcept;
 void reset_all();
private: std::map<std::string,std::shared_ptr<Device>> devices_;
};
}