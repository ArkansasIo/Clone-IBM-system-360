# System/360 Complete Architecture Plan

This repository is an educational clean-room emulator. The architecture is layered so CPU, storage, channels, devices, loaders, assembler, EBCDIC, IBM 1401 compatibility work, and FORTRAN tooling can evolve independently.

## Layers

1. **Machine** — model profile, storage size, reset and power-on state.
2. **CPU** — GPRs, PSW, instruction decoder, ALU, instruction execution, interrupts.
3. **Memory** — byte/halfword/fullword access with bounds and alignment checks.
4. **Channels** — channel programs, CCWs, device selection, status and interruption.
5. **Devices** — card reader/punch, printer, tape, console and future DASD.
6. **Language tools** — assembler, loader, EBCDIC conversion and FORTRAN runtime/compiler.
7. **Observability** — tracing, deterministic fixtures and conformance tests.

## Instruction pipeline

`fetch -> classify -> decode -> effective-address calculation -> execute -> condition-code update -> PSW synchronization -> interrupt boundary`

Current CPU support includes the RR/RX families already implemented plus RS/SI/SS decoding and a practical execution subset. Historical opcode semantics should be expanded only with architectural tests.

## PSW and interrupt model

`System360PSW` is intentionally small and explicit. It provides the state needed by the emulator without pretending to implement every historical model-specific bit. `System360InterruptController` queues a pending class/code/parameter and is the integration point for program, supervisor, external, machine-check and I/O interruptions.

## Channel model

The channel subsystem exposes CCWs and a device interface. A channel address selects a device, the CCW describes the operation, and the device returns unit/channel status. Future work adds chained CCWs, TIC, skip/suppress-length-indication, sense data, channel status words and asynchronous completion.

## Model profiles

Use JSON configuration for memory size and device topology. Do not encode machine-specific memory sizes or device addresses directly into the CPU implementation.

## Compatibility policy

The project is an educational emulator and is not a replacement for IBM licensed microcode, firmware, manuals, or proprietary source. Historical behavior should be implemented from lawfully obtained public documentation and independently written tests.
