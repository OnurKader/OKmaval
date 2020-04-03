#include "Lexer.hpp"

namespace OK
{
static constexpr const TokenType operators[] = {TokenType::Addition, TokenType::Subtraction};

constexpr bool isOperator(TokenType type)
{
	for(const auto& elem: operators)
		if(type == elem)
			return true;

	return false;
}

Token Lexer::nextToken()
{
	// OOF Just duplicate code, at least make the EOF check into a function
	// Or at least a local lambda

	Token tok = m_tokenizer.parseWhitespace();
	if(tok.type() == TokenType::Whitespace || tok.type() == TokenType::EndOfFile)
		return tok;

	tok = m_tokenizer.parseDouble();
	if(tok.type() == TokenType::Double || tok.type() == TokenType::Integer ||
	   tok.type() == TokenType::EndOfFile)
		return tok;

	tok = m_tokenizer.parseInt();
	if(tok.type() == TokenType::Integer || tok.type() == TokenType::EndOfFile)
		return tok;

	tok = m_tokenizer.parseWord();
	if(tok.type() == TokenType::Word || tok.type() == TokenType::EndOfFile)
		return tok;

	tok = m_tokenizer.parseOperator();
	if(tok.type() == TokenType::EndOfFile || isOperator(tok.type()))
		return tok;

	return Token(TokenType::Bad, "", m_tokenizer.position(), nullptr);
}
}	 // namespace OK
