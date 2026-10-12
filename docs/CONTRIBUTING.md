# Contributing

1. Keep emulator behavior tied to a specific IBM model and manual.
2. Mark unimplemented behavior explicitly; do not silently approximate architectural results.
3. Add regression tests for every new instruction, device command or media format behavior.
4. Keep file formats versioned and validate sizes before allocation.
5. Separate historical behavior from convenience features and modern host tooling.
6. Never claim physical hardware support unless an interface has been implemented and tested against that hardware.