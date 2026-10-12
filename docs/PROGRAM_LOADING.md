# Program loading

Two loaders are available for educational experiments:

- `runtime::load_hex_program`: parses whitespace-separated hex bytes.
- `runtime::load_binary_program`: copies a raw binary file into byte-addressed System/360 storage.

Both validate the target storage range before writing. Neither understands executable headers, relocation, symbols, load maps, object decks, or entry-point metadata. The caller is responsible for setting the instruction address to the correct program entry point.