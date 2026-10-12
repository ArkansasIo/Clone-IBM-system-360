# IBM System/360 Virtual Hardware Lab

Independent C++23 emulator research project for historically informed IBM 1401/729 and System/360/2400 virtual hardware, with an initial FORTRAN subset tool.

## Status

This is an incremental educational implementation, not a complete or bit-compatible IBM emulator and not IBM's original source code. Current components include virtual tape images and drive, card-deck and line-printer models, 1401 character storage, System/360 byte storage/registers, a small System/360 register-instruction subset, and an experimental fixed-form FORTRAN reader/translator.

## Build

Requires CMake 3.25+ and a C++23 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Commands

```sh
./build/ibm-legacy --help
./build/ibm-legacy memory-demo
./build/ibm-legacy tape-demo demo.vmt
./build/ibm-legacy inspect-tape demo.vmt
./build/ibm-fortran --emit-c examples/system360/fortran/arithmetic.f arithmetic.cpp
./build/ibm-fortran --emit-s360 examples/system360/fortran/arithmetic.f arithmetic.s360.asm
```

The FORTRAN compiler is a prototype. Its generated System/360 assembly is an illustrative listing, not an executable object deck. The IBM 1401 CPU decoder and full System/360 instruction set remain future work.

## Research references

- IBM 1401 reference manual: https://bitsavers.org/pdf/ibm/1401/A24-1403-5_1401_Reference_Apr62.pdf
- IBM 729 tape notes: https://ibm1401.computerhistory.org/729-Info.html
- System/360 Principles of Operation: https://www.eserviceinfo.com/preview_html.php?fileid=79665&previewid=50152

See `docs/` for architecture, hardware, research, roadmap, and FORTRAN support notes.