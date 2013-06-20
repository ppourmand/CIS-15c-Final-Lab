# Nikita Kouevda
# 2013/06/20

# C compiler and options
CC = gcc
CCOPTS = -Wall

# All sources
SOURCES = $(wildcard *.c)

# Phony targets
.PHONY: all clean

all:
	$(CC) $(CCOPTS) $(SOURCES)

%.o: %.c
	$(CC) $(CCOPTS) $+

clean:
	rm -f *.{o,out}
