C     PLANNED FEATURE EXAMPLE - DO LOOP IS NOT YET LOWERED
      PROGRAM ARRAYS
      INTEGER I,S
      S = 0
C     A future compiler version will support DIMENSION and DO.
C     DO 100 I = 1,10
C 100 S = S + I
      PRINT *, S
      STOP
      END
