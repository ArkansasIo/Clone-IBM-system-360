* Educational System/360 assembler example
         START 0
         LA    1,DATA
         L     2,VALUE
         A     2,VALUE
         ST    2,RESULT
         BC    15,HALT
HALT     BCR   15,0
VALUE    DC    F'1'
RESULT   DC    F'0'
DATA     DC    C'HELLO S/360'
         END   START
