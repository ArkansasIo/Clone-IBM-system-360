#include "ibmlegacy/runtime/binary_loader.hpp"
#include <fstream>
#include <iterator>
#include <vector>
namespace ibmlegacy::runtime {
BinaryLoadResult load_binary_program(machines::System360Storage& storage,const std::filesystem::path& path,std::size_t start){
 std::ifstream in(path,std::ios::binary);if(!in)return {false,0,"Cannot open binary file: "+path.string()};
 std::vector<char> bytes((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());
 if(start>storage.size()||bytes.size()>storage.size()-start)return {false,0,"Binary program does not fit in storage"};
 for(std::size_t i=0;i<bytes.size();++i)storage.write_byte(start+i,static_cast<unsigned char>(bytes[i]));
 return {true,bytes.size(),{}};
}
}