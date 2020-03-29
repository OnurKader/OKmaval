#pragma once

#include <cstring>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

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
	Integer,
	Double,
	Expression,
	NumericExpression,
	BinaryExpression,
	EndOfFile,
	Bad
};

constexpr const char* TokenTypeStrings[] = {
	"Whitespace",		"Addition",	  "Subtraction", "Multiplication", "Division",
	"Modulus",			"BitwiseAND", "BitwiseOR",	 "BitwiseXOR",	   "BitwiseNOT",
	"LogicalAND",		"LogicalOR",  "LogicalNOT",	 "OpenParens",	   "CloseParens",
	"ParensExpression", "Integer",	  "Double",		 "Expression",	   "NumericExpression",
	"BinaryExpression", "EndOfFile",  "Bad"};

using token_t = std::variant<int64_t, double, std::nullptr_t>;

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

	int64_t& asInt() { return std::get<int64_t>(m_value); }
	const int64_t& asInt() const { return std::get<int64_t>(m_value); }
	double& asDouble() { return std::get<double>(m_value); }
	const double& asDouble() const { return std::get<double>(m_value); }

	private:
	TokenType m_type;
	std::string_view m_str;
	size_t m_position;
	token_t m_value;
};

class Tokenizer
{
	public:
	Tokenizer(const char* str) : m_str(str) {}

	const char& current(size_t offset = 0ULL) const { return m_str[m_index + offset]; }
	size_t increment() { return ++m_index; }
	std::string_view& str() { return m_str; }
	const std::string_view& str() const { return m_str; }
	const char* data() const { return m_str.data(); }

	Token parseWhitespace()
	{
		if(m_str.data() == nullptr || position() >= m_str.length())
			return Token(TokenType::EndOfFile, nullptr, position(), nullptr);

		if(std::isspace(current()))
		{
			size_t start = position();
			while(std::isspace(current()))
				increment();

			size_t length = position() - start;
			char* token_buffer = new char[length];
			str().copy(token_buffer, length, start);

			return Token(TokenType::Whitespace, token_buffer, start, nullptr);
		}

		return Token(TokenType::Bad, str().data() + position(), position(), nullptr);
	}

	Token parseInt()
	{
		if(m_str.data() == nullptr || position() >= m_str.length())
			return Token(TokenType::EndOfFile, nullptr, position(), nullptr);

		size_t start = position();

		if(current() == '-' && std::isdigit(current(1ULL)))	   // Negative Number
			increment();

		if(std::isdigit(current()))	   // Positive Number
		{
			while(std::isdigit(current()))
				increment();

			size_t length = position() - start;
			char* token_buffer = new char[length];
			str().copy(token_buffer, length, start);
			int64_t value = std::atoll(token_buffer);
			return Token(TokenType::Integer, token_buffer, start, value);
		}

		return Token(TokenType::Bad, str().data() + position(), position(), nullptr);
	}

	Token parseDouble()
	{
		if(m_str.data() == nullptr || position() >= m_str.length())
			return Token(TokenType::EndOfFile, nullptr, position(), nullptr);

		size_t start = position();

		if(((current() == '-' || current() == '.') &&
			std::isdigit(current(1))))	  // Doesn't support -.234 yet
			increment();

		if(std::isdigit(current()))
		{
			while(std::isdigit(current()) || current() == '.')
				increment();

			size_t length = position() - start;
			char* token_buffer = new char[length];
			str().copy(token_buffer, length, start);
			double value = std::atof(token_buffer);
			return Token(TokenType::Double, token_buffer, start, value);
		}

		return Token(TokenType::Bad, str().data() + position(), position(), nullptr);
	}

	size_t index() const { return m_index; }
	size_t position() const { return m_index; }

	private:
	std::string_view m_str;
	size_t m_index {0ULL};
};

}	 // namespace OK
