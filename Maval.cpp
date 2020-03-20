#include "Maval.hpp"

namespace OK
{
Expression::Expression(Operator op, double val) : m_operator(op), m_rhs(val) {}

Expression::~Expression() {}

UnaryExpression::UnaryExpression(Operator op, double val) : Expression(op, val) {}

UnaryExpression::~UnaryExpression() {}

BinaryExpression::BinaryExpression(Operator op, double lhs, double rhs) :
	Expression(op, rhs), m_lhs(lhs)
{
}

BinaryExpression::~BinaryExpression() {}

Maval::Maval() {}

Maval::~Maval() {}
}	 // namespace OK
