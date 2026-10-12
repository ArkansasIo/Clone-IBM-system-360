#!/usr/bin/env python3
"""Compile and run the supported FORTRAN example subset end-to-end."""
import argparse
import subprocess
import tempfile
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
EXAMPLES = ROOT / "resources" / "fortran" / "examples"

def run(command: list[str]) -> subprocess.CompletedProcess[str]:
    return subprocess.run(command, check=False, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--compiler", default=str(ROOT / "build" / "ibm-fortran"))
    parser.add_argument("--cxx", default="c++")
    args = parser.parse_args()
    compiler = Path(args.compiler)
    if not compiler.is_file():
        print(f"FORTRAN compiler executable not found: {compiler}", file=sys.stderr)
        return 2
    for name in ("hello", "arithmetic"):
        source = EXAMPLES / f"{name}.f"
        expected_path = EXAMPLES / f"{name}.expected.txt"
        if not source.is_file() or not expected_path.is_file():
            print(f"missing source or expected output for {name}", file=sys.stderr)
            return 1
        with tempfile.TemporaryDirectory(prefix="ibm-fortran-") as tmp:
            generated = Path(tmp) / f"{name}.cpp"
            executable = Path(tmp) / name
            translated = run([str(compiler), "--emit-c", str(source), str(generated)])
            if translated.returncode:
                print(translated.stderr or translated.stdout, file=sys.stderr)
                return translated.returncode
            built = run([args.cxx, "-std=c++23", str(generated), "-o", str(executable)])
            if built.returncode:
                print(built.stderr or built.stdout, file=sys.stderr)
                return built.returncode
            executed = run([str(executable)])
            expected = expected_path.read_text(encoding="utf-8")
            if executed.returncode or executed.stdout != expected:
                print(f"{name}: output mismatch\nexpected={expected!r}\nactual={executed.stdout!r}\n{executed.stderr}", file=sys.stderr)
                return 1
            print(f"{name}: passed")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
