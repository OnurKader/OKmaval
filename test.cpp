#include "Lexer.hpp"
#include "Parser.hpp"

#include <cstdio>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const OK::Token& token)
{
	os << '[' << OK::TokenTypeStrings[static_cast<uint8_t>(token.type())] << "]: ";

	switch(token.type())
	{
		case OK::TokenType::Integer: os << token.asInt(); break;
		case OK::TokenType::Double: os << token.asDouble(); break;
		default: os << token.str(); break;
	}

	return os;
}

int main()
{
	char* input_buffer = nullptr;
	ssize_t read_count = 0ULL;
	size_t len = 0ULL;

	printf("\033[32;1m\u276F\033[m ");

	while((read_count = getline(&input_buffer, &len, stdin)) != -1)
	{
		input_buffer[--read_count] = '\0';
		OK::Lexer lexer(input_buffer);

		while(true)
		{
			OK::Token tok = lexer.nextToken();

			// Should be a switch
			if(tok.type() == OK::TokenType::EndOfFile)
				break;
			else if(tok.type() == OK::TokenType::Bad)
			{
				std::cout << "Unrecognized identifier " << tok << std::endl;
				break;
			}
			else if(tok.type() == OK::TokenType::Whitespace)
				continue;

			std::cout << tok << std::endl;
		}

		delete[] input_buffer;
		input_buffer = nullptr;

		printf("\033[32;1m\u276F\033[m ");
	}

	return 0;
}
