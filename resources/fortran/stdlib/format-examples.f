C     FORMAT examples for the partial descriptor parser
      PROGRAM FORMATS
      INTEGER I
      REAL X
      I = 12
      X = 3.5
C     FORMAT parsing resources only; compiler formatted I/O is not ready.
  100 FORMAT(I5,F8.2)
      PRINT *, I, X
      STOP
      END
