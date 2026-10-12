#include "ibmlegacy/tape/tape_image.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
namespace ibmlegacy::tape {
namespace {
constexpr char magic[]={'V','M','T','1'};
constexpr std::uint32_t max_record=64U*1024U*1024U;
void write_u32(std::ostream& o,std::uint32_t n){for(int s=24;s>=0;s-=8)o.put(static_cast<char>((n>>s)&0xffU));}
std::uint32_t read_u32(std::istream& in){std::uint32_t n=0;for(int i=0;i<4;++i){int c=in.get();if(c==EOF)throw std::runtime_error("Truncated tape image");n=(n<<8U)|static_cast<std::uint32_t>(static_cast<unsigned char>(c));}return n;}
}
void TapeImage::append_record(std::vector<std::uint8_t> b){records_.push_back({false,std::move(b)});}
void TapeImage::append_tape_mark(){records_.push_back({true,{}});}
const std::vector<TapeRecord>& TapeImage::records()const noexcept{return records_;}
std::optional<TapeRecord> TapeImage::read_next(){if(position_>=records_.size())return {};return records_[position_++];}
std::optional<TapeRecord> TapeImage::backspace_read(){if(position_==0)return {};return records_[--position_];}
void TapeImage::rewind()noexcept{position_=0;}
std::size_t TapeImage::position()const noexcept{return position_;}
void TapeImage::save(const std::filesystem::path& p)const{std::ofstream o(p,std::ios::binary);if(!o)throw std::runtime_error("Cannot create tape image");o.write(magic,4);write_u32(o,static_cast<std::uint32_t>(records_.size()));for(auto&r:records_){o.put(r.tape_mark?1:0);write_u32(o,static_cast<std::uint32_t>(r.bytes.size()));if(!r.bytes.empty())o.write(reinterpret_cast<const char*>(r.bytes.data()),static_cast<std::streamsize>(r.bytes.size()));}if(!o)throw std::runtime_error("Tape image write failed");}
TapeImage TapeImage::load(const std::filesystem::path& p){std::ifstream in(p,std::ios::binary);if(!in)throw std::runtime_error("Cannot open tape image");char h[4]{};in.read(h,4);if(!in||std::string(h,4)!=std::string(magic,4))throw std::runtime_error("Invalid tape image header");auto count=read_u32(in);if(count>10000000U)throw std::runtime_error("Unreasonable tape record count");TapeImage image;for(std::uint32_t i=0;i<count;++i){int mark=in.get();if(mark==EOF)throw std::runtime_error("Truncated tape image");auto size=read_u32(in);if(size>max_record)throw std::runtime_error("Tape record too large");std::vector<std::uint8_t>b(size);if(size)in.read(reinterpret_cast<char*>(b.data()),static_cast<std::streamsize>(size));if(!in)throw std::runtime_error("Truncated tape record");image.records_.push_back({mark!=0,std::move(b)});}return image;}
}
