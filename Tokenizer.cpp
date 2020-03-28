#include "Tokenizer.hpp"

namespace OK
{
Token::Token(TokenType type, const char* str, size_t position, token_t value) :
	m_type(type), m_str(str), m_position(position), m_value(value)
{
}

}	 // namespace OK
