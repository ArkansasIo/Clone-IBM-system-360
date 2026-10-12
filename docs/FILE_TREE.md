# Repository layout

- `include/ibmlegacy/assembler`: assembler line model, lexer and RR encoder APIs
- `include/ibmlegacy/cpu`: CPU result, System/360 CPU/ALU/decoder/opcodes and IBM 1401 CPU interface
- `include/ibmlegacy/devices`: device interface/bus, tape drives, channel queue, card/printer wrappers
- `include/ibmlegacy/fortran`: FORTRAN compiler prototype and fixed-form source reader
- `include/ibmlegacy/machines`: IBM 1401 and System/360 memory models, EBCDIC and profile metadata
- `include/ibmlegacy/runtime`: machine profiles, hex/binary loaders, trace logger
- `include/ibmlegacy/tape`: virtual tape-image interface
- `src`: C++23 implementations and command-line entry points
- `config`: descriptive machine/device profiles
- `docs`: architecture, research, subsystem status, and limitations
- `examples`: assembler, FORTRAN and device fixtures
- `tests`: regression tests
- `.github/workflows`: build and test workflow

This is a growing educational project; a present file or profile does not imply complete historical hardware compatibility.
