#include "ibmlegacy/assembler/encoder.hpp"
#include "ibmlegacy/assembler/lexer.hpp"
#include <fstream>
#include <iostream>
#include <string>
int main(int argc,char**argv){
 if(argc<3||std::string(argv[1])=="--help"){std::cout<<"Usage: ibm-as source.asm output.bin\nSupported RR subset: LR, AR, BALR, BCR\n";return 0;}
 std::ifstream in(argv[1]);if(!in){std::cerr<<"Cannot open source file\n";return 2;}
 std::ofstream out(argv[2],std::ios::binary);if(!out){std::cerr<<"Cannot create output file\n";return 2;}
 std::string line;std::size_t number=0;while(std::getline(in,line)){++number;auto parsed=ibmlegacy::assembler::parse_assembler_line(line,number);if(!parsed.success){std::cerr<<parsed.diagnostic<<'\n';return 1;}if(parsed.line.mnemonic.empty())continue;auto encoded=ibmlegacy::assembler::encode_rr_subset(parsed.line);if(!encoded.success){std::cerr<<"Line "<<number<<": "<<encoded.diagnostic<<'\n';return 1;}for(auto b:encoded.bytes)out.put(static_cast<char>(b));}
 if(!out){std::cerr<<"Failed while writing output\n";return 2;}std::cout<<"Wrote RR subset object bytes to "<<argv[2]<<'\n';return 0;
}