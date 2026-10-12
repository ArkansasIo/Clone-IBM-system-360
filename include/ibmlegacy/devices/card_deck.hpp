#pragma once
#include <filesystem>
#include <string>
#include <vector>
namespace ibmlegacy::devices {
class CardDeck { public: static constexpr std::size_t columns=80; void add(std::string card); [[nodiscard]] const std::vector<std::string>& cards()const noexcept; void save_text(const std::filesystem::path&)const; static CardDeck load_text(const std::filesystem::path&); private: std::vector<std::string> cards_; };
}