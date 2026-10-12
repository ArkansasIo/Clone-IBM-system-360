#pragma once
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace ibmlegacy::ui
{

  // Which machine dialect the editor is annotating. This only affects validation
  // and the help/dump formatting; the buffer itself is plain text lines.
  enum class EditorFlavor
  {
    Plain,    // free text
    Ibm1401,  // 1401 character-oriented source (A/B word/character addresses)
    System360 // assembler-style source with RR-subset mnemonics
  };

  // Outcome of one editor command, so a caller (menu or script) can react.
  enum class EditorStatus
  {
    Ok,
    Saved,  // file written
    Loaded, // file read into buffer
    Quit,   // operator asked to leave the editor
    Error   // see last_error()
  };

  // A small line editor over an in-memory buffer with optional file backing.
  // Deliberately terminal-agnostic: every operation is a method so the same code
  // path is exercised by the interactive menu and by unit tests.
  class LineEditor
  {
  public:
    explicit LineEditor(EditorFlavor flavor = EditorFlavor::Plain);

    [[nodiscard]] EditorFlavor flavor() const noexcept { return flavor_; }
    [[nodiscard]] const std::string &path() const noexcept { return path_; }
    [[nodiscard]] bool modified() const noexcept { return modified_; }
    [[nodiscard]] const std::string &last_error() const noexcept { return last_error_; }

    [[nodiscard]] std::size_t line_count() const noexcept { return lines_.size(); }
    [[nodiscard]] std::size_t cursor() const noexcept { return cursor_; } // 1-based
    [[nodiscard]] const std::vector<std::string> &lines() const noexcept { return lines_; }

    // ---- navigation -------------------------------------------------------
    bool goto_line(std::size_t line_number); // 1-based; clamps, false if empty
    void move_up(std::size_t n = 1);
    void move_down(std::size_t n = 1);
    void move_top();
    void move_bottom();

    // ---- mutation ---------------------------------------------------------
    // Insert a new line after the cursor (cursor advances onto the new line).
    bool insert_after(std::string text);
    // Replace the current line. Empty buffer inserts at position 1.
    bool replace_current(std::string text);
    // Append text to the current line.
    bool append_to_current(std::string text);
    // Delete the current line; cursor stays on the same index when possible.
    bool delete_current();
    // Insert raw text split on '\n' at the cursor.
    bool insert_block(std::string_view text);

    // ---- buffer / file ----------------------------------------------------
    void clear();
    void set_lines(std::vector<std::string> lines);
    bool load_file(const std::string &path);
    bool save_file(); // save to path_
    bool save_file_as(const std::string &path);
    [[nodiscard]] std::string render_buffer() const; // lines joined with '\n'

    // ---- validation -------------------------------------------------------
    // Flavor-aware sanity check of the buffer. Returns a human-readable problem
    // string, or nullopt when the buffer looks acceptable.
    [[nodiscard]] std::optional<std::string> validate() const;

    // ---- display ----------------------------------------------------------
    void render(std::ostream &out) const; // numbered listing with cursor mark

  private:
    void clamp_cursor();

    EditorFlavor flavor_;
    std::vector<std::string> lines_;
    std::size_t cursor_{1};
    std::string path_;
    bool modified_{false};
    std::string last_error_;
  };

  // Formatting helpers shared by the editors and menus.
  [[nodiscard]] std::string flavor_name(EditorFlavor flavor);
  [[nodiscard]] std::string format_1401_dump(const std::string &ascii);
  [[nodiscard]] std::string format_360_hex_dump(const std::vector<std::uint8_t> &bytes,
                                                std::size_t base_address = 0);

} // namespace ibmlegacy::ui
