#pragma once

#include "Tokenizer.hpp"

namespace OK
{
class Lexer
{
	public:
	Lexer(const char* str) : m_tokenizer(str), m_str(str) {}
	Token nextToken();

	private:
	Tokenizer m_tokenizer;
	std::string_view m_str;
};
}	 // namespace OK
