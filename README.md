# IBM 1401 / IBM 729 and System/360 / IBM 2400 Virtual Hardware Lab

An independent C++23 research and educational codebase for experimenting with early IBM business-computing hardware families.

## Hardware families
- **IBM 1401:** character-addressed memory and word-mark representation, a preliminary CPU interface, and card/printer utilities.
- **IBM 729:** virtual tape-image format, record/tape-mark navigation, and named drive configuration profiles.
- **IBM System/360:** byte-addressed storage, general registers, a small RR instruction subset, opcode metadata, and an educational channel-command queue.
- **IBM 2400 family:** named 2400-family tape unit/control-unit profiles using the generic virtual tape backend.
- **FORTRAN subset tooling:** experimental fixed-form source reader/translator with illustrative assembly listing output.

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
```

## Compatibility status
This is not a complete, bit-compatible emulator and does not contain IBM's original source code. IBM 1401 instruction execution is not implemented. System/360 CPU support currently recognizes only a small RR instruction subset. The named 729/2400 profiles are configuration presets rather than cycle-accurate physical device simulations. FORTRAN translation and generated assembly remain experimental.

Read `docs/MODEL_MATRIX.md`, `docs/IBM1401_729.md`, `docs/SYSTEM360_2400.md`, `docs/ARCHITECTURE.md`, and `docs/RESEARCH_SOURCES.md` before extending the emulator.
