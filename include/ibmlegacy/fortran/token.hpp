#pragma once
#include "ibmlegacy/fortran/types.hpp"
#include <string>
namespace ibmlegacy::fortran {
enum class TokenKind { Identifier, IntegerLiteral, RealLiteral, StringLiteral, Plus, Minus, Star, Slash, Power, LeftParen, RightParen, Comma, Equals, Relational, EndOfLine, Invalid };
struct Token { TokenKind kind{TokenKind::Invalid}; std::string lexeme; SourceLocation location; };
}