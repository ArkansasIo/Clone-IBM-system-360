# IBM Legacy Virtual Hardware Lab

Independent C++23 research and educational codebase for IBM 1401 / IBM 729 and IBM System/360 / IBM 2400-family virtual hardware.

## Current modules
- IBM 1401 character storage and preliminary CPU interface.
- IBM 729 and IBM 2400-family named tape profiles over a generic virtual tape image.
- System/360 byte storage, GPRs, a small RR instruction subset, ALU helpers, decoder metadata, and channel queue.
- Virtual card deck, IBM 1402 reader, IBM 1403 printer wrapper, IBM 2540 reader/punch wrapper, and device bus.
- Hex and binary byte loaders, EBCDIC invariant-character helpers, trace logger, fixed-form FORTRAN reader/prototype translator.
- Experimental RR assembler command `ibm-as`.

## Build and test
Requires CMake 3.25+ and a C++23 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Examples
```sh
./build/ibm-legacy --help
./build/ibm-legacy memory-demo
./build/ibm-legacy tape-demo demo.vmt
./build/ibm-legacy inspect-tape demo.vmt
./build/ibm-fortran --help
./build/ibm-as examples/system360/rr_subset.asm rr_subset.bin
```

## FORTRAN library

A reusable static library target, `ibmfortran`, is provided (CMake alias `ibmlegacy::fortran`). Its headers include source records, lexer/token types, diagnostics, symbols, arithmetic expression evaluation, initial intrinsic helpers, basic runtime I/O/math, a partial FORMAT descriptor parser, and bounded numeric arrays. Metadata, include files, and examples are under `resources/fortran/`; see `docs/FORTRAN_BUILD.md` and `docs/FORTRAN_LIBRARY.md`.

## Compatibility and verification status
This is not a complete or bit-compatible emulator and does not include IBM's original source code. The IBM 1401 instruction decoder remains unimplemented. System/360 execution covers only a small educational RR subset. The 729/2400 profiles are configuration scaffolds rather than cycle-accurate device simulations. The FORTRAN translator and assembler are limited prototypes. See `docs/DEVELOPMENT_STATUS.md`, `docs/MODEL_MATRIX.md`, `docs/ROADMAP.md`, and `docs/RESEARCH_SOURCES.md`.

Do not consider a commit verified until the build, CTest suite, and CI workflow have been run successfully.
