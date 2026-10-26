#include "ibmlegacy/devices/channel_subsystem.hpp"
namespace ibmlegacy::devices {
DeviceStatus ChannelSubsystem::start(std::uint8_t address,const CCW& ccw,std::uint8_t* memory,std::size_t size) {
 auto it=devices_.find(address); if(it==devices_.end()) return DeviceStatus{0x40,0x01,false,false};
 return it->second->execute(ccw,memory,size);
}
}
