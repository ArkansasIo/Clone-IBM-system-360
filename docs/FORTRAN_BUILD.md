# Building the FORTRAN library

The repository builds a reusable static library target named `ibmfortran`, with the CMake alias `ibmlegacy::fortran`.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Consumers can link the CMake target `ibmfortran` and include headers from `ibmlegacy/fortran`. The `ibm-fortran` executable is a small driver for the current prototype.

The library includes source reading, tokenization, diagnostics, symbol table, numeric expression evaluation, initial intrinsic evaluation, partial FORMAT descriptor parsing, basic runtime I/O/math helpers and a bounded one-dimensional numeric array abstraction.

This is a foundation for a FORTRAN IV-style compiler; it is not a complete implementation of the FORTRAN standard or IBM's historical compiler.