# System/360 CPU Expansion Milestone

This milestone expands the educational System/360 execution core from the original RR-only subset toward a table-driven CPU.

## Goals

- Keep instruction metadata separate from execution logic.
- Support RR logical, compare, add/subtract, load/test and branch instructions.
- Add RX-format effective-address calculation.
- Add basic RX load/store/add/compare and conditional-branch instructions.
- Preserve the existing `System360Cpu` API and C++23 build.
- Keep architectural behavior explicit and testable rather than claiming full historical compatibility.

## Scope

The implementation is an educational emulator. It does not claim complete System/360 compatibility. Unsupported opcodes must remain explicit `IllegalInstruction` results.

## Instruction groups

### RR

`BALR`, `BCR`, `LR`, `CR`, `AR`, `SR`, `MR`, `DR`, `NR`, `OR`, `XR`, `CLR`, `ALR`, `SLR`, `LTR`.

### RX

`BC`, `BAL`, `BCT`, `LA`, `ST`, `L`, `C`, `A`, `S`, `N`, `O`, `X`.

RX instructions use the architectural `base + index + displacement` effective-address form with a 12-bit displacement. Register 0 is treated as zero when used as base or index.

## Condition-code policy

The CPU stores the architectural condition code as a two-bit value. Arithmetic and comparison helpers update it according to the operation. Branch masks use the System/360 convention where mask bit `3 - CC` selects the corresponding condition code.

## Next steps

1. Add remaining RX/RS/SI/SS instruction families.
2. Model the full 64-bit PSW and interruption state.
3. Add channel-program execution and device status/sense handling.
4. Add instruction-level conformance fixtures.
5. Add model profiles and memory-size validation.
