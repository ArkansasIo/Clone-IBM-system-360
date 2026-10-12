#include "ibmlegacy/fortran/fortran_compiler.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
int main(int argc,char**argv){using namespace ibmlegacy::fortran;if(argc<3||std::string(argv[1])=="--help"){std::cout<<"Usage: ibm-fortran [--emit-c|--emit-s360] source.f [output]\n";return 0;}std::string mode=argv[1],source=argv[2];if(mode!="--emit-c"&&mode!="--emit-s360"){source=argv[1];mode="--emit-c";}std::filesystem::path src(source),outpath=argc>=4?argv[3]:src.stem().string()+(mode=="--emit-s360"?".s360.asm":".cpp");FortranCompiler c;auto r=mode=="--emit-s360"?c.emit_s360_listing(src):c.emit_cpp(src);if(!r.success){std::cerr<<r.diagnostics<<'\n';return 1;}std::ofstream out(outpath);if(!out){std::cerr<<"Cannot write output\n";return 2;}out<<r.output;std::cout<<"Wrote "<<outpath<<'\n';return 0;}