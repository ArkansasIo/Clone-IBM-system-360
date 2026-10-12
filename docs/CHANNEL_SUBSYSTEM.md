# Channel subsystem prototype

The virtual channel stores channel-command-word-like entries and tracks a simplified result status and residual count. It is useful for structuring later device I/O code, but it does not implement the System/360 channel protocol, CCW chaining, data chaining, interruption handling, sense bytes, or timing.

The IBM System/360 architecture and device manuals must be used to implement model-specific behavior.