# Architecture

Layers: machine models, device models, I/O fabric, media formats, command-line tools, and tests.

## IBM 1401
Character-oriented decimal architecture. Current memory model stores a character code plus a separate word-mark bit. It is not a CPU emulator yet.

## System/360
Byte-addressed storage, 16 general registers, instruction address and condition code. The implemented CPU is only a small register-instruction subset; the PSW, interrupts, storage protection and channel subsystem are not complete.

## Tape
VMT1 is a project-defined tape-image container with records and tape marks. It is not a bit-level IBM tape dump and does not model physical tape timing.

## FORTRAN
The compiler prototype reads fixed-form source and translates a limited subset to host C++. The System/360 listing output is documentation scaffolding, not executable machine code.