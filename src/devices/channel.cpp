#include "ibmlegacy/devices/channel.hpp"
#include <stdexcept>
#include <utility>
namespace ibmlegacy::devices {
void VirtualChannel::submit(ChannelCommandWord c){queue_.push_back(c);last_={ChannelStatus::Busy,c.count,"Command queued"};}
bool VirtualChannel::has_pending()const noexcept{return cursor_<queue_.size();}
ChannelCommandWord VirtualChannel::next(){if(!has_pending())throw std::out_of_range("No pending channel command");return queue_[cursor_++];}
void VirtualChannel::complete(ChannelStatus s,std::uint16_t r,std::string m){last_={s,r,std::move(m)};if(cursor_==queue_.size()){queue_.clear();cursor_=0;}}
ChannelResult VirtualChannel::last_result()const{return last_;}
void VirtualChannel::reset()noexcept{queue_.clear();cursor_=0;last_={};}
}