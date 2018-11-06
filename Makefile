CC = gcc
CFLAGS = -std=c99 -Wall -I.
TARGETS_DOT = \
	  vectorDot.o \
	  vectorDot_test.o \
	  vectorDot

TARGETS = \
	  vector.o \
	  vector_test.o \
	  vector

.PHONY: all clean vectorDot vector

all: $(TARGETS) $(TARGETS_DOT)

vectorDot.o: vectorDot.c Dot.h common_debug.h
	$(CC) $(CFLAGS) -c $< -o $@

vectorDot_test.o: vectorDot_test.c Dot.h
	$(CC) $(CFLAGS) -c $< -o $@

vectorDot: vectorDot.o vectorDot_test.o
	$(CC) $^ -o $@ 

vector.o: vector.c common_debug.h
	$(CC) $(CFLAGS) -c $< -o $@

vector_test.o: vector_test.c
	$(CC) $(CFLAGS) -c $< -o $@

vector: vector.o vector_test.o
	$(CC) $^ -o $@

clean:
	rm -rf vector vectorDot *.o
