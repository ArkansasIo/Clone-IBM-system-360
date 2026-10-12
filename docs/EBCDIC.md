# EBCDIC conversion support

The current conversion helper covers ASCII digits, Latin letters, space, period, comma, hyphen, slash and equals. All other bytes map to a replacement value. This is deliberately not advertised as a complete EBCDIC code page. Select a specific EBCDIC code page and add complete round-trip tests before using it for archival conversion.