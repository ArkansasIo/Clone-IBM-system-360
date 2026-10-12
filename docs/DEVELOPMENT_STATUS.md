# Development status

## Available source modules
- C++23/CMake project and command-line tools: `ibm-legacy`, `ibm-fortran`, `ibm-as`.
- IBM 1401 character storage and placeholder CPU interface.
- System/360 storage, a small RR instruction subset, ALU helpers, decoder metadata and raw/hex program loaders.
- Virtual tape image, IBM 729/2400 profile scaffolds, channel queue and device bus.
- Text card deck, virtual IBM 1402 reader, IBM 1403 printer wrapper and IBM 2540 reader/punch wrapper.
- EBCDIC invariant-character conversion, fixed-form FORTRAN source reader and prototype translator.
- Assembler line parser and RR subset encoder.

## Not complete
This project is not yet a complete emulator. Full 1401 CPU semantics, full System/360 instruction execution, model-accurate device protocols, channel I/O, full FORTRAN IV, full assembler/object modules, and compatibility test suites remain future work.

## Verification
A file being committed is not evidence that it compiles. Run the documented build and CTest commands on a supported C++23 toolchain and inspect the GitHub Actions workflow result before treating a revision as verified.