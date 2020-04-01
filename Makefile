CXX:=g++
CXXFLAGS:= -g -std=c++2a -Wall -Wextra -Wpedantic -Wshadow
CLIBS=
LINK_TARGET:=test

OBJS = test.o Tokenizer.o BinaryExpression.o Expression.o ExpressionTree.o Lexer.o Parser.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

.PHONY: all clean test

VERBOSE=1

all: $(LINK_TARGET)

clean:
	@echo Deleting $(REBUILDABLES)
	@rm -f $(REBUILDABLES)

$(LINK_TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CLIBS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CLIBS)

run: $(LINK_TARGET)
	./test

BinaryExpression.o: BinaryExpression.hpp
Expression.o: Expression.hpp
ExpressionTree.o: ExpressionTree.hpp
Lexer.o: Lexer.hpp Tokenizer.hpp
Parser.o: Parser.hpp
Tokenizer.o: Tokenizer.hpp
test.o : BinaryExpression.hpp Expression.hpp ExpressionTree.hpp Lexer.hpp Parser.hpp Tokenizer.hpp
