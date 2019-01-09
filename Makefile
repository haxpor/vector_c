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

TARGETS_DOT_LINK = $(filter-out vectorDot, $(TARGETS_DOT))
TARGETS_LINK = $(filter-out vector, $(TARGETS))

.PHONY: all clean vectorDot vector

all: $(TARGETS) $(TARGETS_DOT)

# for specific type Dot
vectorDot.o: vectorDot.c Dot.h common_debug.h
	$(CC) $(CFLAGS) -c $< -o $@

vectorDot_test.o: vectorDot_test.c Dot.h
	$(CC) $(CFLAGS) -c $< -o $@

vectorDot: $(TARGETS_DOT_LINK)
	$(CC) $^ -o $@ 

# general purpose
vector.o: vector.c common_debug.h
	$(CC) $(CFLAGS) -c $< -o $@

vector_test.o: vector_test.c
	$(CC) $(CFLAGS) -c $< -o $@

vector: $(TARGETS_LINK)
	$(CC) $^ -o $@

clean:
	rm -rf vector vectorDot *.o
