ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = serial-tests

AM_CFLAGS = -Wall	\
			-Wextra \
			-pedantic \
			-std=c99 \
			-O2

lib_LTLIBRARIES = libvector_c.la
libvector_c_la_CFLAGS = -I./include
libvector_c_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = README.md LICENSE autogen.sh

vectordir=$(includedir)/vector
vector_HEADERS = include/vector/vector.h

libvector_c_la_SOURCES = src/vector.c

# with 'make check', this will run test suite
check_PROGRAMS = test/tests
TESTS = $(check_PROGRAMS)
test_tests_SOURCES = test/test_vector.c

test_tests_CFLAGS = -I./include \
					-std=c99 \
					-O2
test_tests_LDFLAGS = -lm \
					 -lvector_c
