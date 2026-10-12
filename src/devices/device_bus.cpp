#include "ibmlegacy/devices/device_bus.hpp"
#include <utility>
namespace ibmlegacy::devices {
bool DeviceBus::attach(std::string a,std::shared_ptr<Device>d){if(a.empty()||!d)return false;return devices_.emplace(std::move(a),std::move(d)).second;}
std::shared_ptr<Device> DeviceBus::find(const std::string&a)const{auto i=devices_.find(a);return i==devices_.end()?nullptr:i->second;}
bool DeviceBus::detach(const std::string&a){return devices_.erase(a)!=0;}
std::size_t DeviceBus::size()const noexcept{return devices_.size();}
void DeviceBus::reset_all(){for(auto&[address,device]:devices_){(void)address;device->reset();}}
}