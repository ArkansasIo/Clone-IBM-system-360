# Device modeling strategy

## Shared interfaces
Device implementations should expose readiness/status and a stable name. Media formats must be independent of drive mechanics so image data can be tested separately.

## IBM 729 and IBM 2400
Both families currently use the virtual tape-image backend. Named profiles are descriptive configuration only, not simulations of exact tape speed, recording density encoding, inter-record gaps, rewind behavior, command timing, or parity. Keep model-specific behavior behind explicit profiles and add tests from primary manuals before claiming compatibility.

## IBM 1402/1403
Current card and printer classes are text conveniences. Future implementations should model 80-column card records, character translation, read/punch status, carriage control, forms, and device error paths with regression tests.

## Real hardware
No physical tape unit, controller, serial adapter, or IBM interface is driven by this repository. Any future hardware bridge must be separately implemented, explicitly configured, and tested against a safe mock interface before connecting to equipment.