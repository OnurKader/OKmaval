#include "Lexer.hpp"

namespace OK
{
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

	return Token(TokenType::Bad, "", m_tokenizer.position(), nullptr);
}
}	 // namespace OK
