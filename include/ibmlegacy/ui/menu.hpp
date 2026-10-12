nus adn submneus 
#pragma once
#include <cstddef>
#include <functional>
#include <iosfwd>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace ibmlegacy::ui {

// Result of dispatching one menu selection.
enum class MenuOutcome {
  Stay,      // remain in the current menu
  Enter,     // a submenu was pushed
  Back,      // pop back to the parent menu
  Exit       // leave the menu system entirely
};

// One selectable entry. `key` is what the operator types (e.g. "1", "load").
// `action` runs when selected; it may return `Enter` together with a pushed
// submenu (done by the owning Menu) or `Back`/`Exit` to navigate.
struct MenuItem {
  std::string key;
  std::string label;
  std::string help;
  std::function<MenuOutcome(Menu&)> action;
};

class MenuSystem;

// A single menu level: a title plus an ordered list of items. A menu may also
// own named child menus, which is what makes the hierarchy navigable.
class Menu {
 public:
  Menu(std::string title, std::string description = {});

  [[nodiscard]] const std::string& title() const noexcept { return title_; }
  [[nodiscard]] const std::string& description() const noexcept { return description_; }

  // Append a selectable entry. Returns *this so entries can be chained.
  Menu& add(std::string key, std::string label, std::string help,
            std::function<MenuOutcome(Menu&)> action);

  // Register a child menu addressable from this level.
  Menu& add_submenu(Menu child);

  [[nodiscard]] const std::vector<MenuItem>& items() const noexcept { return items_; }
  [[nodiscard]] const std::vector<Menu>& children() const noexcept { return children_; }

  // Find an entry or child menu by key/name. Nullopt when absent.
  [[nodiscard]] std::optional<std::size_t> find_item(std::string_view key) const noexcept;
  [[nodiscard]] std::optional<std::size_t> find_child(std::string_view name) const noexcept;

  // Run one entry by key. Returns nullopt when the key is unknown.
  [[nodiscard]] std::optional<MenuOutcome> select(std::string_view key);

  // Render this level to a stream (the "menu screen").
  void render(std::ostream& out) const;

 private:
  std::string title_;
  std::string description_;
  std::vector<MenuItem> items_;
  std::vector<Menu> children_;
};

// Owns a stack of menus and drives navigation. The root menu is the entry
// point; entering a child pushes it, "back" pops, "exit" unwinds.
class MenuSystem {
 public:
  explicit MenuSystem(Menu root);

  [[nodiscard]] Menu& current() noexcept;
  [[nodiscard]] const Menu& current() const noexcept;
  [[nodiscard]] std::size_t depth() const noexcept { return stack_.size(); }

  // Push a named child of the current menu. False when the name is unknown.
  bool enter(std::string_view child_name);
  // Pop the current menu. False when already at the root.
  bool back();

  // Dispatch a key against the current menu, applying navigation side effects.
  // Returns false when the key is not recognised at this level.
  bool submit(std::string_view key);

  void render(std::ostream& out) const;

  // Breadcrumb such as "Main > IBM 1401 > Memory".
  [[nodiscard]] std::string breadcrumb() const;

 private:
  std::vector<Menu> stack_;
};

}  // namespace ibmlegacy::ui
