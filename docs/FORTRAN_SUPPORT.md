# System/360 FORTRAN support

The project now exposes an independently written FORTRAN IV-style educational library as the CMake static target `ibmfortran` (alias `ibmlegacy::fortran`) and a driver executable named `ibm-fortran`.

## Library modules
- Fixed-form source reader with source line/column records.
- Token and statement lexer, source locations, structured diagnostics.
- Case-insensitive symbol table and a numeric expression evaluator supporting arithmetic, parentheses, exponentiation and E/D exponents.
- Initial intrinsic evaluation helpers and elementary double-precision math wrappers.
- Basic runtime text I/O, a partial FORMAT descriptor parser, and bounded one-dimensional numeric array storage.
- C++ subset emitter and illustrative System/360 listing emitter.
- JSON dialect/intrinsic/keyword/resource manifests, sample source, expected-output fixtures, and an include-file example.

## Build and test
```sh
cmake -S . -B build
cmake --build build
python3 scripts/validate_fortran_resources.py
python3 scripts/test_fortran_examples.py --compiler build/ibm-fortran --cxx c++
ctest --test-dir build --output-on-failure
```

The GitHub Actions workflow runs resource validation and end-to-end example checks after building.

## Limitations
This is not a full FORTRAN IV/H compiler or a replacement for IBM's historical compiler. The translator currently handles only simple declarations, assignments and PRINT lists. Full statement parsing, implicit typing, arrays in the language frontend, DO loops, arithmetic/computed IF, GO TO labels, FORMAT execution, file units, READ/WRITE semantics, COMMON/EQUIVALENCE/DATA, subprogram linkage, object modules and executable System/360 output remain unimplemented. The S/360 listing mode is a documentation scaffold and is not executable object code.

The resources are independently written project metadata and examples; they do not include IBM proprietary compiler source code. Confirm historical language semantics against primary manuals before claiming compatibility.