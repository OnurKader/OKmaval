#pragma once

#include <cfloat>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <stack>
#include <string>

namespace OK
{
enum class Operator : uint8_t
{
	Nop,
	Addition,
	Subtraction,
	Multiplication,
	Division,
	OpenParens,
	CloseParens,
	Comma,
	SemiColon,
	Assignment,
	LogicalAnd,
	LogicalOr,
	LogicalXor,
	LogicalNot,
	BitwiseAnd,
	BitwiseOr,
	BitwiseXor,
};

class Expression
{
	public:
	Expression(Operator op, double val);
	virtual ~Expression();
	Operator op() const { return m_operator; }
	double rhs() const { return m_rhs; }
	virtual double evaluate() = 0;

	protected:
	Operator m_operator;
	double m_rhs;
};

class UnaryExpression : public Expression
{
	public:
	UnaryExpression(Operator op, double val);
	~UnaryExpression() override;
	double evaluate() override
	{
		switch(m_operator)
		{
			case Operator::Subtraction: return -m_rhs;
			case Operator::LogicalNot: return !static_cast<int>(m_rhs);
			// FIXME Add bitwise operations
			default: return m_rhs;
		}
	}
};

class BinaryExpression : public Expression
{
	public:
	BinaryExpression(Operator op, double lhs, double rhs);
	~BinaryExpression() override;
	double lhs() const { return m_lhs; }
	double evaluate() override
	{
		switch(m_operator)
		{
			case Operator::Nop: return DBL_MAX;
			case Operator::Addition: return m_lhs + m_rhs;
			case Operator::Subtraction: return m_lhs - m_rhs;
			case Operator::Multiplication: return m_lhs * m_rhs;
			case Operator::Division:
				// FIXME Check for m_rhs == 0.0, maybe print something sassy
				return m_lhs / m_rhs;
			case Operator::LogicalAnd: return static_cast<int>(m_lhs) && static_cast<int>(m_rhs);
			case Operator::LogicalOr: return static_cast<int>(m_lhs) || static_cast<int>(m_rhs);
			case Operator::BitwiseAnd: return static_cast<int>(m_lhs) & static_cast<int>(m_rhs);
			case Operator::BitwiseOr: return static_cast<int>(m_lhs) | static_cast<int>(m_rhs);
			case Operator::BitwiseXor: return static_cast<int>(m_lhs) ^ static_cast<int>(m_rhs);
			default:
				fprintf(stderr, "I'm sorry Onur, I'm afraid I can't do that\n");
				return DBL_MAX;
		}
	}

	private:
	double m_lhs;
};

class Maval
{
	public:
	Maval();
	~Maval();

	private:
};
}	 // namespace OK
