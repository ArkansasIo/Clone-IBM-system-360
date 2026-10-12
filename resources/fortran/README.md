# FORTRAN resources

These are independently written resources for the educational FORTRAN IV-style toolchain. They are not IBM proprietary compiler files or an authoritative complete language specification.

- `intrinsics.json`: intrinsic inventory implemented or planned.
- `keywords.json`: language statement and declaration inventory.
- `format-descriptors.json`: initial supported FORMAT descriptor inventory.
- `dialect-profile.json`: explicit subset profile and unsupported features.
- `examples/`: source and input fixtures.
- `include/ibmlegacy/fortran/`: public library headers, AST, parser, lexer, symbol table, expression evaluator, diagnostics, runtime helpers and array utility.
- `src/fortran/`: implementation files.

Run `python3 scripts/validate_fortran_resources.py` to validate the resource metadata. CI also translates, compiles and runs the two supported-subset examples. All syntax/semantics must be verified against a specific FORTRAN IV reference manual before claiming dialect compatibility.