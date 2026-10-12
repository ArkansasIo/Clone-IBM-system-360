# Roadmap

## Foundation completed
- [x] C++23/CMake skeleton and CI workflow
- [x] Virtual tape image records, tape marks and navigation
- [x] 1401 character storage with word-mark representation
- [x] System/360 byte storage and register model
- [x] Generic virtual tape drive, card deck and line-printer abstractions
- [x] Small System/360 RR instruction subset and opcode metadata
- [x] Educational channel command queue
- [x] Hex byte loader and EBCDIC invariant-character conversion
- [x] Named IBM 729 and IBM 2400 family configuration profiles
- [x] Experimental fixed-form FORTRAN reader/translator
- [x] Model-specific scope and research documentation

## Major implementation work remaining
- [ ] IBM 1401 instruction decoding, word-mark semantics and decimal arithmetic verified against primary manuals
- [ ] IBM 1401 BCD character conversion and record/device operations
- [ ] Broader System/360 instruction set, effective-address calculation, condition-code edge cases and PSW behavior
- [ ] Program interruptions, external interruptions, I/O interruptions and supervisor state
- [ ] Channel command chaining, sense data and device status transitions
- [ ] IBM 729 and IBM 2400 model-specific commands, recording formats and transport timing
- [ ] Card reader/punch column encoding and printer carriage control
- [ ] FORTRAN IV FORMAT, I/O, DO loops, labels, subprograms and runtime conventions
- [ ] Assembler and object-module generation/loader
- [ ] Integration tests against manuals and a trusted reference emulator
- [ ] Run and verify all CI builds on Linux, macOS and Windows

Named hardware profiles are configuration scaffolds, not claims of cycle-accurate or full historical compatibility.