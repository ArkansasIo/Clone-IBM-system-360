# CPU status

## System/360
The educational stepper recognizes LR, AR, BALR, and BCR register-format instructions. It does not implement the complete System/360 architecture, full PSW semantics, interrupts, storage protection, full addressing modes, or signed-overflow behavior.

## IBM 1401
The current CPU class is a checked instruction-fetch harness. It deliberately reports decoding as unsupported rather than pretending to emulate the complete variable-length instruction set. Instruction semantics must be implemented against the reference manual and verified test vectors.