# FORTRAN runtime library resources

The C++ runtime implementation is exposed through headers under `include/ibmlegacy/fortran`. This directory records planned library coverage and is not a binary or historically complete IBM runtime library.

Current helper areas include numeric intrinsics, elementary math, basic list-directed-style text output/input, and array storage scaffolding. Missing areas include complete format editing, unit numbers, OPEN/CLOSE/REWIND/BACKSPACE/ENDFILE, error/status handling, complex arithmetic, and compiler-compatible calling conventions.