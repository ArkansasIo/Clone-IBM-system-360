#pragma once
#include <cstdint>
namespace ibmlegacy::machines {
struct IBM1401Character {
 std::uint8_t code{0};
 bool word_mark{false};
 bool record_mark{false};
 bool group_mark{false};
 bool item_mark{false};
};
}