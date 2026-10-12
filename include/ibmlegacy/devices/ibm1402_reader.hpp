#pragma once
#include "ibmlegacy/devices/card_deck.hpp"
#include "ibmlegacy/devices/device.hpp"
#include <cstddef>
#include <optional>
#include <string>
namespace ibmlegacy::devices {
class VirtualIBM1402Reader final:public Device {
public:
 void load_deck(CardDeck deck); [[nodiscard]] std::optional<std::string> read_card();
 void reset()override; [[nodiscard]] DeviceStatus status()const noexcept override; [[nodiscard]] std::string name()const override;
 [[nodiscard]] std::size_t cards_remaining()const noexcept;
private: CardDeck deck_; std::size_t position_{0}; DeviceStatus status_{DeviceStatus::NotReady};
};
}