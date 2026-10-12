# Educational System/360 assembler subset

The `ibm-as` command translates RR-format instructions LR, AR, BALR and BCR into their two-byte instruction encodings.

```sh
./build/ibm-as examples/system360/rr_subset.asm rr_subset.bin
```

The current encoder does not implement symbols, address constants, relocations, assembler directives, full operand syntax, object-deck headers or a loader-compatible executable format. Its binary output is a raw byte stream for the educational CPU subset only.