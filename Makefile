CC = gcc
CFLAGS = -std=c99 -Wall -I.

TARGETS = \
	  vector.o \
	  vector_test.o \
	  vector_test

TARGETS_LINK = $(filter-out vector_test, $(TARGETS))

.PHONY: all clean

all: $(TARGETS)

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c $< -o $@

vector_test.o: vector_test.c
	$(CC) $(CFLAGS) -c $< -o $@

vector_test: $(TARGETS_LINK)
	$(CC) $^ -o $@

clean:
	rm -f vector_test *.o
