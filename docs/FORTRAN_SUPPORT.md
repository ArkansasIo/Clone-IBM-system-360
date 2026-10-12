# System/360 FORTRAN support

The ibm-fortran tool is an independently written fixed-form source reader and limited translator. It is not IBM FORTRAN IV or FORTRAN H and does not provide full dialect compatibility.

The C++ emitter supports simple declarations, assignments, and PRINT lists. It rejects unsupported control flow rather than silently compiling it incorrectly. The System/360 listing emitter is explanatory scaffolding, not executable machine code or an object deck.

Future work: expression parsing, label-aware DO/GO TO/arithmetic IF lowering, FORMAT and I/O, subprogram linkage, runtime conventions, object modules, and loader integration.