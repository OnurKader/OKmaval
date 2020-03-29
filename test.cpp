#include "Parser.hpp"
#include "Tokenizer.hpp"

#include <cstdio>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const OK::Token& token)
{
	os << '[' << OK::TokenTypeStrings[static_cast<uint8_t>(token.type())] << "]: '" << token.str()
	   << '\'';
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
		OK::Tokenizer tokenizer(input_buffer);

		while(true)
		{
			OK::Token tok = tokenizer.parseInt();
			if(tok.type() == OK::TokenType::Bad || tok.type() == OK::TokenType::EndOfFile)
				break;
			printf("Got Token with %ld\n", tok.asInt());
			std::cout << tok << std::endl;
			if(tok.type() == OK::TokenType::Integer)
				break;
		}

		delete[] input_buffer;
		input_buffer = nullptr;

		printf("\033[32;1m\u276F\033[m ");
	}

	return 0;
}
