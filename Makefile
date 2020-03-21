CC=g++
CFLAGS=-g -std=c++17 -Wall -Wextra -Wpedantic -Wshadow
CLIBS=
LINK_TARGET = test

VERBOSE=1

OBJS = Maval.o Token.o test.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

.PHONY: all clean test

all: $(LINK_TARGET)

clean:
	@echo Deleting $(REBUILDABLES)
	@rm -f $(REBUILDABLES)

$(LINK_TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(CLIBS)

%.o: %.cpp
	g++ -g -o $@ -c $< $(CFLAGS) $(CLIBS)

Maval.o : Maval.hpp Token.hpp
test.o : Maval.hpp Token.hpp
Token.o: Token.hpp
