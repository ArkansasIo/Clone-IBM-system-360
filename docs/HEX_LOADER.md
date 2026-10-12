# Hex program loader

The optional hex loader accepts whitespace-separated two-digit hexadecimal bytes, with comments beginning with # or ;. It writes bytes into the configured System/360 storage after checking the starting address and bounds. It does not parse assembler source, relocations, object decks, or executable formats.

Example bytes are in examples/system360/rr_subset.hex. The sample contains instruction encodings for the currently implemented educational RR subset and is not a complete standalone program.