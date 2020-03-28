#pragma once

#include <cstring>
#include <string_view>
#include <utility>
#include <variant>

namespace OK
{
enum class TokenType : uint8_t
{
	Whitespace,
	Addition,
	Subtraction,
	Multiplication,
	Division,
	Modulus,
	BitwiseAND,
	BitwiseOR,
	BitwiseXOR,
	BitwiseNOT,
	LogicalAND,
	LogicalOR,
	LogicalNOT,
	OpenParens,
	CloseParens,
	ParensExpression,
	Number,
	Expression,
	NumericExpression,
	BinaryExpression,
	EndOfFile,
	Bad
};

using token_t = std::variant<int64_t, double, char*, std::nullptr_t>;

static constexpr const char* TokenTypeStrings[] = {
	"Whitespace",		"Addition",	  "Subtraction", "Multiplication",	  "Division",
	"Modulus",			"BitwiseAND", "BitwiseOR",	 "BitwiseXOR",		  "BitwiseNOT",
	"LogicalAND",		"LogicalOR",  "LogicalNOT",	 "OpenParens",		  "CloseParens",
	"ParensExpression", "Number",	  "Expression",	 "NumericExpression", "BinaryExpression",
	"EndOfFile",		"Bad"};

class Token
{
	public:
	Token(TokenType, const char*, size_t, token_t);
	std::string_view& view() { return m_str; }
	const std::string_view& view() const { return m_str; }
	const char* str() const { return m_str.data(); }
	size_t position() const { return m_position; }
	TokenType& type() { return m_type; }
	const TokenType& type() const { return m_type; }
	token_t value() { return m_value; }
	const token_t value() const { return m_value; }

	template<typename T>
	T& as()
	{
		return std::get<T>(m_value);
	}

	template<typename T>
	const T& as() const
	{
		return std::get<T>(m_value);
	}

	private:
	TokenType m_type;
	std::string_view m_str;
	size_t m_position;
	token_t m_value;
};

class Tokenizer
{
};

}	 // namespace OK
