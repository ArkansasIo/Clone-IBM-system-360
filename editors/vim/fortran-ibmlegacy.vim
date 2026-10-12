" Vim syntax file for IBM Legacy FORTRAN (fixed form).
" Install by copying to ~/.vim/syntax/ and adding:
"   au BufRead,BufNewFile *.f,*.for,*.ftn,*.f77 set filetype=fortran-ibmlegacy
if exists("b:current_syntax")
  finish
endif

let b:current_syntax = "fortran-ibmlegacy"

syntax keyword ibmFortranType INTEGER REAL LOGICAL COMPLEX CHARACTER DIMENSION
syntax keyword ibmFortranType COMMON EQUIVALENCE EXTERNAL INTRINSIC PARAMETER DATA IMPLICIT
syntax keyword ibmFortranType DOUBLE PRECISION
syntax keyword ibmFortranStatement PROGRAM END STOP PAUSE CONTINUE RETURN CALL
syntax keyword ibmFortranStatement SUBROUTINE FUNCTION DO IF THEN ELSE GOTO
syntax keyword ibmFortranStatement GO TO ASSIGN READ WRITE PRINT FORMAT REWIND
syntax keyword ibmFortranIntrinsic ABS SQRT EXP LOG SIN COS TAN ATAN INT FLOAT SIGN MOD MIN MAX
syntax keyword ibmFortranOperator EQ NE LT LE GT GE AND OR NOT TRUE FALSE

syntax match ibmFortranComment "^[Cc*!].*$"
syntax region ibmFortranString start=/'/ end=/'/ oneline
syntax region ibmFortranString start=/"/ end=/"/ oneline
syntax match ibmFortranNumber "\<\d\+\(\.\d*\)\?\([eEdD][+-]\?\d\+\)\?\>"
syntax match ibmFortranLabel "^[ 0-9]\{5\}\ze[^ 0Cc*!]"

highlight default link ibmFortranType Type
highlight default link ibmFortranStatement Statement
highlight default link ibmFortranIntrinsic Function
highlight default link ibmFortranOperator Operator
highlight default link ibmFortranComment Comment
highlight default link ibmFortranString String
highlight default link ibmFortranNumber Number
highlight default link ibmFortranLabel Label
