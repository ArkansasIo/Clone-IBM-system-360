# System/360 FORTRAN prototype

An independent educational fixed-form source reader and translator. It is not IBM FORTRAN IV/H and does not claim full dialect or object-deck compatibility. It supports only a small subset; unsupported control flow is rejected rather than silently translated. The System/360 assembly output is illustrative and not executable machine code.

Build with CMake and run ibm-fortran --emit-c arithmetic.f arithmetic.cpp or --emit-s360 for the listing scaffold.