# FORTRAN library and resource inventory

The public headers under `include/ibmlegacy/fortran` provide the current library surface:

- `types.hpp`: scalar/type and source-location models.
- `diagnostic.hpp`: structured diagnostics and diagnostic collection.
- `token.hpp`, `lexer.hpp`: token definitions and statement lexer.
- `source_record.hpp`, `source_reader.hpp`: fixed-form source records.
- `symbol_table.hpp`: case-insensitive symbol table.
- `expression.hpp`: numeric expression evaluator for arithmetic operators and variable lookup.
- `intrinsics.hpp`: initial intrinsic-function evaluation helpers.
- `format_descriptor.hpp`: partial FORMAT descriptor parser.
- `runtime_io.hpp`, `runtime_math.hpp`: simple runtime I/O and mathematical helpers.
- `ast.hpp`, `parser.hpp`: statement-kind AST and fixed-form statement classification parser.\n- `fortran_compiler.hpp`: limited source translation API.

The `resources/fortran` directory contains JSON dialect inventories, a manifest, sample programs with expected-output fixtures, input fixtures, an illustrative include file, and runtime resource inventories. The resource files document the project subset; they are not a complete compiler specification.

## Deliberate limitations
This library is not yet a full FORTRAN IV/H compiler. It lacks a complete statement parser, label/control-flow lowering, arrays, implied DO, COMMON/EQUIVALENCE/DATA semantics, subprogram calling conventions, full formatted I/O, and IBM object-deck output. Validate future semantics against the selected historical language reference and System/360 compiler manuals.