# Hardware model matrix

| Family | Present implementation | Not implemented |
|---|---|---|
| IBM 1401 | Character storage and word-mark representation | Verified CPU execution, complete BCD character set, full device interface |
| IBM 729 | Virtual tape image backend and named configuration profiles | Physical transport timing, density-specific encoding, parity and model-accurate commands |
| System/360 | Byte storage, GPRs, four-instruction RR subset | Full instruction set, PSW/interruption architecture, complete channel I/O |
| IBM 2400 | Named tape-unit/control-unit profiles using generic tape backend | Model-specific commands, status/sense, channel integration and timing |
| IBM 1402/1403 | Text card-deck and line-printer utilities | Punch/read column encoding, carriage control, full device status and timing |

The table describes the code currently present, not a claim of historical compatibility.