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
	Word,
	Expression,
	NumericExpression,
	BinaryExpression,
	EndOfFile,
	Bad
};

constexpr const char* TokenTypeStrings[] = {
	"Whitespace", "Addition",	"Subtraction",		 "Multiplication",	 "Division",   "Modulus",
	"BitwiseAND", "BitwiseOR",	"BitwiseXOR",		 "BitwiseNOT",		 "LogicalAND", "LogicalOR",
	"LogicalNOT", "OpenParens", "CloseParens",		 "ParensExpression", "Integer",	   "Double",
	"Word",		  "Expression", "NumericExpression", "BinaryExpression", "EndOfFile",  "Bad"};

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
	size_t increment(size_t offset = 1ULL) { return m_index += offset; }
	std::string_view& str() { return m_str; }
	const std::string_view& str() const { return m_str; }
	const char* data() const { return m_str.data(); }

	Token parseWhitespace()
	{
		if(m_str.data() == nullptr || position() >= m_str.length())
			return Token(TokenType::EndOfFile, "", position(), nullptr);

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
			return Token(TokenType::EndOfFile, "", position(), nullptr);

		size_t start = position();

		if(current() == '-' && std::isdigit(current(1)))	// Negative Number
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
			return Token(TokenType::EndOfFile, "", position(), nullptr);

		size_t start = position();
		bool has_seen_period = false;

		if(current() == '-' && std::isdigit(current(1)))
			increment();
		else if(current() == '.' && std::isdigit(current(1)))
		{
			increment();
			has_seen_period = true;
		}
		else if(current() == '-' && current(1) == '.' && std::isdigit(current(2)))
		{
			has_seen_period = true;
			increment(3);
		}

		if(std::isdigit(current()))
		{
			while(std::isdigit(current()) || current() == '.')
			{
				increment();
				if(current() == '.')
					has_seen_period = true;
			}

			if(has_seen_period)
			{
				size_t length = position() - start;
				char* token_buffer = new char[length];
				str().copy(token_buffer, length, start);
				double value = std::atof(token_buffer);
				return Token(TokenType::Double, token_buffer, start, value);
			}
			else
			{
				m_index = start;
				return parseInt();
			}
		}

		return Token(TokenType::Bad, str().data() + position(), position(), nullptr);
	}

	Token parseWord()
	{
		if(m_str.data() == nullptr || position() >= m_str.length())
			return Token(TokenType::EndOfFile, "", position(), nullptr);

		size_t start = position();

		if(std::isalpha(current()))
		{
			while(std::isalnum(current()) || current() == '_')
				increment();

			size_t length = position() - start;
			char* token_buffer = new char[length];
			str().copy(token_buffer, length, start);
			return Token(TokenType::Word, token_buffer, start, nullptr);
		}

		return Token(TokenType::Bad, str().data() + position(), position(), nullptr);
	}

	Token parseOperator()
	{
		if(m_str.data() == nullptr || position() >= m_str.length())
			return Token(TokenType::EndOfFile, "", position(), nullptr);

		size_t start = position();
		char c = current();
		increment();
		switch(c)
		{
			case '+': return Token(TokenType::Addition, "+", start, nullptr);
			case '-': return Token(TokenType::Subtraction, "-", start, nullptr);
			case '*': return Token(TokenType::Multiplication, "*", start, nullptr);
			case '/': return Token(TokenType::Division, "/", start, nullptr);
			case '%': return Token(TokenType::Modulus, "%", start, nullptr);
			case '(': return Token(TokenType::OpenParens, "(", start, nullptr);
			case ')': return Token(TokenType::CloseParens, ")", start, nullptr);

			// Add Support for && and other multi character operators
			case '&': return Token(TokenType::BitwiseAND, "&", start, nullptr);
			case '|': return Token(TokenType::BitwiseOR, "|", start, nullptr);
			case '^': return Token(TokenType::BitwiseXOR, "^", start, nullptr);
			default: break;
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
