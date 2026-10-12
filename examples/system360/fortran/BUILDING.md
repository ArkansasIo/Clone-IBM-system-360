# FORTRAN prototype examples

The `hello.f` and `arithmetic.f` samples use fixed-form source layout. The current translator supports only a small subset and rejects control-flow constructs it cannot lower. It does not produce historically compatible IBM FORTRAN IV output or an executable object deck.

Build from the repository root:

```sh
cmake -S . -B build
cmake --build build
./build/ibm-fortran --help
```

See `docs/FORTRAN_SUPPORT.md` for current limitations.