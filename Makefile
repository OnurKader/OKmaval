CC=g++
CFLAGS=-g -std=c++2a -Wall -Wextra -Wpedantic -Wshadow
CLIBS=
LINK_TARGET = test

OBJS = Maval.o test.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

.PHONY: all clean test

clean:
	@rm -f $(REBUILDABLES)

all: $(LINK_TARGET)

$(LINK_TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(CLIBS)

%.o: %.cpp
	g++ -g -o $@ -c $< $(CFLAGS) $(CLIBS)

Maval.o : Maval.hpp
test.o : test.hpp Maval.hpp
