# Repository layout

- include/ibmlegacy: public headers for CPU, device, FORTRAN, machine, runtime and tape modules
- src: C++23 implementations and command-line applications
- config: descriptive JSON machine profiles
- docs: architecture, research, hardware, testing, roadmap and CPU/FORTRAN status
- examples/system360/fortran: fixed-form FORTRAN sample programs
- tests: unit tests
- scripts: Windows PowerShell and POSIX shell build helpers

The project is incremental. Full historical instruction-set and device compatibility are not claimed.