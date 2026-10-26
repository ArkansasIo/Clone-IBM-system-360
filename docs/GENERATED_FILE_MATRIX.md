# Generated File Matrix

## CPU
- `include/ibmlegacy/cpu/system360_formats.hpp` — RR/RX/RS/SI/SS structures
- `include/ibmlegacy/cpu/system360_decoder.hpp` — format decoders
- `src/cpu/system360_decoder.cpp` — decoder implementation
- `include/ibmlegacy/cpu/system360_psw.hpp` — PSW state model
- `include/ibmlegacy/cpu/system360_interrupts.hpp` — interrupt queue
- `include/ibmlegacy/cpu/system360_cpu.hpp` — CPU public API
- `src/cpu/system360_cpu.cpp` — execution engine
- `include/ibmlegacy/cpu/system360_opcodes.hpp` — opcode metadata

## I/O
- `include/ibmlegacy/devices/ccw.hpp` — CCW/status structures
- `include/ibmlegacy/devices/channel_subsystem.hpp` — channel/device API
- `src/devices/channel_subsystem.cpp` — channel dispatch

## Tests
- `tests/test_system360_cpu_expansion.cpp` — CPU execution coverage
- `tests/test_system360_formats.cpp` — instruction-format coverage
- `tests/fixtures/system360_smoke.hex` — loader smoke fixture

## Build and configuration
- `CMakeLists.txt` — targets and CTest registration
- `CMakePresets.json` — repeatable configure/build/test presets
- `.clang-format` — C++ formatting
- `config/system360-model-40.json` — machine profile

## Documentation and examples
- `docs/SYSTEM360_COMPLETE_ARCHITECTURE.md` — architecture contract
- `examples/hello360.asm` — assembler smoke example

The existing IBM 1401, IBM 729/2400, card, printer, tape, EBCDIC, assembler, loader, FORTRAN, tracing and runtime modules remain part of the same build and are not replaced by these additions.
