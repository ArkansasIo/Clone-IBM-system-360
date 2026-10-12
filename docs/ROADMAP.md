# Roadmap

## Development foundation present
- [x] C++23/CMake emulator project and CI workflow
- [x] Virtual tape image and initial IBM 729/2400 profile scaffolding
- [x] IBM 1401 character storage and word-mark representation
- [x] System/360 storage, registers and a small RR instruction subset
- [x] Device abstractions, text card/printer models and channel queue
- [x] Hex/binary program loading and basic EBCDIC conversion helpers
- [x] FORTRAN static library target and CLI driver
- [x] FORTRAN fixed-form source reader, lexer/token model, diagnostics and symbol table
- [x] Numeric expression evaluator, initial intrinsic helpers and runtime math
- [x] Basic runtime text I/O, partial FORMAT descriptor parser and bounded 1-D numeric array utility
- [x] FORTRAN dialect/resource manifests, examples, expected outputs and CI validation scripts
- [x] Experimental FORTRAN-to-C++ subset emitter and illustrative System/360 listing emitter

## FORTRAN language implementation remaining
- [ ] Complete statement parser and semantic/type analysis
- [ ] FORTRAN implicit typing and declaration/attribute semantics
- [ ] Array declarations, multidimensional arrays, sections and array expressions
- [ ] DO loops, statement labels, arithmetic IF, computed GO TO and assigned GO TO
- [ ] Full FORMAT grammar and formatted/unformatted I/O with unit management
- [ ] DATA, PARAMETER, COMMON, EQUIVALENCE, EXTERNAL and INTRINSIC semantics
- [ ] FUNCTION/SUBROUTINE calling conventions, argument passing and RETURN
- [ ] Historical IBM FORTRAN IV object-module and loader integration
- [ ] Conformance tests against a selected manual/compiler reference

## Emulator implementation remaining
- [ ] Verified IBM 1401 instruction decoder, decimal arithmetic and device operations
- [ ] Broader System/360 instruction set, addressing, PSW and interruptions
- [ ] Channel programs, device status/sense and model-specific tape behavior
- [ ] Build/test verification across supported toolchains and operating systems

Completed foundation items describe code scaffolding and limited subset functionality, not complete historical compatibility.