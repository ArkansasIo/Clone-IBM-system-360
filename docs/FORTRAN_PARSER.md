# FORTRAN statement parser scaffold

The parser converts fixed-form source records into a lightweight statement inventory with source locations, statement labels and a statement kind. It recognizes common declaration and executable statement families, including DO, IF, GO TO, READ/WRITE, FORMAT, CALL, RETURN, COMMON, DATA and DIMENSION.

This is a classification/parser scaffold, not a complete grammar or semantic analyzer. It does not validate all operand syntax, label targets, DO termination rules, implicit typing, argument types or compiler-specific extensions. Unknown statements are returned with a warning so the caller can decide how to handle them.