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
	LogicalNot,
};

class Expression
{
	public:
	Expression(Operator op, double val) : m_operator(op), m_rhs(val) {}
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
	UnaryExpression(Operator op, double val) : Expression(op, val) {}
	~UnaryExpression() override {}
	double evaluate() override
	{
		switch(m_operator)
		{
			case Operator::Subtraction: return -m_rhs;
			// TODO Either static_cast to int or determine the output with a ternary
			case Operator::LogicalNot: return !static_cast<int>(m_rhs);
			default: return m_rhs;
		}
	}
};

class BinaryExpression : public Expression
{
	public:
	BinaryExpression(Operator op, double lhs, double rhs) : Expression(op, rhs), m_lhs(lhs) {}
	~BinaryExpression() override {}
	double evaluate() override
	{
		switch(m_operator)
		{
			case Operator::Nop: return DBL_MAX;
			default: fprintf(stderr, "I'm sorry Onur, I'm afraid I can't do that\n");
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
