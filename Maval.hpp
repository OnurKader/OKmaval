#pragma once

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <stack>
#include <string>

namespace OK
{
enum class Operator
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
			default: return m_rhs;
		}
	}
};

class Maval
{
	public:
	Maval();
	~Maval();

	private:
};
}	 // namespace OK
