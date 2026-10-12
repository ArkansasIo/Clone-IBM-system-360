#pragma once
#include <string_view>
namespace ibmlegacy::machines {
struct IBM1401OpcodeInfo { char opcode; std::string_view mnemonic; std::string_view description; };
inline constexpr IBM1401OpcodeInfo ibm1401_opcode_reference[] = {
 {'A',"A","Add (addressing and operands require model-specific decoding)"},
 {'S',"S","Subtract (addressing and operands require model-specific decoding)"},
 {'M',"M","Multiply (availability and semantics depend on configuration)"},
 {'D',"D","Divide (availability and semantics depend on configuration)"},
 {'C',"C","Compare"},
 {'L',"L","Load"},
 {'B',"B","Branch"},
 {'H',"H","Halt"},
 {'R',"R","Read"},
 {'W',"W","Write"}
};
// Mnemonics are an orientation aid, not a complete or authoritative opcode table.
}