#!/usr/bin/env python3
"""Validate JSON metadata resources shipped with the FORTRAN library."""
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
RESOURCE_ROOT = ROOT / "resources" / "fortran"
REQUIRED = {
    "intrinsics.json": {"language", "implemented", "planned", "note"},
    "keywords.json": {"declarations", "executable", "program_units", "note"},
    "format-descriptors.json": {"supported_by_initial_parser", "planned", "note"},
    "dialect-profile.json": {"name", "source_form", "statement_columns", "supported_frontend", "planned", "object_output"},
    "stdlib/runtime-functions.json": {"implemented_helpers", "planned_runtime_services", "status"},
    "stdlib/character-set.json": {"source_form", "columns", "case_insensitive_identifiers", "note"},
}

def main() -> int:
    for relative, keys in REQUIRED.items():
        path = RESOURCE_ROOT / relative
        if not path.is_file():
            print(f"missing resource: {path}", file=sys.stderr)
            return 1
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError) as exc:
            print(f"invalid JSON resource {path}: {exc}", file=sys.stderr)
            return 1
        missing = keys - data.keys()
        if missing:
            print(f"{path}: missing keys: {', '.join(sorted(missing))}", file=sys.stderr)
            return 1
    examples = RESOURCE_ROOT / "examples"
    if not (examples / "hello.f").is_file() or not (examples / "arithmetic.f").is_file():
        print("missing required FORTRAN example source", file=sys.stderr)
        return 1
    print("FORTRAN resource metadata and example files are valid")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
