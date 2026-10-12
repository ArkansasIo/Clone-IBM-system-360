#include "ibmlegacy/devices/tape_drive.hpp"
#include <stdexcept>
#include <utility>
namespace ibmlegacy::devices {
VirtualTapeDrive::VirtualTapeDrive(TapeDriveConfig c):config_(std::move(c)){}
void VirtualTapeDrive::mount(const std::filesystem::path&p){image_=tape::TapeImage::load(p);mounted_=true;status_=DeviceStatus::Ready;}
void VirtualTapeDrive::create_blank(){image_=tape::TapeImage{};mounted_=true;status_=DeviceStatus::Ready;}
void VirtualTapeDrive::save(const std::filesystem::path&p)const{if(!mounted_)throw std::logic_error("No tape mounted");image_.save(p);}
void VirtualTapeDrive::reset(){image_.rewind();status_=mounted_?DeviceStatus::Ready:DeviceStatus::NotReady;}
DeviceStatus VirtualTapeDrive::status()const noexcept{return status_;}
std::string VirtualTapeDrive::name()const{return config_.model;}
std::size_t VirtualTapeDrive::position()const noexcept{return image_.position();}
const TapeDriveConfig& VirtualTapeDrive::config()const noexcept{return config_;}
std::optional<tape::TapeRecord> VirtualTapeDrive::read_forward(){if(!mounted_){status_=DeviceStatus::NotReady;return{};}auto r=image_.read_next();status_=r?(r->tape_mark?DeviceStatus::EndOfFile:DeviceStatus::Ready):DeviceStatus::EndOfTape;return r;}
std::optional<tape::TapeRecord> VirtualTapeDrive::read_backward(){if(!mounted_){status_=DeviceStatus::NotReady;return{};}auto r=image_.backspace_read();status_=r?DeviceStatus::Ready:DeviceStatus::EndOfTape;return r;}
void VirtualTapeDrive::rewind(){if(!mounted_)throw std::logic_error("No tape mounted");image_.rewind();status_=DeviceStatus::Ready;}
void VirtualTapeDrive::write_record(std::vector<std::uint8_t>b){if(!mounted_)throw std::logic_error("No tape mounted");if(config_.write_protected){status_=DeviceStatus::Error;throw std::runtime_error("Tape is write-protected");}image_.append_record(std::move(b));}
void VirtualTapeDrive::write_tape_mark(){if(!mounted_)throw std::logic_error("No tape mounted");if(config_.write_protected){status_=DeviceStatus::Error;throw std::runtime_error("Tape is write-protected");}image_.append_tape_mark();}
}