# Subsystem inventory

## CPU
- System/360 register and condition-code arithmetic helpers.
- RR instruction decoder metadata and subset encoder.
- IBM 1401 CPU interface remains a placeholder pending verified instruction semantics.

## Assembler
- Fixed-column-ish source-line tokenizer for labels, mnemonics, operands and comments.
- RR subset encoder for LR, AR, BALR and BCR.
- No symbol resolution, relocation, full assembler directives or object deck output yet.

## Devices
- Device bus registry, virtual IBM 1402 text card reader, virtual IBM 1403 printer wrapper.
- IBM 729 and IBM 2400 profiles currently reuse the generic virtual tape image.

## FORTRAN
- Fixed-form source reader records line number, indicator, label columns and statement area.
- Existing compiler translator remains a limited prototype, not a full FORTRAN IV implementation.

## Compatibility policy
Treat every module as educational until its behavior has tests grounded in a specific model's primary reference manual.