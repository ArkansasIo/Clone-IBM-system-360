#pragma once
#include "ibmlegacy/devices/card_deck.hpp"
#include "ibmlegacy/devices/device.hpp"
#include <optional>
#include <string>
namespace ibmlegacy::devices {
class VirtualIBM2540ReaderPunch final:public Device {
public:
 void load_input(CardDeck deck); [[nodiscard]] std::optional<std::string> read_card();
 void punch_card(std::string card); [[nodiscard]] const CardDeck& punched_cards()const noexcept;
 void reset()override; [[nodiscard]] DeviceStatus status()const noexcept override; [[nodiscard]] std::string name()const override;
private: CardDeck input_; CardDeck punched_; std::size_t input_position_{0}; DeviceStatus status_{DeviceStatus::NotReady};
};
}