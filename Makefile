CC=g++
CFLAGS=-g -std=c++2a -Wall -Wextra -Wpedantic -Wshadow
CLIBS=
LINK_TARGET = test

OBJS = Maval.o test.o

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

Maval.o : Maval.hpp
test.o : Maval.hpp
