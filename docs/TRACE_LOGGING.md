# Trace logging

`runtime::TraceLogger` appends categorized text events to a log file. It is intentionally minimal and does not synchronize concurrent writers. Use it for single-threaded development traces, not as a durable audit log or a cycle-accurate hardware trace.