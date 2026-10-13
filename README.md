# IBM Legacy Virtual Hardware Lab

Independent C++23 research and educational codebase for IBM 1401 / IBM 729 and IBM System/360 / IBM 2400-family virtual hardware.

## Current modules
- IBM 1401 character storage and preliminary CPU interface.
- IBM 729 and IBM 2400-family named tape profiles over a generic virtual tape image.
- System/360 byte storage, GPRs, a small RR instruction subset, ALU helpers, decoder metadata, and channel queue.
- Virtual card deck, IBM 1402 reader, IBM 1403 printer wrapper, IBM 2540 reader/punch wrapper, and device bus.
- Hex and binary byte loaders, EBCDIC invariant-character helpers, trace logger, fixed-form FORTRAN reader/prototype translator.
- Experimental RR assembler command `ibm-as`.
- FORTRAN front-end executables: `ibm-fortran` (prototype translator), `ibm-fortran-app` (interactive shell), and `ibm-fortran-tool` (source analyzer).

## Build and test
Requires CMake 3.25+ and a C++23 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build -C Debug --output-on-failure
```

> With a single-config generator (Makefiles, Ninja) drop the `-C Debug` flag.
> With a multi-config generator (Visual Studio, Xcode) pass `--config Debug` to
> `cmake --build` and `-C Debug` to `ctest`.

## Examples
All executables are written to the `bin/` folder at the project root
(`bin/Debug` / `bin/Release` with multi-config generators such as Visual Studio).
Override with `-DIBMLEGACY_EXE_OUTPUT_DIR=<path>` when configuring.

```sh
./bin/Debug/ibm-legacy --help
./bin/Debug/ibm-legacy memory-demo
./bin/Debug/ibm-legacy tape-demo demo.vmt
./bin/Debug/ibm-legacy inspect-tape demo.vmt
./bin/Debug/ibm-fortran --help
./bin/Debug/ibm-fortran-tool resources/fortran/examples/hello.f --json
./bin/Debug/ibm-as examples/system360/rr_subset.asm rr_subset.bin
```

## Tests and CI

The CTest suite is registered as `ibmlegacy-tests` and is run by `ctest`. Two
Python helper scripts under `scripts/` back the CI workflow:

```sh
python3 scripts/validate_fortran_resources.py
python3 scripts/test_fortran_examples.py --compiler build/ibm-fortran --cxx c++
```

The GitHub Actions workflow (`.github/workflows/build.yml`) configures a Debug
build, compiles, validates the FORTRAN resources, runs the example programs, and
then runs CTest on every push and pull request to `main`.

## FORTRAN library

A reusable static library target, `ibmfortran`, is provided (CMake alias `ibmlegacy::fortran`). Its headers include source records, lexer/token types, diagnostics, symbols, arithmetic expression evaluation, initial intrinsic helpers, basic runtime I/O/math, a partial FORMAT descriptor parser, and bounded numeric arrays. Metadata, include files, and examples are under `resources/fortran/`; see `docs/FORTRAN_BUILD.md` and `docs/FORTRAN_LIBRARY.md`.

## Compatibility and verification status
This is not a complete or bit-compatible emulator and does not include IBM's original source code. The IBM 1401 instruction decoder remains unimplemented. System/360 execution covers only a small educational RR subset. The 729/2400 profiles are configuration scaffolds rather than cycle-accurate device simulations. The FORTRAN translator and assembler are limited prototypes. See `docs/DEVELOPMENT_STATUS.md`, `docs/MODEL_MATRIX.md`, `docs/ROADMAP.md`, and `docs/RESEARCH_SOURCES.md`.

Do not consider a commit verified until the build, CTest suite, and CI workflow have been run successfully.

## License

This is a clean-room, educational project. It is not affiliated with, endorsed
by, or derived from any IBM product source code. See `docs/RESEARCH_SOURCES.md`
for the public references consulted.
