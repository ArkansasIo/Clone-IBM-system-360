# Testing

Configure and build:

    cmake -S . -B build
    cmake --build build
    ctest --test-dir build --output-on-failure

The test suite currently checks basic memory operations, tape-image round-tripping, card-deck width, and line-printer buffering. It does not certify instruction-set compatibility.