#include "Maval.hpp"

#include <iostream>

int main(int argc, char** argv)
{
	OK::Maval maval;

	if(argc == 1)
	{
		std::cout << "Hello There!\n";
		std::cout
			<< "\u03C0 * e = "
			<< OK::BinaryExpression(OK::Operator::Multiplication, 3.14159265, 2.7182818).evaluate()
			<< '\n';
	}

	return 0;
}
